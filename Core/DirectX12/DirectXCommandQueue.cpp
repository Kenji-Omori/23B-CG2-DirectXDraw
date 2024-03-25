#include "DirectXCommandQueue.h"

#include <Core/DirectX12/DirectXDevice.h>
#include <Core/DirectX12/DirectXCommandAllocator.h>
#include <Core/DirectX12/DirectXCommandList.h>
#include <Core/DirectX12/DirectXFence.h>
#include <cassert>
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

void Core::DirectXCommandQueue::WaitForFin(DirectXFence* fence)
{
  // コマンドリストの実行完了を待つ
  fence->AddFenceValue();
  // https://shobomaru.wordpress.com/2015/07/12/d3d12-fence/
  commandQueue->Signal(fence->Get(), fence->GetFenceValue());
  fence->WaitForFin();
}

void Core::DirectXCommandQueue::ExcuteCommand(DirectXCommandList* commandList) const
{
  ID3D12CommandList* cmdLists[] = { commandList->GetCommandList() };
  UINT commandNum = 1;
  commandQueue->ExecuteCommandLists(commandNum, cmdLists);
}

