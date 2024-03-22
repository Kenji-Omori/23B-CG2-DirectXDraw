#include "DirectXSwapChain.h"

#include <Core/Window.h>
#include <Core/DirectX12/DirectXFactory.h>
#include <Core/DirectX12/DirectXCommandQueue.h>
#include <Core/DirectX12/DirectXSwapChainBuffers.h>
#include <Core/DirectX12/DirectXDevice.h>
#include <Core/DirectX12/DirectXCommandList.h>
#include <Core/DirectX12/DirectXDepthBuffer.h>
#include <Externals/DirectXTex/d3dx12.h>
#include <Core/DirectX12/DirectXFence.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>


Core::DirectXSwapChain::DirectXSwapChain(DirectXDevice* device, DirectXCommandQueue* commandQueue, int bufferNum)
{
  this->bufferNum = bufferNum;
  this->commandQueue = commandQueue;
  this->device = device;
  Window* window = device->GetWindow();
  IDXGIFactory7* factory = device->GetFactory()->Get().Get();

  DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

  swapChainDesc.Width = window->GetResolution().x; // 画面の幅。ウィンドウのクライアント領域を同じものにしておく
  swapChainDesc.Height = window->GetResolution().y;   // 画面の高さ。ウィンドウのクライアント領域を同じものにしておく
  swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // 色の形式
  swapChainDesc.SampleDesc.Count = 1; // マルチサンプルしない
  swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER; // 描画のターゲットとして利用する
  swapChainDesc.BufferCount = bufferNum;  // ダブルバッファ
  swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // モニタにうつしたら、中身を破棄
  swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING; // ティアリングサポート
  // コマンドキュー、ウィンドウハンドル、設定を渡して生成する
  Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain1;
  HRESULT hr = factory->CreateSwapChainForHwnd(commandQueue->GetRaw(), window->GetWindowHandle(), &swapChainDesc, nullptr, nullptr, &swapChain1);
  assert(SUCCEEDED(hr));
  swapChain1->QueryInterface(IID_PPV_ARGS(&swapChain));
  buffers = new DirectXSwapChainBuffers(device, this);
  depthBuffer = new DirectXDepthBuffer(device, window);
}

Core::DirectXSwapChain::~DirectXSwapChain()
{
}

int Core::DirectXSwapChain::GetBufferNum()
{
  return bufferNum;
}

HRESULT Core::DirectXSwapChain::GetDesc(DXGI_SWAP_CHAIN_DESC* desc)
{
  return swapChain->GetDesc(desc);
}

Microsoft::WRL::ComPtr<IDXGISwapChain4> Core::DirectXSwapChain::Get() const
{
  return swapChain;
}

UINT Core::DirectXSwapChain::GetCurrentBackBufferIndex()
{
  return swapChain->GetCurrentBackBufferIndex();
}

ID3D12Resource* Core::DirectXSwapChain::GetBackBuffer()
{
  return buffers->GetBackBuffer();
}

void Core::DirectXSwapChain::PreDraw(DirectXCommandList* commandList)
{
  commandList->SetResourceBarrier(this);
  commandList->SetOutputMergeRenderTargets(buffers, depthBuffer, GetCurrentBackBufferIndex());
  commandList->ClearRenderTarget(buffers, GetCurrentBackBufferIndex(), clearColor);
  commandList->ClearDepthBuffer(depthBuffer);

  commandList->SetResourceViewports(1);
  commandList->SetResourceScissorRects(1);
}

void Core::DirectXSwapChain::PostDraw()
{
}

void Core::DirectXSwapChain::Flip(DirectXFence* fence)
{

  // バッファをフリップ
  HRESULT result = swapChain->Present(1, 0);
#ifdef _DEBUG
  if (FAILED(result)) {
    Microsoft::WRL::ComPtr<ID3D12DeviceRemovedExtendedData> dred;

    result = device->Get()->QueryInterface(IID_PPV_ARGS(&dred));
    assert(SUCCEEDED(result));

    // 自動パンくず取得
    D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT autoBreadcrumbsOutput{};
    result = dred->GetAutoBreadcrumbsOutput(&autoBreadcrumbsOutput);
    assert(SUCCEEDED(result));
  }
#endif

  // コマンドリストの実行完了を待つ
  fence->AddFenceValue();
  // https://shobomaru.wordpress.com/2015/07/12/d3d12-fence/
  commandQueue->Get()->Signal(fence->Get(), fence->GetFenceValue());
  fence->WaitForFenceValue();

}

void Core::DirectXSwapChain::Present()
{
  swapChain->Present(1, 0);
  //swapChain->Present1(1,0,nullptr);
}

void Core::DirectXSwapChain::ClearRenderTarget(DirectXCommandList* commandList)
{

}
