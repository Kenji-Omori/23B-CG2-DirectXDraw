#pragma once
#include <wrl.h>
struct IDXGISwapChain4;

namespace Core {
  class DirectXFactory;
  class DirectXCommandQueue;
  class Window;
  class DirectXSwapChain
  {
  public:
    DirectXSwapChain(Window* window, DirectXFactory* factory, DirectXCommandQueue* commandQueue, int bufferNum);
    ~DirectXSwapChain();
    int GetBufferNum();
    Microsoft::WRL::ComPtr<IDXGISwapChain4> Get() const;
  private:

    Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
    DirectXFactory* factory;
    DirectXCommandQueue* commandQueue;
    int bufferNum;
  };

}