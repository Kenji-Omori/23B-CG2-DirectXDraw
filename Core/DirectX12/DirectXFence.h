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

  private:
    DirectXDevice* device;
    Microsoft::WRL::ComPtr<ID3D12Fence> fence;
    //HANDLE event;
  //  HANDLE fenceEvent;
  };
}