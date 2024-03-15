#pragma once
#include<Core/DirectX12/DirectXDescriptorHeap.h>
#include <vector>
#include <wrl.h>
namespace Core {
  class DirectXDevice;
  class DirectXSwapChain;
  class DirectXDescriptorHeapSwapChainBuffers :DirectXDescriptorHeap
  {
  public:
    DirectXDescriptorHeapSwapChainBuffers(DirectXDevice* device, DirectXSwapChain* swapChain);
    ~DirectXDescriptorHeapSwapChainBuffers();

  private:
    std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
  };
}