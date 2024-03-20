#pragma once
#include <wrl.h>
#include <Utility/Type/Color.h>

struct IDXGISwapChain4;
struct ID3D12Resource;
struct DXGI_SWAP_CHAIN_DESC;
namespace Core {
  class DirectXCommandQueue;
  class DirectXSwapChainBuffers;
  class DirectXDevice;
  class DirectXCommandList;
  class DirectXDescriptorHeap;
  class DirectXSwapChain
  {
  public:
    DirectXSwapChain(DirectXDevice* device,  DirectXCommandQueue* commandQueue, int bufferNum);
    ~DirectXSwapChain();
    int GetBufferNum();
    HRESULT GetDesc(DXGI_SWAP_CHAIN_DESC* desc);
    Microsoft::WRL::ComPtr<IDXGISwapChain4> Get() const;
    UINT GetCurrentBackBufferIndex();
    ID3D12Resource* GetBackBuffer();
    void SetDSVHeap(DirectXDescriptorHeap* dsvHeap);
    void PreDraw(DirectXCommandList* commandList);
    void PostDraw();
    static const Color clearColor; 
  private:
    void ClearRenderTarget(DirectXCommandList* commandList);

    Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
    DirectXCommandQueue* commandQueue;
    int bufferNum;
    DirectXSwapChainBuffers* buffers;
    DirectXDevice* device;
    DirectXDescriptorHeap* dsvHeap;
  };

}