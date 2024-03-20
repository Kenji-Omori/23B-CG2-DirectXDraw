#include "DirectXSwapChainBuffers.h"
#include <Core/DirectX12/DirectXSwapChain.h>
#include <Core/DirectX12/DirectXDevice.h>
#include <Externals/DirectXTex/d3dx12.h>
#include <d3d12.h>
#include <cassert>
#include <dxgi1_6.h>


Core::DirectXSwapChainBuffers::DirectXSwapChainBuffers(DirectXDevice* device, DirectXSwapChain* swapChain) :DirectXDescriptorHeap(device)
{
  this->swapChain = swapChain;
  HRESULT result = S_FALSE;

  DXGI_SWAP_CHAIN_DESC swcDesc = {};
  result = swapChain->Get()->GetDesc(&swcDesc);
  assert(SUCCEEDED(result));

  // 各種設定をしてディスクリプタヒープを生成

  descriptorHeapDesc = 
  {
    D3D12_DESCRIPTOR_HEAP_TYPE_RTV  , // D3D12_DESCRIPTOR_HEAP_TYPE Type;
    swcDesc.BufferCount             ,// UINT NumDescriptors;
    D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_NONE,// D3D12_DESCRIPTOR_HEAP_FLAGS Flags;
    0 // UINT NodeMask;
  };

  CreateDescriptorHeap();

  // 裏表の２つ分について
  backBuffers.resize(swcDesc.BufferCount);
  for (int i = 0; i < backBuffers.size(); i++) {
    // スワップチェーンからバッファを取得
    result = swapChain->Get()->GetBuffer(i, IID_PPV_ARGS(&backBuffers[i]));
    assert(SUCCEEDED(result));

    // ディスクリプタヒープのハンドルを取得
    CD3DX12_CPU_DESCRIPTOR_HANDLE handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
      descriptorHeap->GetCPUDescriptorHandleForHeapStart(), i,
      device->Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
    // レンダーターゲットビューの設定
    D3D12_RENDER_TARGET_VIEW_DESC renderTargetViewDesc{};
    // シェーダーの計算結果をSRGBに変換して書き込む
    renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    renderTargetViewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
    // レンダーターゲットビューの生成
    device->Get()->CreateRenderTargetView(backBuffers[i].Get(), &renderTargetViewDesc, handle);
  }
}

Core::DirectXSwapChainBuffers::~DirectXSwapChainBuffers()
{
}

ID3D12Resource* Core::DirectXSwapChainBuffers::GetBackBuffer()
{
  UINT backbufferIndex = swapChain->GetBufferNum()-1;
    return backBuffers[backbufferIndex].Get();
}
