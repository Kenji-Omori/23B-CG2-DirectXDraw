#include "DirectXResource.h"


#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>

Core::DirectXResource::DirectXResource(DirectXDevice* device)
{
  this->device = device;
  this->desc = {};
  this->properties = {};
  this->resource = nullptr;
}

Core::DirectXResource::DirectXResource(DirectXDevice* device,const D3D12_RESOURCE_DESC& desc, const D3D12_HEAP_PROPERTIES& properties)
{
  this->device = device;
  this->desc = desc;
  this->properties = properties;
  this->resource = nullptr;
}



Core::DirectXResource::~DirectXResource()
{

}

void Core::DirectXResource::SetResourceDesc(const D3D12_RESOURCE_DESC& desc)
{
  this->desc = desc;
}

void Core::DirectXResource::SetProperties(const D3D12_HEAP_PROPERTIES& properties)
{
  this->properties = properties;
}
//
//void Core::DirectXResource::CreateCommittedResource()
//{
//  HRESULT hr = device->Get()->CreateCommittedResource(&properties, D3D12_HEAP_FLAG_NONE,&desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&resource));
//  assert(SUCCEEDED(hr));
//}

Core::DirectXDevice* Core::DirectXResource::GetDevice()
{
  return device;
}

ID3D12Resource* Core::DirectXResource::GetResource()
{
  return resource;
}

