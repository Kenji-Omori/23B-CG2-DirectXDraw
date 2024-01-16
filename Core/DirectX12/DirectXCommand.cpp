#include "DirectXCommand.h"

#include <dxgi1_6.h>

#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>

DirectXCommand::DirectXCommand(DirectXDevice* device)
{
  this->device = device;
  queue = nullptr;
  list = nullptr;
  desc = {};
}

DirectXCommand::~DirectXCommand()
{
}

void DirectXCommand::Setup()
{
  CreateQueue();
  CreateList();
}


void DirectXCommand::CreateQueue()
{
  HRESULT hr = device->Get()->CreateCommandQueue(&desc, IID_PPV_ARGS(&queue));
  // コマンドキューの生成がうまくいかなかったので起動できない
  assert(SUCCEEDED(hr));
}

void DirectXCommand::CreateList()
{
  HRESULT hr = device->Get()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator, nullptr, IID_PPV_ARGS(&list));
  // コマンドリストの生成がうまくいかなかったので起動できない
  assert(SUCCEEDED(hr));
}

