#include "DirectXFence.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <Core/DirectX12/DirectXDevice.h>

Core::DirectXFence::DirectXFence(DirectXDevice* device)
{
  this->device = device;
  fenceValue = 0;
  HRESULT hr = device->Get()->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
  assert(SUCCEEDED(hr));
  // FenceのSignalを待つためのイベントを作成する
  HANDLE fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  assert(fenceEvent != nullptr);
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

UINT64 Core::DirectXFence::GetFenceValue()
{
  return fenceValue;
}

UINT64 Core::DirectXFence::GetCompletedValue()
{
  return fence->GetCompletedValue();
}

bool Core::DirectXFence::IsOverFenceValue()
{
  return GetCompletedValue() >= fenceValue;
}

void Core::DirectXFence::WaitForFin()
{
  if (IsOverFenceValue()) { return; }
  HANDLE fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
  fence->SetEventOnCompletion(fenceValue, fenceEvent);
  WaitForSingleObject(fenceEvent, INFINITE);
  CloseHandle(fenceEvent);
}
