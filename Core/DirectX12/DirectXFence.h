#pragma once
#include <format>

class DirectXDevice;
class ID3D12Fence;
class DirectXFence
{
public:
  DirectXFence(DirectXDevice* device);
  ~DirectXFence();

private:
  DirectXDevice* device;
  ID3D12Fence* fence;
  HANDLE fenceEvent;
};
