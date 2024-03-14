#pragma once
#include<Core/DirectX12/DirectXDescriptorHeap.h>
#include <vector>
#include <wrl.h>
namespace Core {
  class DirectXDevice;
  class DirectXSwapChain;
  class DirectXDescriptorHeapBackBuffers :DirectXDescriptorHeap
  {
  public:
    DirectXDescriptorHeapBackBuffers(DirectXDevice* device, DirectXSwapChain* swapChain);
    ~DirectXDescriptorHeapBackBuffers();

  private:
    std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
  };
}