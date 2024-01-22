#include "DirectXCommandList.h"
#include <Core/DirectX12/DirectXDevice.h>
#include <cassert>
#include <d3d12.h>

DirectXCommandList::DirectXCommandList(DirectXDevice* device)
{
  this->device = device;

  HRESULT hr = device->Get()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, nullptr, IID_PPV_ARGS(&commandList));
  // コマンドリストの生成がうまくいかなかったので起動できない
  assert(SUCCEEDED(hr));
}

DirectXCommandList::~DirectXCommandList()
{
}

void DirectXCommandList::Release()
{
  commandList->Release();
  commandList = nullptr;
}
