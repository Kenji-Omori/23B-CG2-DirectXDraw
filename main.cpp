
#include <cstdint>
#include <string>
#include <format>
#include <dxgidebug.h>
#include <dxcapi.h>

#include <Core/Window.h>

#include <Core/Type/Vector2.h>
#include <Core/Type/Vector4.h>
#include <Core/Type/Matrix4x4.h>

#include <Core/TextureConverter.h>
#include <Core/DirectXCommon.h>



#include "Externals/imgui/imgui.h"
#include "Externals/imgui/imgui_impl_dx12.h"
#include "Externals/imgui/imgui_impl_win32.h"

#include "Externals/DirectXTex/DirectXTex.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")










//IDxcBlob* CompileShader(
//  // CompilerするShaderファイルへのパス
//  const std::wstring& filePath,
//  // Compilerに使用するProfile
//  const wchar_t* profile,
//  // 初期化で生成したものを3つ
//  IDxcUtils* dxcUtils,
//  IDxcCompiler3* dxcCompiler,
//  IDxcIncludeHandler* includeHandler)
//{
//  // ここの中身をこの後書いていく
//  // 1. hlslファイルを読む
//  // これからシェーダーをコンパイルする旨をログに出す
//  //Omory::Debug::Log(ConvertString(std::format(L"Begin CompileShader, path:{}, profile:{}\n", filePath, profile)));
//  // hlslファイルを読む
//  IDxcBlobEncoding* shaderSource = nullptr;
//  HRESULT hr = dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource);
//  // 読めなかったら止める
//  assert(SUCCEEDED(hr));
//  // 読み込んだファイルの内容を設定する
//  DxcBuffer shaderSourceBuffer;
//  shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
//  shaderSourceBuffer.Size = shaderSource->GetBufferSize();
//  shaderSourceBuffer.Encoding = DXC_CP_UTF8; // UTF8の文字コードであることを通知
//
//
//  // 2. Compileする
//  LPCWSTR arguments[] = {
//    filePath.c_str(), // コンパイル対象のhlslファイル名
//    L"-E", L"main", // エントリーポイントの指定。基本的にmain以外にはしない
//    L"-T", profile, // ShaderProfileの設定
//    L"-Zi", L"-Qembed_debug",   // デバッグ用の情報を埋め込む
//    L"-Od",     // 最適化を外しておく
//    L"-Zpr",    // メモリレイアウトは行優先
//  };
//  // 実際にShaderをコンパイルする
//  IDxcResult* shaderResult = nullptr;
//  hr = dxcCompiler->Compile(
//    &shaderSourceBuffer,    // 読み込んだファイル
//    arguments,              // コンパイルオプション
//    _countof(arguments),    // コンパイルオプションの数
//    includeHandler,         // includeが含まれた諸々
//    IID_PPV_ARGS(&shaderResult) // コンパイル結果
//  );
//  // コンパイルエラーではなくdxcが起動できないなど致命的な状況
//  assert(SUCCEEDED(hr));
//
//
//  // 3. 警告・エラーがでていないか確認する
//  // 警告・エラーが出てたらログに出して止める
//  IDxcBlobUtf8* shaderError = nullptr;
//  shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);
//  if (shaderError != nullptr && shaderError->GetStringLength() != 0) {
//    //Omory::Debug::Log(shaderError->GetStringPointer());
//    // 警告・エラーダメゼッタイ
//    assert(false);
//  }
//
//
//  // 4. Compile結果を受け取って返す
//  // コンパイル結果から実行用のバイナリ部分を取得
//  IDxcBlob* shaderBlob = nullptr;
//  hr = shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
//  assert(SUCCEEDED(hr));
//  // 成功したログを出す
//  //Omory::Debug::Log(ConvertString(std::format(L"Compile Succeeded, path:{}, profile:{}\n", filePath, profile)));
//  // もう使わないリソースを解放
//  shaderSource->Release();
//  shaderResult->Release();
//  // 実行用のバイナリを返却
//  return shaderBlob;
//
//
//}

//ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInBytes)
//{
//  // 頂点リソース用のヒープの設定
//  D3D12_HEAP_PROPERTIES uploadHeapProperties{};
//  uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;// UploadHeapを使う
//  // 頂点リソースの設定
//  D3D12_RESOURCE_DESC resourceDesc{};
//  // バッファリソース。テクスチャの場合はまた別の設定をする
//  resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
//  resourceDesc.Width = sizeInBytes;// リソースのサイズ。
//  // バッファの場合はこれらは1にする決まり
//  resourceDesc.Height = 1;
//  resourceDesc.DepthOrArraySize = 1;
//  resourceDesc.MipLevels = 1;
//  resourceDesc.SampleDesc.Count = 1;
//  // バッファの場合はこれにする決まり
//  resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
//  // 実際に頂点リソースを作る
//  ID3D12Resource* resource = nullptr;
//  HRESULT hr = device->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&resource));
//  assert(SUCCEEDED(hr));
//  return resource;
//
//}

ID3D12DescriptorHeap* CreateDescriptorHeap(
  ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible)
{
  ID3D12DescriptorHeap* descriptorHeap = nullptr;
  D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc{};
  descriptorHeapDesc.Type = heapType;
  descriptorHeapDesc.NumDescriptors = numDescriptors;
  descriptorHeapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
  HRESULT hr = device->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&descriptorHeap));
  assert(SUCCEEDED(hr));
  return descriptorHeap;
}

//DirectX::ScratchImage LoadTexture(const std::string& filePath)
//{
//  
//
//  // テクスチャファイルを読んでプログラムで扱えるようにする
//  DirectX::ScratchImage image{};
//  std::wstring filePathW = ConvertString(filePath);
//  HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
//  assert(SUCCEEDED(hr));
//
//  // ミップマップの作成
//  DirectX::ScratchImage mipImages{};
//  hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
//  assert(SUCCEEDED(hr));
//
//  // ミップマップ付きのデータを返す
//  return mipImages;
//}

ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata)
{
  // 1. metadataを基にResourceの設定
  // // metadataを基にResourceの設定
  D3D12_RESOURCE_DESC resourceDesc{};
  resourceDesc.Width = UINT(metadata.width); // Textureの幅
  resourceDesc.Height = UINT(metadata.height); // Textureの高さ
  resourceDesc.MipLevels = UINT16(metadata.mipLevels); // mipmapの数
  resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize); // 奥行き or 配列Textureの配列数
  resourceDesc.Format = metadata.format; // TextureのFormat
  resourceDesc.SampleDesc.Count = 1; // サンプリングカウント。1固定。
  resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension); // Textureの次元数。普段使っているのは2次元



  // 2. 利用するHeapの設定
  // 利用するHeapの設定。非常に特殊な運用。02_04exで一般的なケース版がある
  D3D12_HEAP_PROPERTIES heapProperties{};
  heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM; // 細かい設定を行う
  heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK; // WriteBackポリシーでCPUアクセス可能
  heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0; //　プロセッサの近くに配置

  // 3. Resourceを生成する
  // Resourceの生成
  ID3D12Resource* resource = nullptr;
  HRESULT hr = device->CreateCommittedResource(
    &heapProperties, // Heapの設定
    D3D12_HEAP_FLAG_NONE, // Heapの特殊な設定。特になし。
    &resourceDesc,  // Resourceの設定
    D3D12_RESOURCE_STATE_GENERIC_READ,  // 初回のResourceState。Textureは基本読むだけ
    nullptr, // Clear最適値。使わないのでnullptr
    IID_PPV_ARGS(&resource)); // 作成するResourceポインタへのポインタ
  assert(SUCCEEDED(hr));
  return resource;

}

void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages)
{
  // Meta情報を取得
  const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
  // 全MipMapについて
  for (size_t mipLevel = 0; mipLevel < metadata.mipLevels; ++mipLevel) {
    // MipMapLevelを指定して各Imageを取得
    const DirectX::Image* img = mipImages.GetImage(mipLevel, 0, 0);
    // Textureに転送
    HRESULT hr = texture->WriteToSubresource(
      UINT(mipLevel),
      nullptr,              // 全領域へコピー
      img->pixels,          // 元データアドレス
      UINT(img->rowPitch),  // 1ラインサイズ
      UINT(img->slicePitch) // 1枚サイズ
    );
    assert(SUCCEEDED(hr));
  }
}










