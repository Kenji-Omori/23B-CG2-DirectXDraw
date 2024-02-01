#include "DirectXResource.h"


#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>

DirectXResource::DirectXResource(DirectXDevice* device,const D3D12_RESOURCE_DESC& desc, const D3D12_HEAP_PROPERTIES& properties)
{
  this->device = device;
  this->desc = desc;
  this->properties = properties;
  HRESULT hr = device->Get()->CreateCommittedResource(&properties, D3D12_HEAP_FLAG_NONE, &this->desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&resource));
  assert(SUCCEEDED(hr));
}

DirectXResource::~DirectXResource()
{

}

void DirectXResource::CreateColorBuffers()
{

}

DirectXDevice* DirectXResource::GetDevice()
{
  return device;
}

ID3D12Resource* DirectXResource::GetResource()
{
  return resource;
}

