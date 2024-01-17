#pragma once
#include <format>

class DirectXDevice;
struct ID3D12Fence;
class DirectXFence
{
public:
  DirectXFence(DirectXDevice* device);
  ~DirectXFence();

private:
  DirectXDevice* device;
  ID3D12Fence* fence;
//  HANDLE fenceEvent;
};
