#pragma once
#include <format>
#include <wrl.h>
struct ID3D12Fence;
namespace Core {
  class DirectXDevice;
  class DirectXFence
  {
  public:
    DirectXFence(DirectXDevice* device);
    ~DirectXFence();
    void Release();
    ID3D12Fence* Get();
    void AddFenceValue();
    UINT64 GetFenceValue();
    UINT64 GetCompletedValue();
    bool IsOverFenceValue();
    void WaitForFin();
  private:
    DirectXDevice* device;
    Microsoft::WRL::ComPtr<ID3D12Fence> fence;
    UINT64 fenceValue;
  };
}