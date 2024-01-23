#pragma once
#include <wrl.h>
class DirectXDevice;

class DirectXInfoQueue
{
public:
  DirectXInfoQueue(Microsoft::WRL::ComPtr<DirectXDevice> device);
  ~DirectXInfoQueue();

private:
  Microsoft::WRL::ComPtr<DirectXDevice> device;
};