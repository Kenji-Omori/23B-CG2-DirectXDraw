#include "DirectXCommon.h"

#include <dxgidebug.h>
#include <dxcapi.h>
#include <format>
#include <cassert>
#include <Utility/Debug.h>
#include <Utility/Type/Matrix4x4.h>
#include <Utility/Type/Vector4.h>
#include <Utility/Type/VertexData.h>

#include <Core/Window.h>
#include <Core/DirectX12/DirectXAdapter.h>
#include <Core/DirectX12/DirectXCommand.h>
#include <Core/DirectX12/DirectXDevice.h>
#include <Core/DirectX12/DirectXFactory.h>
#include <Core/DirectX12/DirectXFence.h>
#include <Core/DirectX12/DirectXInfoQueue.h>
#include <Core/DirectX12/DirectXSwapChain.h>
#include <Core/DirectX12/DirectXSwapChain.h>
#include <Core/DirectX12/DirectXCommandQueue.h>
#include <Core/DirectX12/DirectXCommandAllocator.h>
#include <Core/DirectX12/DirectXCommandList.h>
#include <Core/DirectX12/DirectXSwapChain.h>
#include <Core/DirectX12/DirectXDescriptorHeapRTV.h>
#include <Core/DirectX12/DirectXDescriptorHeapSRV.h>
#include <Core/DirectX12/DirectXDepthBuffer.h>
#include <Core/DirectX12/DirectXResourceTexture.h>
#include <Core/ImGuiWrap.h>
#include <Core/TimeKeeper.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")




Core::DirectXCommon::DirectXCommon(Window* window)
{
  this->window = window;
  factory = nullptr;
  adapter = nullptr;
  device = nullptr;
  commandAllocator = nullptr;
  commandList = nullptr;
  commandQueue = nullptr;
  fence = nullptr;
  infoQueue = nullptr;
  swapChain = nullptr;
  //resourceTexture = nullptr;
  //rtvDescriptorHeap = nullptr;
  resourceTexture = nullptr;
  depthBuffer = nullptr;
  imgui = nullptr;
}

Core::DirectXCommon::~DirectXCommon()
{
}

void Core::DirectXCommon::Initialize()
{
  // Device
  #ifdef _DEBUG
  Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
  if(SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
  {
    debugController->EnableDebugLayer();
    //debugController->Release();
  }
  #endif

  factory = new DirectXFactory(window);
  adapter = new DirectXAdapter(factory);
  device = new DirectXDevice(adapter);
   
  infoQueue = new DirectXInfoQueue(device);
  commandAllocator = new DirectXCommandAllocator(device);
  commandList = new DirectXCommandList(device, commandAllocator);
  commandQueue = new DirectXCommandQueue(device);

  swapChain = new DirectXSwapChain(device,commandQueue,SWAP_CHAIN_BUFFER_NUM);
  fence = new DirectXFence(device);
  imgui = new ImGuiWrap(device, swapChain);
  timeKeeper = new TimeKeeper();

  Utility::Debug::Log("Complete create D3D12Device!!!\n");// 初期化完了のログをだす
}


void Core::DirectXCommon::Release()
{
  delete(timeKeeper);
  delete(imgui);
  delete(fence);
  delete(swapChain);
  delete(commandQueue);
  delete(commandList);
  delete(commandAllocator);
  delete(device);
  delete(adapter);
  delete(factory);

#ifdef _DEBUG
  //debugController->Release();
#endif
}

void Core::DirectXCommon::Update()
{
  timeKeeper->Update();
  if(!timeKeeper->IsNextFrame()){ return; }
}

void Core::DirectXCommon::Draw()
{
  PreDraw();
  CurDraw();
  PostDraw();
}

#include <Externals/DirectXTex/d3dx12.h>
#include <Externals/imgui/imgui_impl_win32.h>
#include <Externals/imgui/imgui_impl_dx12.h>
#include <d3d12.h>
#include <dxgi1_6.h>

void Core::DirectXCommon::PreDraw()
{
  commandList->SetResourceBarrierWriteMode(swapChain);
  swapChain->PreDraw(commandList);
  imgui->PreDraw();

  //// バックバッファの番号を取得（2つなので0番か1番）
  //UINT bbIndex = swapChain->Get()->GetCurrentBackBufferIndex();
  //ID3D12Resource* backBuffer = swapChain->GetBackBuffer();
  //// リソースバリアを変更（表示状態→描画対象）
  //CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
  //  backBuffer, D3D12_RESOURCE_STATE_PRESENT,
  //  D3D12_RESOURCE_STATE_RENDER_TARGET);
  //commandList->ResourceBarrier(1, &barrier);

  //// レンダーターゲットビュー用ディスクリプタヒープのハンドルを取得
  //CD3DX12_CPU_DESCRIPTOR_HANDLE rtvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(
  //  rtvHeaps->GetCPUDescriptorHandleForHeapStart(), 
  //  bbIndex, 
  //  device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)
  //);
  //// 深度ステンシルビュー用デスクリプタヒープのハンドルを取得
  //CD3DX12_CPU_DESCRIPTOR_HANDLE dsvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(
  //  dsvHeap->GetCPUDescriptorHandleForHeapStart()
  //);
  //// レンダーターゲットをセット
  //commandList->OMSetRenderTargets(1, &rtvH, false, &dsvH);

  //// 全画面クリア
  //ClearRenderTarget();
  //// 深度バッファクリア
  //ClearDepthBuffer();

  //// ビューポートの設定
  //CD3DX12_VIEWPORT viewport =
  //  CD3DX12_VIEWPORT(0.0f, 0.0f, float(WinApp::window_width), float(WinApp::window_height));
  //commandList->RSSetViewports(1, &viewport);
  //// シザリング矩形の設定
  //CD3DX12_RECT rect = CD3DX12_RECT(0, 0, WinApp::window_width, WinApp::window_height);
  //commandList->RSSetScissorRects(1, &rect);

  //// imgui開始
  //ImGui_ImplDX12_NewFrame();
  //ImGui_ImplWin32_NewFrame();
  //ImGui::NewFrame();

  //// 経過時間計測
  //auto now = std::chrono::steady_clock::now();
  //deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1000000.0f;
  //frameRate = 1.0f / deltaTime;
  //lastUpdate = now;

  //// FPS,CPU使用率表示
  //{
  //  static int count = 0;
  //  const float FPS_BASIS = 60.0f;
  //  // 一秒に一度更新
  //  if (++count > FPS_BASIS) {
  //    count = 0;
  //    float cputime = deltaTime - commandWaitTime;
  //    char str[50];
  //    sprintf_s(str, "fps=%03.0f cpu usage=%06.2f%%", frameRate, cputime * FPS_BASIS * 100.0f);
  //    SetWindowTextA(winApp->GetHwnd(), str);
  //  }
  //}


}
void Core::DirectXCommon::CurDraw()
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
}
void Core::DirectXCommon::PostDraw()
{
  //imgui->DrawUI(commandList);
  commandList->SetResourceBarrierViewMode(swapChain);
  commandList->Close();
  commandQueue->ExcuteCommand(commandList);

  swapChain->Flip(fence);

  commandAllocator->Reset(); // キューをクリア
  commandList->Reset(); // 再びコマンドリストを貯める準備

  swapChain->Present();
}

