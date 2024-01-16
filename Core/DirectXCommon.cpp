#include "DirectXCommon.h"

#include <dxgidebug.h>
#include <dxcapi.h>
#include <format>
#include <cassert>
#include <Core/Debug.h>
#include <Core/Type/Matrix4x4.h>
#include <Core/Type/Vector4.h>
#include <Core/Type/VertexData.h>

#include <Core/DirectX12/DirectXAdapter.h>
#include <Core/DirectX12/DirectXCommand.h>
#include <Core/DirectX12/DirectXDevice.h>
#include <Core/DirectX12/DirectXFactory.h>
#include <Core/DirectX12/DirectXFence.h>
#include <Core/DirectX12/DirectXInfoQueue.h>



namespace Core {
  DirectXCommon::DirectXCommon(const Window* window)
  {
    this->window = window;
  }
  void DirectXCommon::Initialize()
  {
    // Device
    factory = std::make_unique<DirectXFactory>();
    adapter = std::make_unique<DirectXAdapter>(factory);
    device = std::make_unique<DirectXDevice>(adapter);
    infoQueue = std::make_unique<DirectXInfoQueue>(device);
    command = std::make_unique<DirectXCommand>(device);

    // Swapchain
    // Depth
    // DescripterHeap
    // RenderTarget
    // DepthStencil
    // Fence
    // ViewportRectangle
    // ScissoringRenctangle
    // DCXCompiler
    // ImGui


    //Omory::Debug::Log("Complete create D3D12Device!!!\n");// 初期化完了のログをだす
  }


  void DirectXCommon::Release()
  {
    device->Release();
    adapter->Release();
    factory->Release();
#ifdef _DEBUG
    debugController->Release();
#endif
  }

  void DirectXCommon::InitializeDebugController()
  {
#ifdef _DEBUG
  ID3D12Debug1* debugController = nullptr;
  if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
    // デバッグレイヤーを有効化する
    debugController->EnableDebugLayer();
    // さらにGPU側でもチェックを行うようにする
    debugController->SetEnableGPUBasedValidation(TRUE);
  }

#endif

  }

  void DirectXCommon::InitializeFactory()
  {
    HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
    assert(SUCCEEDED(hr));
  }

void DirectXCommon::InitializeAdapter()
{
  // 良い順にアダプタを頼む
  for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&useAdapter)) != DXGI_ERROR_NOT_FOUND; ++i) {
    // アダプターの情報を取得する
    DXGI_ADAPTER_DESC3 adapterDesc{};
    HRESULT hr = useAdapter->GetDesc3(&adapterDesc);
    assert(SUCCEEDED(hr)); // 取得できないのは一大事
    // ソフトウェアアダプタでなければ採用！
    if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
      // 採用したアダプタの情報をログに出力。wstringの方なので注意
      //Omory::Debug::Log(std::format(L"Use Adapater:{}\n", adapterDesc.Description));
      break;
    }
    useAdapter = nullptr; // ソフトウェアアダプタの場合は見なかったことにする
  }
  // 適切なアダプタが見つからなかったので起動できない
  assert(useAdapter != nullptr);
}

