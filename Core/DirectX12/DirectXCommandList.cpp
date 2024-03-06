#include "DirectXCommandList.h"
#include <cassert>
#include <d3d12.h>
#include <Core/DirectX12/DirectXDevice.h>
#include <Core/DirectX12/DirectXCommandAllocator.h>

Core::DirectXCommandList::DirectXCommandList(DirectXDevice* device, DirectXCommandAllocator* allocator)
{
  this->allocator = allocator;
  HRESULT hr = device->Get()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator->GetRaw() , nullptr, IID_PPV_ARGS(&commandList));
  // コマンドリストの生成がうまくいかなかったので起動できない
  assert(SUCCEEDED(hr));
}

Core::DirectXCommandList::~DirectXCommandList()
{
}

void Core::DirectXCommandList::Release()
{
  commandList->Release();
}
