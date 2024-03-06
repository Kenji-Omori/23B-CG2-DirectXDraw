#include "DirectXResource.h"


#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>

Core::DirectXResource::DirectXResource(DirectXDevice* device,const D3D12_RESOURCE_DESC& desc, const D3D12_HEAP_PROPERTIES& properties)
{
  this->device = device;
  this->desc = desc;
  this->properties = properties;
  HRESULT hr = device->Get()->CreateCommittedResource(&properties, D3D12_HEAP_FLAG_NONE, &this->desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&resource));
  assert(SUCCEEDED(hr));
}

Core::DirectXResource::~DirectXResource()
{

}

void Core::DirectXResource::CreateColorBuffers()
{

}

Core::DirectXDevice* Core::DirectXResource::GetDevice()
{
  return device;
}

ID3D12Resource* Core::DirectXResource::GetResource()
{
  return resource;
}

