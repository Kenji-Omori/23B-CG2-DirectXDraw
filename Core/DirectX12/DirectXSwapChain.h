#pragma once
#include <wrl.h>
struct IDXGISwapChain4;

struct DXGI_SWAP_CHAIN_DESC;
namespace Core {
  class DirectXCommandQueue;
  class DirectXSwapChainBuffers;
  class DirectXDevice;
  class DirectXSwapChain
  {
  public:
    DirectXSwapChain(DirectXDevice* device,  DirectXCommandQueue* commandQueue, int bufferNum);
    ~DirectXSwapChain();
    int GetBufferNum();
    HRESULT GetDesc(DXGI_SWAP_CHAIN_DESC* desc);
    Microsoft::WRL::ComPtr<IDXGISwapChain4> Get() const;
  private:

    Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
    DirectXCommandQueue* commandQueue;
    int bufferNum;
    DirectXSwapChainBuffers* buffers;
    DirectXDevice* device;
  };

}