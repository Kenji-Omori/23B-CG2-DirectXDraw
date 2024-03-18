#include "DirectXCommandQueue.h"

#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>
#include <Core/DirectX12/DirectXCommandAllocator.h>
#include <Core/DirectX12/DirectXCommandList.h>
Core::DirectXCommandQueue::DirectXCommandQueue(DirectXDevice* device)
{
  this->device = device;
  commandQueue = nullptr;
  D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
  HRESULT hr = device->Get()->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
  // コマンドアロケータの生成がうまくいかなかったので起動できない
  assert(SUCCEEDED(hr));
}

Core::DirectXCommandQueue::~DirectXCommandQueue()
{
}

void Core::DirectXCommandQueue::Release()
{
  commandQueue->Release();
}

Microsoft::WRL::ComPtr<ID3D12CommandQueue> Core::DirectXCommandQueue::Get()
{
  return commandQueue;
}

ID3D12CommandQueue* Core::DirectXCommandQueue::GetRaw()
{
  return commandQueue.Get();
}

void Core::DirectXCommandQueue::ExcuteCommand(DirectXCommandList* commandList) const
{
  ID3D12CommandList* cmdLists[] = { commandList->GetCommandList() };
  UINT commandNum = 1;
  commandQueue->ExecuteCommandLists(commandNum, cmdLists);
}

