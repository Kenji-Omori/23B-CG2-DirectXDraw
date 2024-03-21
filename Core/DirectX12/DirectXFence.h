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
    int GetFenceValue();
    UINT GetCompletedValue();
  private:
    DirectXDevice* device;
    Microsoft::WRL::ComPtr<ID3D12Fence> fence;
    UINT fenceValue;
  };
}