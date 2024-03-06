#include "DirectXDescriptorHeap.h"

#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>

Core::DirectXDescriptorHeap::DirectXDescriptorHeap(DirectXDevice* device, D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc)
{
  this->device = device;
  this->descriptorHeapDesc = descriptorHeapDesc;
  Create();
}

Core::DirectXDescriptorHeap::DirectXDescriptorHeap(DirectXDevice* device)
{
  this->device = device;
  descriptorHeapDesc = {};
  descriptorHeap = nullptr;
}

Core::DirectXDescriptorHeap::~DirectXDescriptorHeap()
{
}

ID3D12DescriptorHeap* Core::DirectXDescriptorHeap::Get()
{
  return descriptorHeap;
}

void Core::DirectXDescriptorHeap::Create()
{
  HRESULT hr = device->Get()->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&descriptorHeap));
  assert(SUCCEEDED(hr));
}

Core::DirectXDevice* Core::DirectXDescriptorHeap::GetDevice() const
{
    return device;
}

