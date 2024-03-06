#pragma once
#include <wrl.h>

namespace Core {
  class DirectXDevice;
  class DirectXInfoQueue
  {
  public:
    DirectXInfoQueue(DirectXDevice* device);
    ~DirectXInfoQueue();

  private:
    DirectXDevice* device;
  };
}