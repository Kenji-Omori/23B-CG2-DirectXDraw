#pragma once
#include <wrl.h>


struct ID3D12GraphicsCommandList;
namespace Core {
  class DirectXDevice;
  class DirectXCommandAllocator;
  class DirectXCommandList
  {
  public:
    DirectXCommandList(DirectXDevice* device, DirectXCommandAllocator* allocator);
    ~DirectXCommandList();
    void Release();

  private:
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
    Core::DirectXDevice* device;
    DirectXCommandAllocator* allocator;
  };
}