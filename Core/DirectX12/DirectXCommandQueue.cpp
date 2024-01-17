#include "DirectXCommandQueue.h"

#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>
#include <Core/DirectX12/DirectXCommandAllocator.h>
DirectXCommandQueue::DirectXCommandQueue(DirectXDevice* device, DirectXCommandAllocator* allocator)
{
  this->device = device;
  this->allocator = allocator;

  ID3D12CommandAllocator* alc = allocator->GetAllocator(0);
  HRESULT hr = device->Get()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&alc));
  // コマンドアロケータの生成がうまくいかなかったので起動できない
  assert(SUCCEEDED(hr));
}

DirectXCommandQueue::~DirectXCommandQueue()
{
}

