#include "DirectXDescriptorHeap.h"

#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>

DirectXDescriptorHeap::DirectXDescriptorHeap(DirectXDevice* device, D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc)
{
  this->device = device;
  this->descriptorHeapDesc = descriptorHeapDesc;
  Create();
}

DirectXDescriptorHeap::DirectXDescriptorHeap(DirectXDevice* device)
{
  this->device = device;
  descriptorHeapDesc = {};
  descriptorHeap = nullptr;
}

DirectXDescriptorHeap::~DirectXDescriptorHeap()
{
}

ID3D12DescriptorHeap* DirectXDescriptorHeap::Get()
{
  return descriptorHeap;
}

void DirectXDescriptorHeap::Create()
{
  HRESULT hr = device->Get()->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&descriptorHeap));
  assert(SUCCEEDED(hr));
}

DirectXDevice* DirectXDescriptorHeap::GetDevice()
{
  return device;
}
