#include "DirectXCommandAllocator.h"
#include <d3d12.h>
#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>
DirectXCommandAllocator::DirectXCommandAllocator(DirectXDevice* device)
{
  this->device = device;
  HRESULT hr = device->Get()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator));
  assert(SUCCEEDED(hr));
}

DirectXCommandAllocator::~DirectXCommandAllocator()
{
  assert(allocator == nullptr);
}

ID3D12CommandAllocator* DirectXCommandAllocator::GetAllocator()
{
  return allocator;
}

void DirectXCommandAllocator::Release()
{
  allocator->Release();
  allocator = nullptr;
}