void DirectXCommon::InitializeDevice()
{
  D3D_FEATURE_LEVEL featureLevels[] = {
D3D_FEATURE_LEVEL_12_2, D3D_FEATURE_LEVEL_12_1, D3D_FEATURE_LEVEL_12_0
  };
  const char* featureLevelStrings[] = { "12.2", "12.1", "12.0" };
  // 高い順に生成できるか試していく
  for (size_t i = 0; i < _countof(featureLevels); ++i) {
    // 採用したアダプターでデバイスを生成
    HRESULT hr = D3D12CreateDevice(useAdapter, featureLevels[i], IID_PPV_ARGS(&device));
    // 指定した機能レベルでデバイスが生成できたかを確認
    if (SUCCEEDED(hr)) {
      // 生成できたのでログ出力を行ってループを抜ける
      //Omory::Debug::Log(std::format("FeatureLevel : {}\n", featureLevelStrings[i]));
      break;
    }
  }
  // デバイスの生成がうまくいかなかったので起動できない
  assert(device != nullptr);

  }

  void DirectXCommon::InitializeInfoQueue()
  {
#ifdef _DEBUG
    ID3D12InfoQueue* infoQueue = nullptr;
    if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&infoQueue)))) {
      // ヤバイエラー時に止まる
      infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
      // エラー時に止まる
      infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
      // 警告時に止まる
      //infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);

      // 抑制するメッセージのID
      D3D12_MESSAGE_ID denyIds[] = {
        // Windows11でのDXGIデバッグレイヤーとDX12デバッグレイヤーの相互作用バグによるエラーメッセージ
        // https://stackoverflow.com/questions/69805245/directx-12-application-is-crashing-in-windows-11
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
      };
      // 抑制するレベル
      D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
      D3D12_INFO_QUEUE_FILTER filter{};
      filter.DenyList.NumIDs = _countof(denyIds);
      filter.DenyList.pIDList = denyIds;
      filter.DenyList.NumSeverities = _countof(severities);
      filter.DenyList.pSeverityList = severities;
      // 指定したメッセージの表示を抑制する
      infoQueue->PushStorageFilter(&filter);

      // 解放
      infoQueue->Release();
    }
