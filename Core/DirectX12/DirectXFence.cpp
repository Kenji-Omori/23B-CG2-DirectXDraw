#include "DirectXFence.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>


#include <Core/DirectX12/DirectXDevice.h>
DirectXFence::DirectXFence(DirectXDevice* device)
{
  this->device = device;
  uint64_t fenceValue = 0;
  HRESULT hr = device->Get()->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
  assert(SUCCEEDED(hr));
  // FenceのSignalを待つためのイベントを作成する
  fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  assert(fenceEvent != nullptr);
}
