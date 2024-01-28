#pragma once

#include <memory>
#include <d3d12.h>
struct ID3D12Resource;
class DirectXDevice;

class DirectXResource
{
public:
  DirectXResource(DirectXDevice* device,const D3D12_RESOURCE_DESC& desc, const D3D12_HEAP_PROPERTIES& properties);
  ~DirectXResource();
  void CreateColorBuffers();
  ID3D12Resource* GetResource();

private:
  DirectXDevice* device;
  ID3D12Resource* resource;
  D3D12_RESOURCE_DESC desc;
  D3D12_HEAP_PROPERTIES properties;
};
