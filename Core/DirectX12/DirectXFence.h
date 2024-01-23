#pragma once
#include <format>
#include <wrl.h>
class DirectXDevice;
struct ID3D12Fence;

class DirectXFence
{
public:
  DirectXFence(Microsoft::WRL::ComPtr<DirectXDevice> device);
  ~DirectXFence();
  void Release();

private:
  Microsoft::WRL::ComPtr<DirectXDevice> device;
  Microsoft::WRL::ComPtr<ID3D12Fence> fence;
  //HANDLE event;
//  HANDLE fenceEvent;
};