IDxcBlob* Core::DirectXCommon::CompileShader(const std::wstring& filePath, const wchar_t* profile, IDxcUtils* dxcUtils, IDxcCompiler3* dxcCompiler, IDxcIncludeHandler* includeHandler)
{
  // ここの中身をこの後書いていく
  // 1. hlslファイルを読む
  // これからシェーダーをコンパイルする旨をログに出す
  //Utilitys::Log(std::format(L"Begin CompileShader, path:{}, profile:{}\n", filePath, profile));
  // hlslファイルを読む
  IDxcBlobEncoding* shaderSource = nullptr;
  HRESULT hr = dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource);
  // 読めなかったら止める
  assert(SUCCEEDED(hr));
  // 読み込んだファイルの内容を設定する
  DxcBuffer shaderSourceBuffer = {};
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
    Utility::Debug::Log(shaderError->GetStringPointer());
    // 警告・エラーダメゼッタイ
    assert(false);
  }


  // 4. Compile結果を受け取って返す
  // コンパイル結果から実行用のバイナリ部分を取得
  IDxcBlob* shaderBlob = nullptr;
  hr = shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
  assert(SUCCEEDED(hr));
  // 成功したログを出す
  //Utilitys::Log(std::format(L"Compile Succeeded, path:{}, profile:{}\n", filePath, profile));
  // もう使わないリソースを解放
  shaderSource->Release();
  shaderResult->Release();
  // 実行用のバイナリを返却
  return shaderBlob;
}


//void Core::DirectXCommon::ShaderSetup()
//{
//  // Shaderをコンパイルする
//  IDxcBlob* vertexShaderBlob = CompileShader(L"./Resources/Shader/Object3D.VS.hlsl", L"vs_6_0", dxcUtils, dxcCompiler, includeHandler);
//  assert(vertexShaderBlob != nullptr);
//
//  IDxcBlob* pixelShaderBlob = CompileShader(L"./Resources/Shader/Object3D.PS.hlsl", L"ps_6_0", dxcUtils, dxcCompiler, includeHandler);
//  assert(pixelShaderBlob != nullptr);
//
//  D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
//  graphicsPipelineStateDesc.pRootSignature = rootSignature;// RootSignature
//  graphicsPipelineStateDesc.InputLayout = inputLayoutDesc;// InputLayout
//  graphicsPipelineStateDesc.VS = { vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize() };// VertexShader
//  graphicsPipelineStateDesc.PS = { pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize() };// PixelShader
//  graphicsPipelineStateDesc.BlendState = blendDesc;// BlendState
//  graphicsPipelineStateDesc.RasterizerState = rasterizerDesc;// RasterizerState
//  // 書き込むRTVの情報
//  graphicsPipelineStateDesc.NumRenderTargets = 1;
//  graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
//  // 利用するトポロジ（形状）のタイプ。三角形
//  graphicsPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
//  // どのように画面に色を打ち込むかの設定（気にしなくて良い）
//  graphicsPipelineStateDesc.SampleDesc.Count = 1;
//  graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
//  // 実際に生成
//  ID3D12PipelineState* graphicsPipelineState = nullptr;
//
//  HRESULT hr = device->Get()->CreateGraphicsPipelineState(&graphicsPipelineStateDesc, IID_PPV_ARGS(&graphicsPipelineState));
//  assert(SUCCEEDED(hr));
//
//}

void Core::DirectXCommon::ModelSetup()
{

}

