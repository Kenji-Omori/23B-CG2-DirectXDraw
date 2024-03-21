#include "DirectXFence.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>

Core::DirectXFence::DirectXFence(DirectXDevice* device)
{
  this->device = device;
  uint64_t fenceValue = 0;
  HRESULT hr = device->Get()->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
  assert(SUCCEEDED(hr));
  // FenceのSignalを待つためのイベントを作成する
  HANDLE fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  assert(fenceEvent != nullptr);
  fenceValue = 0;

  //fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
}

Core::DirectXFence::~DirectXFence()
{
}

void Core::DirectXFence::Release()
{
  fence->Release();
}

ID3D12Fence* Core::DirectXFence::Get()
{
    return fence.Get();
}

void Core::DirectXFence::AddFenceValue()
{
  fenceValue++;
}

int Core::DirectXFence::GetFenceValue()
{
  return fenceValue;
}

UINT Core::DirectXFence::GetCompletedValue()
{
  return fence->GetCompletedValue();
}
