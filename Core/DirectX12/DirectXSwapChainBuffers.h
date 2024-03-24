#pragma once
#include<Core/DirectX12/DirectXDescriptorHeap.h>
#include <vector>
#include <wrl.h>
namespace Core {
  class DirectXDevice;
  class DirectXSwapChain;
  class DirectXSwapChainBuffers :public DirectXDescriptorHeap
  {
  public:
    DirectXSwapChainBuffers(DirectXDevice* device, DirectXSwapChain* swapChain);
    ~DirectXSwapChainBuffers();
    ID3D12Resource* GetCurrentBackBuffer();
    ID3D12Resource* GetBackBuffer(UINT index);

  private:
    std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
    DirectXSwapChain* swapChain;
  };
}