int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

  CoInitializeEx(0, COINIT_MULTITHREADED);


  OutputDebugStringA("Hello, DirectX!\n");
  Core::Window window;
  window.Initialize();
  //WNDCLASS wc{};
  //wc.lpfnWndProc = WindowProc;
  //wc.lpszClassName = L"CG2WindowClass";
  //wc.hInstance = GetModuleHandle(nullptr);
  //wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  //RegisterClass(&wc);


  //const int32_t kClientWidth = 720;
  //const int32_t kClientHeight = 720;
  //RECT wrc = { 0,0,kClientWidth, kClientHeight };
  //AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU, false);

  //HWND hwnd = CreateWindow(
  //  wc.lpszClassName,
  //  L"CG2",
  //  WS_OVERLAPPEDWINDOW, 
  //  CW_USEDEFAULT,
  //  CW_USEDEFAULT,
  //  wrc.right - wrc.left,
  //  wrc.bottom - wrc.top,
  //  nullptr, 
  //  nullptr,
  //  wc.hInstance,
  //  nullptr
  //);


//#ifdef _DEBUG
//  ID3D12Debug1* debugController = nullptr;
//  if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
//    // デバッグレイヤーを有効化する
//    debugController->EnableDebugLayer();
//    // さらにGPU側でもチェックを行うようにする
//    debugController->SetEnableGPUBasedValidation(TRUE);
//  }
//
//#endif

  window.Show();
  HRESULT hr;
  DirectXCommon common;
  common.Initialize();
  //  ShowWindow(hwnd, SW_SHOW);


  //  //Setup DirectX12
  //IDXGIFactory7* dxgiFactory = nullptr;
  //HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
  //assert(SUCCEEDED(hr));

  //IDXGIAdapter4* useAdapter = nullptr;
  //// 良い順にアダプタを頼む
  //for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&useAdapter)) != DXGI_ERROR_NOT_FOUND; ++i) {
  //  // アダプターの情報を取得する
  //  DXGI_ADAPTER_DESC3 adapterDesc{};
  //  hr = useAdapter->GetDesc3(&adapterDesc);
  //  assert(SUCCEEDED(hr)); // 取得できないのは一大事
  //  // ソフトウェアアダプタでなければ採用！
  //  if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
  //    // 採用したアダプタの情報をログに出力。wstringの方なので注意
  //    Log(std::format(L"Use Adapater:{}\n", adapterDesc.Description));
  //    break;
  //  }
  //  useAdapter = nullptr; // ソフトウェアアダプタの場合は見なかったことにする
  //}
  //// 適切なアダプタが見つからなかったので起動できない
  //assert(useAdapter != nullptr);

  //ID3D12Device* device = nullptr;
  // 機能レベルとログ出力用の文字列
  //D3D_FEATURE_LEVEL featureLevels[] = {
  //  D3D_FEATURE_LEVEL_12_2, D3D_FEATURE_LEVEL_12_1, D3D_FEATURE_LEVEL_12_0
  //};
  //const char* featureLevelStrings[] = { "12.2", "12.1", "12.0" };
  //// 高い順に生成できるか試していく
  //for (size_t i = 0; i < _countof(featureLevels); ++i) {
  //  // 採用したアダプターでデバイスを生成
  //  hr = D3D12CreateDevice(useAdapter, featureLevels[i], IID_PPV_ARGS(&device));
  //  // 指定した機能レベルでデバイスが生成できたかを確認
  //  if (SUCCEEDED(hr)) {
  //    // 生成できたのでログ出力を行ってループを抜ける
  //    Log(std::format("FeatureLevel : {}\n", featureLevelStrings[i]));
  //    break;
  //  }
  //}
  //// デバイスの生成がうまくいかなかったので起動できない
  //assert(device != nullptr);

  //Omory::Debug::Log("Complete create D3D12Device!!!\n");// 初期化完了のログをだす


  ID3D12Device* device = common.GetDevice();

  //コマンドキューを生成する
  //ID3D12CommandQueue* commandQueue = nullptr;
  //D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
  //hr = common.GetDevice()->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
  //// コマンドキューの生成がうまくいかなかったので起動できない
  //assert(SUCCEEDED(hr));

  // コマンドアロケータを生成する
  //ID3D12CommandAllocator* commandAllocator = nullptr;
  //hr = common.GetDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
  //// コマンドアロケータの生成がうまくいかなかったので起動できない
  //assert(SUCCEEDED(hr));

  // コマンドリストを生成する
  //ID3D12GraphicsCommandList* commandList = nullptr;
  //hr = common.GetDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, nullptr, IID_PPV_ARGS(&commandList));
  //// コマンドリストの生成がうまくいかなかったので起動できない
  //assert(SUCCEEDED(hr));

  // 初期値0でFenceを作る
  //ID3D12Fence* fence = nullptr;
  //uint64_t fenceValue = 0;
  //hr = device->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
  //assert(SUCCEEDED(hr));

  // FenceのSignalを待つためのイベントを作成する
  //HANDLE fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  //assert(fenceEvent != nullptr);

  // dxcCompilerを初期化
  //IDxcUtils* dxcUtils = nullptr;
  //IDxcCompiler3* dxcCompiler = nullptr;
  //hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils));
  //assert(SUCCEEDED(hr));
  //hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler));
  //assert(SUCCEEDED(hr));

  //// 現時点でincludeはしないが、includeに対応するための設定を行っておく
  //IDxcIncludeHandler* includeHandler = nullptr;
  //hr = dxcUtils->CreateDefaultIncludeHandler(&includeHandler);
  //assert(SUCCEEDED(hr));

  // RootSignature作成
  //D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
  //descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
  //// RootParameter作成。複数設定できるので配列。今回は結果1つだけなので長さ1の配列
  //D3D12_ROOT_PARAMETER rootParameters[3] = {};
  //rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;    // CBVを使う
  //rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;   // PixelShaderで使う
  //rootParameters[0].Descriptor.ShaderRegister = 0;    // レジスタ番号0を使う
  //rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;    // CBVを使う
  //rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;   // VertexShaderで使う
  //rootParameters[1].Descriptor.ShaderRegister = 0;    // レジスタ番号0を使う


  //D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
  //descriptorRange[0].BaseShaderRegister = 0;  // 0から始まる
  //descriptorRange[0].NumDescriptors = 1;  // 数は1つ
  //descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV; // SRVを使う
  //descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND; // Offsetを自動計算

  //rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // DescriptorTableを使う
  //rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
  //rootParameters[2].DescriptorTable.pDescriptorRanges = descriptorRange;  // Tableの中身の配列を指定
  //rootParameters[2].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange); // Tableで利用する数

  //D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
  //staticSamplers[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR; // バイリニアフィルタ
  //staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;   // 0~1の範囲外をリピート
  //staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  //staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  //staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER; // 比較しない
  //staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;   // ありったけのMipmapを使う
  //staticSamplers[0].ShaderRegister = 0;   // レジスタ番号0を使う
  //staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
  //descriptionRootSignature.pStaticSamplers = staticSamplers;
  //descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);








  //descriptionRootSignature.pParameters = rootParameters;  // ルートパラメータ配列へのポインタ
  //descriptionRootSignature.NumParameters = _countof(rootParameters);  // 配列の長さ

  //// マテリアル用のリソースを作る。今回はcolor1つ分のサイズを用意する
  //ID3D12Resource* materialResource = CreateBufferResource(device, sizeof(Vector4));
  //// マテリアルにデータを書き込む
  //Vector4* materialData = nullptr;
  //// 書き込むためのアドレスを取得
  //materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
  //// テクスチャの色そのものということで白を書き込む
  //*materialData = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

  //// WVP用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
  //ID3D12Resource* wvpResource = CreateBufferResource(device, sizeof(Matrix4x4));
  //// データを書き込む
  //Matrix4x4* wvpData = nullptr;
  //// 書き込むためのアドレスを取得
  //wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));
  //// 単位行列を書きこんでおく
  //*wvpData = Matrix4x4::Identity();

  //// シリアライズしてバイナリにする
  //ID3DBlob* signatureBlob = nullptr;
  //ID3DBlob* errorBlob = nullptr;
  //hr = D3D12SerializeRootSignature(&descriptionRootSignature, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
  //if (FAILED(hr)) {
  //  //Omory::Debug::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
  //  assert(false);
  //}
  //// バイナリを元に生成
  //ID3D12RootSignature* rootSignature = nullptr;
  //hr = device->CreateRootSignature(0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
  //assert(SUCCEEDED(hr));

  //// InputLayout
  //D3D12_INPUT_ELEMENT_DESC inputElementDescs[2] = {};
  //inputElementDescs[0].SemanticName = "POSITION";
  //inputElementDescs[0].SemanticIndex = 0;
  //inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
  //inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
  //inputElementDescs[1].SemanticName = "TEXCOORD";
  //inputElementDescs[1].SemanticIndex = 0;
  //inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
  //inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
  //D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
  //inputLayoutDesc.pInputElementDescs = inputElementDescs;
  //inputLayoutDesc.NumElements = _countof(inputElementDescs);



  //// BlendStateの設定
  //D3D12_BLEND_DESC blendDesc{};
  //// すべての色要素を書き込む
  //blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

  //// RasiterzerStateの設定
  //D3D12_RASTERIZER_DESC rasterizerDesc{};
  //// 裏面（時計回り）を表示しない
  //rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
  //// 三角形の中を塗りつぶす
  //rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

  //// Shaderをコンパイルする
  //IDxcBlob* vertexShaderBlob = CompileShader(L"./Resources/Shader/Object3D.VS.hlsl", L"vs_6_0", dxcUtils, dxcCompiler, includeHandler);
  //assert(vertexShaderBlob != nullptr);

  //IDxcBlob* pixelShaderBlob = CompileShader(L"./Resources/Shader/Object3D.PS.hlsl", L"ps_6_0", dxcUtils, dxcCompiler, includeHandler);
  //assert(pixelShaderBlob != nullptr);

  //D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
  //graphicsPipelineStateDesc.pRootSignature = rootSignature;// RootSignature
  //graphicsPipelineStateDesc.InputLayout = inputLayoutDesc;// InputLayout
  //graphicsPipelineStateDesc.VS = { vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize() };// VertexShader
  //graphicsPipelineStateDesc.PS = { pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize() };// PixelShader
  //graphicsPipelineStateDesc.BlendState = blendDesc;// BlendState
  //graphicsPipelineStateDesc.RasterizerState = rasterizerDesc;// RasterizerState
  //// 書き込むRTVの情報
  //graphicsPipelineStateDesc.NumRenderTargets = 1;
  //graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
  //// 利用するトポロジ（形状）のタイプ。三角形
  //graphicsPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
  //// どのように画面に色を打ち込むかの設定（気にしなくて良い）
  //graphicsPipelineStateDesc.SampleDesc.Count = 1;
  //graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
  //// 実際に生成
  //ID3D12PipelineState* graphicsPipelineState = nullptr;

  //hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc, IID_PPV_ARGS(&graphicsPipelineState));
  //assert(SUCCEEDED(hr));

  //struct Plane {
  //  Vector2 position;
  //  Vector2 size;
  //};

  //float onePixel = 2.f/512.f;
  //float texSize = 512;
  //float sizes[]={
  //  texSize * onePixel/1.f,
  //  texSize * onePixel/2.f,
  //  texSize * onePixel/4.f,
  //  texSize * onePixel/8.f,
  //  texSize * onePixel/16.f,
  //  texSize * onePixel/32.f,
  //  texSize * onePixel/64.f,
  //  texSize * onePixel/128.f,
  //  texSize * onePixel/256.f,
  //  texSize * onePixel/512.f,
  //};

  //Plane planes[] =
  //{
  //  {{ 1 - sizes[0], 1-sizes[0] },{ sizes[0], sizes[0]}},
  //  {{ 1 - sizes[1], 1-sizes[1] },{ sizes[1], sizes[1]}},
  //  {{ 1 - sizes[2], 1-sizes[2] },{ sizes[2], sizes[2]}},
  //  {{ 1 - sizes[3], 1-sizes[3] },{ sizes[3], sizes[3]}},
  //  {{ 1 - sizes[4], 1-sizes[4] },{ sizes[4], sizes[4]}},
  //  {{ 1 - sizes[5], 1-sizes[5] },{ sizes[5], sizes[5]}},
  //  {{ 1 - sizes[6], 1-sizes[6] },{ sizes[6], sizes[6]}},
  //  {{ 1 - sizes[7], 1-sizes[7] },{ sizes[7], sizes[7]}},
  //  {{ 1 - sizes[8], 1-sizes[8] },{ sizes[8], sizes[8]}},
  //  {{ 1 - sizes[9], 1-sizes[9] },{ sizes[9], sizes[9]}}
  //};


  //int planeNum = sizeof(planes) / sizeof(planes[0]);
  //int vertexNum = 3 * 2 * planeNum;

  // 頂点リソース用のヒープの設定(関数化)
  //ID3D12Resource* vertexResource = CreateBufferResource(device, sizeof(VertexData) * vertexNum);

  //// 頂点バッファビューを作成する
  //D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
  //// リソースの先頭のアドレスから使う
  //vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
  //// 使用するリソースのサイズは頂点3つ分のサイズ
  //vertexBufferView.SizeInBytes = sizeof(VertexData) * vertexNum;
  //// 1頂点あたりのサイズ
  //vertexBufferView.StrideInBytes = sizeof(VertexData);

  //// 頂点リソースにデータを書き込む
  //VertexData* vertexData = nullptr;
  //// 書き込むためのアドレスを取得
  //vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));


 /* VertexData* vertexes = new VertexData[vertexNum];
  for (int i = 0; i < planeNum; i ++)
  {

    float w = planes[i].size.x;
    float h = planes[i].size.y;
    float l = planes[i].position.x;
    float b = planes[i].position.y;
    float r = l + w;
    float t = b + h;

    vertexes[i*6 + 0] = { { l, b, 0.0f, 1.0f },{ 0.0f, 1.0f } };
    vertexes[i*6 + 1] = { { l, t, 0.0f, 1.0f },{ 0.0f, 0.0f } };
    vertexes[i*6 + 2] = { { r, b, 0.0f, 1.0f },{ 1.0f, 1.0f } };

    vertexes[i*6 + 3] = { { l, t, 0.0f, 1.0f },{ 0.0f, 0.0f } };
    vertexes[i*6 + 4] = { { r, t, 0.0f, 1.0f },{ 1.0f, 0.0f } };
    vertexes[i*6 + 5] = { { r, b, 0.0f, 1.0f },{ 1.0f, 1.0f } };*/

    // 左下
    //vertexData[0].position = { -0.5f, -0.5f, 0.0f, 1.0f };
    //vertexData[0].texcoord = { 0.0f, 1.0f };
    //// 上
    //vertexData[1].position = { -0.5f, +0.5f, 0.0f, 1.0f };
    //vertexData[1].texcoord = { 0.0f, 0.0f };
    //// 右下
    //vertexData[2].position = { +0.5f, -0.5f, 0.0f, 1.0f };
    //vertexData[2].texcoord = { 1.0f, 1.0f };

    //// 左下
    //vertexData[3].position = { -0.5f, +0.5f, 0.0f, 1.0f };
    //vertexData[3].texcoord = { 0.0f, 0.0f };
    //// 上
    //vertexData[4].position = { +0.5f, +0.5f, 0.0f, 1.0f };
    //vertexData[4].texcoord = { 1.0f, 0.0f };
    //// 右下
    //vertexData[5].position = { +0.5f, -0.5f, 0.0f, 1.0f };
    //vertexData[5].texcoord = { 1.0f, 1.0f };
  //}
  //for (int v = 0; v < vertexNum; v++)
  //{
  //  vertexData[v].position = vertexes[v].position;
  //  vertexData[v].texcoord = vertexes[v].texcoord;
  //}

  //delete[] vertexes;

  // ビューポート
  D3D12_VIEWPORT viewport{};
  // クライアント領域のサイズと一緒にして画面全体に表示
  viewport.Width = FLOAT(window.GetWidth());
  viewport.Height = FLOAT(window.GetHeight());
  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;
  viewport.MinDepth = 0.0f;
  viewport.MaxDepth = 1.0f;

  // シザー矩形
  D3D12_RECT scissorRect{};
  // 基本的にビューポートと同じ矩形が構成されるようにする
  scissorRect.left = 0;
  scissorRect.right = window.GetWidth();
  scissorRect.top = 0;
  scissorRect.bottom = window.GetHeight();

  // スワップチェーンを生成する
  IDXGISwapChain4* swapChain = nullptr;
  DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
  swapChainDesc.Width = window.GetWidth();     // 画面の幅。ウィンドウのクライアント領域を同じものにしておく
  swapChainDesc.Height = window.GetHeight();   // 画面の高さ。ウィンドウのクライアント領域を同じものにしておく
  swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // 色の形式
  swapChainDesc.SampleDesc.Count = 1; // マルチサンプルしない
  swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 描画のターゲットとして利用する
  swapChainDesc.BufferCount = 2;  // ダブルバッファ
  swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // モニタにうつしたら、中身を破棄
  // コマンドキュー、ウィンドウハンドル、設定を渡して生成する

  hr = common.GetFactory()->CreateSwapChainForHwnd(commandQueue, window.GetWindowHandle(), &swapChainDesc, nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(&swapChain));
  assert(SUCCEEDED(hr));

  //// ディスクリプタヒープの生成
  //D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptorHeapDesc{};
  //rtvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // レンダーターゲットビュー用
  //rtvDescriptorHeapDesc.NumDescriptors = 2; // ダブルバッファ用に2つ。多くても別に構わない
  //hr = device->CreateDescriptorHeap(&rtvDescriptorHeapDesc, IID_PPV_ARGS(&rtvDescriptorHeap));
  //// ディスクリプタヒープが作れなかったので起動できない
  //assert(SUCCEEDED(hr));

  // RTV用のヒープでディスクリプタの数は2。RTVはShader内で触るものではないので、ShaderVisibleはfalse
  ID3D12DescriptorHeap* rtvDescriptorHeap = CreateDescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 2, false);

  // SRV用のヒープでディスクリプタの数は128。SRVはShader内で触るものなので、ShaderVisibleはtrue
  ID3D12DescriptorHeap* srvDescriptorHeap = CreateDescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 128, true);



  TextureConverter textureConverter;
  // Textureを読んで転送する
  DirectX::ScratchImage mipImages = textureConverter.LoadTexture("./Resources/Texture/uvChecker2.dds");
  const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
  ID3D12Resource* textureResource = CreateTextureResource(device, metadata);
  UploadTextureData(textureResource, mipImages);

  // metaDataを基にSRVの設定
  D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
  srvDesc.Format = metadata.format;
  srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
  srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
  srvDesc.Texture2D.MipLevels = UINT(metadata.mipLevels);

  // SRVを作成するDescriptorHeapの場所を決める
  D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU = srvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
  D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU = srvDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
  // 先頭はImGuiが使っているのでその次を使う
  textureSrvHandleCPU.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
  textureSrvHandleGPU.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
  // SRVの生成
  device->CreateShaderResourceView(textureResource, &srvDesc, textureSrvHandleCPU);


  DirectX::XMFLOAT4;

  // SwapChainからResourceを引っ張ってくる
  ID3D12Resource* swapChainResources[2] = { nullptr };
  hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&swapChainResources[0]));
  // うまく取得できなければ起動できない
  assert(SUCCEEDED(hr));
  hr = swapChain->GetBuffer(1, IID_PPV_ARGS(&swapChainResources[1]));
  assert(SUCCEEDED(hr));

  // RTVの設定
  D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
  rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 出力結果をSRGBに変換して書き込む
  rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D; // 2dテクスチャとして書き込む
  // ディスクリプタの先頭を取得する
  D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle = rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
  // RTVを2つ作るのでディスクリプタを2つ用意
  D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
  // まず1つ目を作る。1つ目は最初のところに作る。作る場所をこちらで指定してあげる必要がある
  rtvHandles[0] = rtvStartHandle;
  device->CreateRenderTargetView(swapChainResources[0], &rtvDesc, rtvHandles[0]);
  // 2つ目のディスクリプタハンドルを得る（自力で）
  rtvHandles[1].ptr = rtvHandles[0].ptr + device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
  // 2つ目を作る
  device->CreateRenderTargetView(swapChainResources[1], &rtvDesc, rtvHandles[1]);





  // これから書き込むバックバッファのインデックスを取得
  UINT backBufferIndex = swapChain->GetCurrentBackBufferIndex();

  // TransitionBarrierの設定
  D3D12_RESOURCE_BARRIER barrier{};
  // 今回のバリアはTransition
  barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  // Noneにしておく
  barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  // バリアを張る対象のリソース。現在のバックバッファに対して行う
  barrier.Transition.pResource = swapChainResources[backBufferIndex];
  // 遷移前（現在）のResourceState
  barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
  // 遷移後のResourceState
  barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
  // TransitionBarrierを張る
  commandList->ResourceBarrier(1, &barrier);




  // 描画先のRTVを設定する
  commandList->OMSetRenderTargets(1, &rtvHandles[backBufferIndex], false, nullptr);
  // 指定した色で画面全体をクリアする
  float clearColor[] = { 0.1f, 0.25f, 0.5f, 1.0f }; // 青っぽい色。RGBAの順       
  commandList->ClearRenderTargetView(rtvHandles[backBufferIndex], clearColor, 0, nullptr);

  // 描画用のDescriptorHeapの設定
  ID3D12DescriptorHeap* descriptorHeaps[] = { srvDescriptorHeap };
  commandList->SetDescriptorHeaps(1, descriptorHeaps);





  commandList->RSSetViewports(1, &viewport);  // Viewportを設定
  commandList->RSSetScissorRects(1, &scissorRect);    // Scirssorを設定
  // RootSignatureを設定。PSOに設定しているけど別途設定が必要
  commandList->SetGraphicsRootSignature(rootSignature);
  commandList->SetPipelineState(graphicsPipelineState);   // PSOを設定
  commandList->IASetVertexBuffers(0, 1, &vertexBufferView);   // VBVを設定
  // 形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
  commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  commandList->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
  // wvp用のCBufferの場所を設定
  commandList->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());

  // SRVのDescriptorTableの先頭を設定。2はrootParameter[2]である。
  commandList->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU);



  // 描画！（DrawCall/ドローコール）。3頂点で1つのインスタンス。インスタンスについては今後
  commandList->DrawInstanced(vertexNum, 1, 0, 0);

  // 実際のcommandListのImGuiの描画コマンドを積む
