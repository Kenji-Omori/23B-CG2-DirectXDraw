#include "DirectXCommandQueue.h"

#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>
DirectXCommandQueue::DirectXCommandQueue(DirectXDevice* device, unsigned char allocatorNum)
{
  this->allocatorNum = allocatorNum;
  allocators = std::make_unique < ID3D12CommandAllocator * []>(allocatorNum);
  for (unsigned char i = 0; i < allocatorNum; i++)
  {
    HRESULT hr = device->Get()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&(allocators[i])));
    // コマンドアロケータの生成がうまくいかなかったので起動できない
    assert(SUCCEEDED(hr));
    

  }
}

DirectXCommandQueue::~DirectXCommandQueue()
{
  for (unsigned char i = 0; i < allocatorNum; i++)
  {
    allocators[i]->Release();
  }
}

ID3D12CommandAllocator* DirectXCommandQueue::GetAllocator(unsigned char index)
{
  return allocators[index];
}
