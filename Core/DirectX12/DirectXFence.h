#pragma once
#include <format>

class DirectXDevice;
struct ID3D12Fence;
class DirectXFence
{
public:
  DirectXFence(DirectXDevice* device);
  ~DirectXFence();
  void Release();

private:
  DirectXDevice* device;
  ID3D12Fence* fence;
  HANDLE event;
//  HANDLE fenceEvent;
};