//  ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList);





  // 今回はRenderTargetからPresentにする
  barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
  barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
  // TransitionBarrierを張る
  commandList->ResourceBarrier(1, &barrier);

//  // コマンドリストの内容を確定させる。すべてのコマンドを積んでからCloseすること
//  hr = commandList->Close();
//  assert(SUCCEEDED(hr));
//
//  // GPUにコマンドリストの実行を行わせる
//  ID3D12CommandList* commandLists[] = { commandList };
//  commandQueue->ExecuteCommandLists(1, commandLists);
//  // GPUとOSに画面の交換を行うよう通知する
//  swapChain->Present(1, 0);
//
//  // Fenceの値を更新
//  fenceValue++;
//  // GPUがここまでたどり着いたときに、Fenceの値を指定した値に代入するようにSignalを送る
//  commandQueue->Signal(fence, fenceValue);
//
//  // Fenceの値が指定したSignal値にたどり着いているか確認する
//// GetCompletedValueの初期値はFence作成時に渡した初期値
//  if (fence->GetCompletedValue() < fenceValue)
//  {
//    // 指定したSignalにたどりついていないので、たどり着くまで待つようにイベントを設定する
//    fence->SetEventOnCompletion(fenceValue, fenceEvent);
//    // イベント待つ
//    WaitForSingleObject(fenceEvent, INFINITE);
//  }



  //// 次のフレーム用のコマンドリストを準備
  //hr = commandAllocator->Reset();
  //assert(SUCCEEDED(hr));
  //hr = commandList->Reset(commandAllocator, nullptr);
  //assert(SUCCEEDED(hr));




  // comment テスト


   


  // ImGuiの初期化。詳細はさして重要ではないので解説は省略する。
  // こういうもんである
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();
  ImGui_ImplWin32_Init(window.GetWindowHandle());
  ImGui_ImplDX12_Init(device,
    swapChainDesc.BufferCount,
    rtvDesc.Format,
    srvDescriptorHeap,
    srvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
    srvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());




  MSG msg{};
  LPSTR preCmd = lpCmdLine;
  LPSTR curCmd = lpCmdLine;
  while (msg.message != WM_QUIT)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
      continue;
    }

    curCmd = lpCmdLine;
    if (strcmp(preCmd, curCmd) != 0)
    {
      printf("cmd:%s", curCmd);
      preCmd = curCmd;
    }

    //ImGui_ImplDX12_NewFrame();
    //ImGui_ImplWin32_NewFrame();
    //ImGui::NewFrame();

    //// 開発用UIの処理。実際に開発用のUIを出す場合はここをゲーム固有の処理に置き換える
    ////ImGui::ShowDemoWindow();

    //// ImGuiの内部コマンドを生成する
    //ImGui::Render();








  }

  CloseHandle(fenceEvent);
  fence->Release();
  rtvDescriptorHeap->Release();

  swapChainResources[0]->Release();
  swapChainResources[1]->Release();
  swapChain->Release();
  materialResource->Release();
  commandList->Release();
  commandAllocator->Release();
  commandQueue->Release();
  common.Release();
//#ifdef _DEBUG
//  debugController->Release();
//#endif
  window.Close();




  // リソースリークチェック
  IDXGIDebug1* debug_;
  if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug_)))) {
    debug_->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
    debug_->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
    debug_->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
    debug_->Release();
  }

  CoUninitialize();
  return 0;
}
