#include "DirectXCommand.h"

#include <dxgi1_6.h>

#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>

Core::DirectXCommand::DirectXCommand(DirectXDevice* device)
{
  this->device = device;
  queue = nullptr;
  list = nullptr;
  //desc = {};
}

Core::DirectXCommand::~DirectXCommand()
{
}

void Core::DirectXCommand::Setup()
{
  CreateQueue();
  CreateList();
}


void Core::DirectXCommand::CreateQueue()
{
  //HRESULT hr = device->Get()->CreateCommandQueue(&desc, IID_PPV_ARGS(&queue));
  //// コマンドキューの生成がうまくいかなかったので起動できない
  //assert(SUCCEEDED(hr));
}

void Core::DirectXCommand::CreateList()
{
  //HRESULT hr = device->Get()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator, nullptr, IID_PPV_ARGS(&list));
  //// コマンドリストの生成がうまくいかなかったので起動できない
  //assert(SUCCEEDED(hr));
}

