#pragma once
#include <wrl.h>


struct ID3D12GraphicsCommandList;
class Color;
namespace Core {
  class DirectXDevice;
  class DirectXCommandAllocator;
  class DirectXSwapChain;
  class DirectXDescriptorHeap;
  class DirectXCommandList
  {
  public:
    DirectXCommandList(DirectXDevice* device, DirectXCommandAllocator* allocator);
    ~DirectXCommandList();
    ID3D12CommandList* GetCommandList();
    void SetResourceBarrier(DirectXSwapChain* swapChain, UINT barrierNum=1);
    void SetOutputMergeRenderTargets(DirectXDescriptorHeap* rtvHeap, DirectXDescriptorHeap* dsvHeap);
    void ClearRenderTarget(DirectXDescriptorHeap* rtvHeap, UINT backBufferIndex, const Color& clearColor);
    void Close();
    void Release();

  private:
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
    Core::DirectXDevice* device;
    DirectXCommandAllocator* allocator;
  };
}