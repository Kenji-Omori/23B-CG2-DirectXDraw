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

  auto WindowResolution = window->GetResolution();
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
  HRESULT hr = factory->CreateSwapChainForHwnd(
    commandQueue->GetRaw(), 
    window->GetWindowHandle(), 
    &swapChainDesc, 
    nullptr, 
    nullptr, 
    &swapChain1
  );
  assert(SUCCEEDED(hr));
//  swapChain1->QueryInterface(IID_PPV_ARGS(&swapChain));
  swapChain1.As(&swapChain);
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

ID3D12Resource* Core::DirectXSwapChain::GetCurrentBackBuffer()
{
  return buffers->GetCurrentBackBuffer();
}

void Core::DirectXSwapChain::PreDraw(DirectXCommandList* commandList)
{
  commandList->SetOutputMergeRenderTargets(buffers, depthBuffer, GetCurrentBackBufferIndex());
  commandList->ClearRenderTarget(buffers, GetCurrentBackBufferIndex(), clearColor);
  commandList->ClearDepthBuffer(depthBuffer);

  commandList->SetResourceViewports(1);
  commandList->SetResourceScissorRects(1);

}

void Core::DirectXSwapChain::PostDraw()
{
}

/*
D3D12 ERROR: ID3D12CommandQueue::ExecuteCommandLists: Using IDXGISwapChain::Present on Command List (0x000001B0D92F1610:'Internal DXGI CommandList'): Resource state (0x4: D3D12_RESOURCE_STATE_RENDER_TARGET) of resource (0x000001B0D9356770:'Unnamed ID3D12Resource Object') (subresource: 0) is invalid for use as a PRESENT_SOURCE.  Expected State Bits (all): 0x0: D3D12_RESOURCE_STATE_[COMMON|PRESENT], Actual State: 0x4: D3D12_RESOURCE_STATE_RENDER_TARGET, Missing State: 0x0: D3D12_RESOURCE_STATE_[COMMON|PRESENT]. [ EXECUTION ERROR #538: INVALID_SUBRESOURCE_STATE]
D3D12: **BREAK** enabled for the previous message, which was: [ ERROR EXECUTION #538: INVALID_SUBRESOURCE_STATE ]

*/


void Core::DirectXSwapChain::Present()
{
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
  //swapChain->Present1(1,0,nullptr);
}

void Core::DirectXSwapChain::ClearRenderTarget(DirectXCommandList* commandList)
{

}
