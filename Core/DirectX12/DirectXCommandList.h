#pragma once
#include <wrl.h>


struct ID3D12GraphicsCommandList;
struct ID3D12DescriptorHeap;
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
    ID3D12GraphicsCommandList* GetCommandList();
    void SetResourceBarrier(DirectXSwapChain* swapChain, UINT barrierNum = 1) ;
    void SetOutputMergeRenderTargets(DirectXDescriptorHeap* rtvHeap, DirectXDescriptorHeap* dsvHeap, UINT backBufferIndex);
    void ClearRenderTarget(DirectXDescriptorHeap* rtvHeap, UINT backBufferIndex,const Color& clearColor);
    void ClearDepthBuffer(DirectXDescriptorHeap* dsvHeap);
    void SetResourceViewports(UINT viewportNum);
    void SetResourceScissorRects(UINT viewportNum);
    void SetDescriptorHeap(ID3D12DescriptorHeap* descriptorHeap);
    void SetDescriptorHeap(DirectXDescriptorHeap* descriptorHeap);
    void Reset();
    void Close();
    void Release();

  private:
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
    Core::DirectXDevice* device;
    DirectXCommandAllocator* allocator;
  };
}