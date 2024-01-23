#include "DirectXCommandQueue.h"

#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>
#include <Core/DirectX12/DirectXCommandAllocator.h>
DirectXCommandQueue::DirectXCommandQueue(Microsoft::WRL::ComPtr<DirectXDevice> device)
{
  this->device = device;
  commandQueue = nullptr;
  D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
  HRESULT hr = device->Get()->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
  // コマンドアロケータの生成がうまくいかなかったので起動できない
  assert(SUCCEEDED(hr));
}

DirectXCommandQueue::~DirectXCommandQueue()
{
}

void DirectXCommandQueue::Release()
{
  commandQueue->Release();
}