#endif


  }

  void DirectXCommon::InitializeCommandQueue()
  {
    HRESULT hr = device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
    // コマンドキューの生成がうまくいかなかったので起動できない
    assert(SUCCEEDED(hr));

  }

  void DirectXCommon::InitializeCommandAllocator()
  {
    HRESULT hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
    // コマンドアロケータの生成がうまくいかなかったので起動できない
    assert(SUCCEEDED(hr));
  }

  void DirectXCommon::InitializeCommandList()
  {
    HRESULT hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, nullptr, IID_PPV_ARGS(&commandList));
    // コマンドリストの生成がうまくいかなかったので起動できない
    assert(SUCCEEDED(hr));
  }

  void DirectXCommon::InitializeFence()
  {
    uint64_t fenceValue = 0;
    HRESULT hr = device->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
    assert(SUCCEEDED(hr));
    // FenceのSignalを待つためのイベントを作成する
    fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    assert(fenceEvent != nullptr);
  }

  void DirectXCommon::InitializeCompiler()
  {

    HRESULT hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils));
    assert(SUCCEEDED(hr));
    hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler));
    assert(SUCCEEDED(hr));

    // 現時点でincludeはしないが、includeに対応するための設定を行っておく
    //IDxcIncludeHandler* includeHandler = nullptr;
    hr = dxcUtils->CreateDefaultIncludeHandler(&includeHandler);
    assert(SUCCEEDED(hr));
  }

  void DirectXCommon::CreateRootSignature()
  {
    descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    // RootParameter作成。複数設定できるので配列。今回は結果1つだけなので長さ1の配列
    D3D12_ROOT_PARAMETER rootParameters[3] = {};
    rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;    // CBVを使う
    rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;   // PixelShaderで使う
    rootParameters[0].Descriptor.ShaderRegister = 0;    // レジスタ番号0を使う
    rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;    // CBVを使う
    rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;   // VertexShaderで使う
    rootParameters[1].Descriptor.ShaderRegister = 0;    // レジスタ番号0を使う


    D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
    descriptorRange[0].BaseShaderRegister = 0;  // 0から始まる
    descriptorRange[0].NumDescriptors = 1;  // 数は1つ
    descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV; // SRVを使う
    descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND; // Offsetを自動計算

    rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // DescriptorTableを使う
    rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
    rootParameters[2].DescriptorTable.pDescriptorRanges = descriptorRange;  // Tableの中身の配列を指定
    rootParameters[2].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange); // Tableで利用する数

    D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
    staticSamplers[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR; // バイリニアフィルタ
    staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;   // 0~1の範囲外をリピート
    staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER; // 比較しない
    staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;   // ありったけのMipmapを使う
    staticSamplers[0].ShaderRegister = 0;   // レジスタ番号0を使う
    staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
    descriptionRootSignature.pStaticSamplers = staticSamplers;
    descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);

    descriptionRootSignature.pParameters = rootParameters;  // ルートパラメータ配列へのポインタ
    descriptionRootSignature.NumParameters = _countof(rootParameters);  // 配列の長さ


  }

  void DirectXCommon::PreRenderer()
  {

    float onePixel = 2.f / 512.f;
    float texSize = 512;
    float sizes[] = {
      texSize * onePixel / 1.f,
      texSize * onePixel / 2.f,
      texSize * onePixel / 4.f,
      texSize * onePixel / 8.f,
      texSize * onePixel / 16.f,
      texSize * onePixel / 32.f,
      texSize * onePixel / 64.f,
      texSize * onePixel / 128.f,
      texSize * onePixel / 256.f,
      texSize * onePixel / 512.f,
    };

    for (int i = 0; i < planeNum; i++)
    {
      planes[i] = { { 1 - sizes[i], 1 - sizes[i] },{ sizes[i], sizes[i]} };
    }
    planeNum = sizeof(planes) / sizeof(planes[0]);
    vertexNum = 3 * 2 * planeNum;
    CreateVertexResource(vertexNum);
  }

  void DirectXCommon::CreateVertexResource(int vertexNum)
  {
    // 頂点リソース用のヒープの設定(関数化)
    vertexResource = CreateBufferResource(sizeof(VertexData) * vertexNum);

    // 頂点バッファビューを作成する
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
    // リソースの先頭のアドレスから使う
    vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
    // 使用するリソースのサイズは頂点3つ分のサイズ
    vertexBufferView.SizeInBytes = sizeof(VertexData) * vertexNum;
    // 1頂点あたりのサイズ
    vertexBufferView.StrideInBytes = sizeof(VertexData);

    // 書き込むためのアドレスを取得
    vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
  }

  void DirectXCommon::Renderer()
  {

    VertexData* vertexes = new VertexData[vertexNum];
    for (int i = 0; i < planeNum; i++)
    {

      float w = planes[i].size.x;
      float h = planes[i].size.y;
      float l = planes[i].position.x;
      float b = planes[i].position.y;
      float r = l + w;
      float t = b + h;

      vertexes[i * 6 + 0] = { { l, b, 0.0f, 1.0f },{ 0.0f, 1.0f } };
      vertexes[i * 6 + 1] = { { l, t, 0.0f, 1.0f },{ 0.0f, 0.0f } };
      vertexes[i * 6 + 2] = { { r, b, 0.0f, 1.0f },{ 1.0f, 1.0f } };

      vertexes[i * 6 + 3] = { { l, t, 0.0f, 1.0f },{ 0.0f, 0.0f } };
      vertexes[i * 6 + 4] = { { r, t, 0.0f, 1.0f },{ 1.0f, 0.0f } };
      vertexes[i * 6 + 5] = { { r, b, 0.0f, 1.0f },{ 1.0f, 1.0f } };
      for (int v = 0; v < vertexNum; v++)
      {
        vertexData[v].position = vertexes[v].position;
        vertexData[v].texcoord = vertexes[v].texcoord;
      }

      delete[] vertexes;

    }
  }
  void DirectXCommon::PostRenderer()
  {
    // コマンドリストの内容を確定させる。すべてのコマンドを積んでからCloseすること
    HRESULT hr = commandList->Close();
    assert(SUCCEEDED(hr));

    // GPUにコマンドリストの実行を行わせる
    commandLists.emplace_back(commandList);
    ID3D12CommandList* cmdLists[] = { commandLists[0] };
    commandQueue->ExecuteCommandLists(1, cmdLists);
    // GPUとOSに画面の交換を行うよう通知する
    swapChain->Present(1, 0);

    // Fenceの値を更新
    fenceValue++;
    // GPUがここまでたどり着いたときに、Fenceの値を指定した値に代入するようにSignalを送る
    commandQueue->Signal(fence, fenceValue);

    // Fenceの値が指定したSignal値にたどり着いているか確認する
    // GetCompletedValueの初期値はFence作成時に渡した初期値
    if (fence->GetCompletedValue() < fenceValue)
    {
      // 指定したSignalにたどりついていないので、たどり着くまで待つようにイベントを設定する
      fence->SetEventOnCompletion(fenceValue, fenceEvent);
      // イベント待つ
      WaitForSingleObject(fenceEvent, INFINITE);
    }

  // 次のフレーム用のコマンドリストを準備
  hr = commandAllocator->Reset();
  assert(SUCCEEDED(hr));
  hr = commandList->Reset(commandAllocator, nullptr);
  assert(SUCCEEDED(hr));
}

  IDxcBlob* DirectXCommon::CompileShader(const std::wstring& filePath, const wchar_t* profile, IDxcUtils* dxcUtils, IDxcCompiler3* dxcCompiler, IDxcIncludeHandler* includeHandler)
  {
    // ここの中身をこの後書いていく
    // 1. hlslファイルを読む
    // これからシェーダーをコンパイルする旨をログに出す
    //Omory::Debug::Log(ConvertString(std::format(L"Begin CompileShader, path:{}, profile:{}\n", filePath, profile)));
    // hlslファイルを読む
    IDxcBlobEncoding* shaderSource = nullptr;
    HRESULT hr = dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource);
    // 読めなかったら止める
    assert(SUCCEEDED(hr));
    // 読み込んだファイルの内容を設定する
    DxcBuffer shaderSourceBuffer;
    shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
    shaderSourceBuffer.Size = shaderSource->GetBufferSize();
    shaderSourceBuffer.Encoding = DXC_CP_UTF8; // UTF8の文字コードであることを通知


    // 2. Compileする
    LPCWSTR arguments[] = {
      filePath.c_str(), // コンパイル対象のhlslファイル名
      L"-E", L"main", // エントリーポイントの指定。基本的にmain以外にはしない
      L"-T", profile, // ShaderProfileの設定
      L"-Zi", L"-Qembed_debug",   // デバッグ用の情報を埋め込む
      L"-Od",     // 最適化を外しておく
      L"-Zpr",    // メモリレイアウトは行優先
    };
    // 実際にShaderをコンパイルする
    IDxcResult* shaderResult = nullptr;
    hr = dxcCompiler->Compile(
      &shaderSourceBuffer,    // 読み込んだファイル
      arguments,              // コンパイルオプション
      _countof(arguments),    // コンパイルオプションの数
      includeHandler,         // includeが含まれた諸々
      IID_PPV_ARGS(&shaderResult) // コンパイル結果
    );
    // コンパイルエラーではなくdxcが起動できないなど致命的な状況
    assert(SUCCEEDED(hr));


    // 3. 警告・エラーがでていないか確認する
    // 警告・エラーが出てたらログに出して止める
    IDxcBlobUtf8* shaderError = nullptr;
    shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);
    if (shaderError != nullptr && shaderError->GetStringLength() != 0) {
      //Omory::Debug::Log(shaderError->GetStringPointer());
      // 警告・エラーダメゼッタイ
      assert(false);
    }


    // 4. Compile結果を受け取って返す
    // コンパイル結果から実行用のバイナリ部分を取得
    IDxcBlob* shaderBlob = nullptr;
    hr = shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
    assert(SUCCEEDED(hr));
    // 成功したログを出す
    //Omory::Debug::Log(ConvertString(std::format(L"Compile Succeeded, path:{}, profile:{}\n", filePath, profile)));
    // もう使わないリソースを解放
    shaderSource->Release();
    shaderResult->Release();
    // 実行用のバイナリを返却
    return shaderBlob;
  }

  void DirectXCommon::CompileShaders()
  {
    // マテリアル用のリソースを作る。今回はcolor1つ分のサイズを用意する
    ID3D12Resource* materialResource = CreateBufferResource(sizeof(Vector4));
    // マテリアルにデータを書き込む
    Vector4* materialData = nullptr;
    // 書き込むためのアドレスを取得
    materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
    // テクスチャの色そのものということで白を書き込む
    *materialData = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

    // WVP用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
    ID3D12Resource* wvpResource = CreateBufferResource(sizeof(Matrix4x4));
    // データを書き込む
    Matrix4x4* wvpData = nullptr;
    // 書き込むためのアドレスを取得
    wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));
    // 単位行列を書きこんでおく
    *wvpData = Matrix4x4::Identity();

    // シリアライズしてバイナリにする
    ID3DBlob* signatureBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;
    HRESULT hr = D3D12SerializeRootSignature(&descriptionRootSignature, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
    if (FAILED(hr)) {
      //Omory::Debug::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
      assert(false);
    }
    // バイナリを元に生成
    hr = device->CreateRootSignature(0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
    assert(SUCCEEDED(hr));

    // InputLayout
    D3D12_INPUT_ELEMENT_DESC inputElementDescs[2] = {};
    inputElementDescs[0].SemanticName = "POSITION";
    inputElementDescs[0].SemanticIndex = 0;
    inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
    inputElementDescs[1].SemanticName = "TEXCOORD";
    inputElementDescs[1].SemanticIndex = 0;
    inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
    inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
    inputLayoutDesc.pInputElementDescs = inputElementDescs;
    inputLayoutDesc.NumElements = _countof(inputElementDescs);



    // BlendStateの設定
    // すべての色要素を書き込む
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

    // RasiterzerStateの設定
    // 裏面（時計回り）を表示しない
    rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
    // 三角形の中を塗りつぶす
    rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

    // Shaderをコンパイルする
    IDxcBlob* vertexShaderBlob = CompileShader(L"./Resources/Shader/Object3D.VS.hlsl", L"vs_6_0", dxcUtils, dxcCompiler, includeHandler);
    assert(vertexShaderBlob != nullptr);

    IDxcBlob* pixelShaderBlob = CompileShader(L"./Resources/Shader/Object3D.PS.hlsl", L"ps_6_0", dxcUtils, dxcCompiler, includeHandler);
    assert(pixelShaderBlob != nullptr);

  }

  ID3D12Resource* DirectXCommon::CreateBufferResource(size_t sizeInBytes)
  {
    // 頂点リソース用のヒープの設定
    D3D12_HEAP_PROPERTIES uploadHeapProperties{};
    uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;// UploadHeapを使う
    // 頂点リソースの設定
    D3D12_RESOURCE_DESC resourceDesc{};
    // バッファリソース。テクスチャの場合はまた別の設定をする
    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resourceDesc.Width = sizeInBytes;// リソースのサイズ。
    // バッファの場合はこれらは1にする決まり
    resourceDesc.Height = 1;
    resourceDesc.DepthOrArraySize = 1;
    resourceDesc.MipLevels = 1;
    resourceDesc.SampleDesc.Count = 1;
    // バッファの場合はこれにする決まり
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    // 実際に頂点リソースを作る
    ID3D12Resource* resource = nullptr;
    HRESULT hr = device->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&resource));
    assert(SUCCEEDED(hr));
    return resource;
  }

  void DirectXCommon::CreateGraphicsPipelineStateDesc()
  {
    D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
    graphicsPipelineStateDesc.pRootSignature = rootSignature;// RootSignature
    graphicsPipelineStateDesc.InputLayout = inputLayoutDesc;// InputLayout
    graphicsPipelineStateDesc.VS = { vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize() };// VertexShader
    graphicsPipelineStateDesc.PS = { pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize() };// PixelShader
    graphicsPipelineStateDesc.BlendState = blendDesc;// BlendState
    graphicsPipelineStateDesc.RasterizerState = rasterizerDesc;// RasterizerState
    // 書き込むRTVの情報
    graphicsPipelineStateDesc.NumRenderTargets = 1;
    graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    // 利用するトポロジ（形状）のタイプ。三角形
    graphicsPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    // どのように画面に色を打ち込むかの設定（気にしなくて良い）
    graphicsPipelineStateDesc.SampleDesc.Count = 1;
    graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
    // 実際に生成
    ID3D12PipelineState* graphicsPipelineState = nullptr;

    HRESULT hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc, IID_PPV_ARGS(&graphicsPipelineState));
    assert(SUCCEEDED(hr));
  }
}