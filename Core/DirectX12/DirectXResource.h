#pragma once

#include <memory>
#include <d3d12.h>
struct ID3D12Resource;
namespace Core {
  class DirectXDevice;
  class DirectXResource
  {
  public:
    DirectXResource(DirectXDevice* device);
    DirectXResource(DirectXDevice* device, const D3D12_RESOURCE_DESC& desc, const D3D12_HEAP_PROPERTIES& properties);
    ~DirectXResource();
    DirectXDevice* GetDevice();
    ID3D12Resource* GetResource();

  protected:
    void SetResourceDesc(const D3D12_RESOURCE_DESC& desc);
    void SetProperties(const D3D12_HEAP_PROPERTIES& properties);
    ID3D12Resource* resource;
    D3D12_RESOURCE_DESC desc;
    D3D12_HEAP_PROPERTIES properties;

  private:
    DirectXDevice* device;
  };
}