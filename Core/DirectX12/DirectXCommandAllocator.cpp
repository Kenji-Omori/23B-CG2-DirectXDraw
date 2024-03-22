#include "DirectXCommandAllocator.h"
#include <d3d12.h>
#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>
Core::DirectXCommandAllocator::DirectXCommandAllocator(DirectXDevice* device)
{
  this->device = device;
  HRESULT hr = device->Get()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator));
  assert(SUCCEEDED(hr));
}

Core::DirectXCommandAllocator::~DirectXCommandAllocator()
{
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> Core::DirectXCommandAllocator::Get()
{
  return allocator;
}

ID3D12CommandAllocator* Core::DirectXCommandAllocator::GetRaw()
{
  return allocator.Get();
}

void Core::DirectXCommandAllocator::Reset()
{
  allocator->Reset();
}

void Core::DirectXCommandAllocator::Release()
{
  allocator->Release();
}
