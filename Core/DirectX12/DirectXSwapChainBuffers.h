#pragma once
#include<Core/DirectX12/DirectXDescriptorHeap.h>
#include <vector>
#include <wrl.h>
namespace Core {
  class DirectXDevice;
  class DirectXSwapChain;
  class DirectXSwapChainBuffers :DirectXDescriptorHeap
  {
  public:
    DirectXSwapChainBuffers(DirectXDevice* device, DirectXSwapChain* swapChain);
    ~DirectXSwapChainBuffers();

  private:
    std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
  };
}