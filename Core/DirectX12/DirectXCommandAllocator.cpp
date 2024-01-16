#include "DirectXCommandAllocator.h"
#include <d3d12.h>
#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>
DirectXCommandAllocator::DirectXCommandAllocator(DirectXDevice* device, unsigned char allocatorNum)
{
  this->allocatorNum = allocatorNum;
  this->device = device;
  allocators = std::make_unique<ID3D12CommandAllocator*[]>(allocatorNum);
  for (unsigned char i = 0; i < allocatorNum; i++)
  {
    HRESULT hr = device->Get()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocators[i]));
    assert(SUCCEEDED(hr));
  }
}

DirectXCommandAllocator::~DirectXCommandAllocator()
{
  for (unsigned char i = 0; i < allocatorNum; i++)
  {
    allocators[i]->Release();
  }
}

ID3D12CommandAllocator* DirectXCommandAllocator::GetAllocator(unsigned char index)
{
  return allocators[index];
}
