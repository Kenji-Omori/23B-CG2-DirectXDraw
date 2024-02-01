#pragma once

// #include <d3d12.h>
// #include <dxgi1_6.h>
//#include <Core/Window.h>
#include <wrl.h>
#include <vector>
#include <memory>

//class DirectXAdapter;
//class DirectXCommand;
//class DirectXDevice;
//class DirectXFactory;
//class DirectXFence;
//class DirectXInfoQueue;
//class DirectXCommandQueue;
//class DirectXCommandAllocator;
//class DirectXCommandList;
class DirectXSwapChain;
class Window;

#include <Core/Window.h>
#include <Core/DirectX12/DirectXAdapter.h>
#include <Core/DirectX12/DirectXCommand.h>
#include <Core/DirectX12/DirectXDevice.h>
#include <Core/DirectX12/DirectXFactory.h>
#include <Core/DirectX12/DirectXFence.h>
#include <Core/DirectX12/DirectXInfoQueue.h>
#include <Core/DirectX12/DirectXSwapChain.h>
#include <Core/DirectX12/DirectXCommandQueue.h>
#include <Core/DirectX12/DirectXCommandAllocator.h>
#include <Core/DirectX12/DirectXCommandList.h>
#include <Core/DirectX12/DirectXDescriptorHeapRTV.h>
#include <Core/DirectX12/DirectXDescriptorHeapSRV.h>
#include <Core/DirectX12/DirectXResourceTexture.h>

namespace Core {
  class DirectXCommon
  {
  public:
    DirectXCommon(Window* window);
    ~DirectXCommon();
    void Initialize();
    void Release();
    void Draw();
  private:
    void PreRenderer();
    void Renderer();
    void PostRenderer();



    DirectXFactory* factory;
    DirectXAdapter* adapter;
    DirectXDevice* device;
    DirectXInfoQueue* infoQueue;
    DirectXCommandQueue* commandQueue;
    DirectXCommandAllocator* allocator;
    DirectXCommandList* commandList;
    DirectXFence* fence;
    DirectXSwapChain* swapChain;
    DirectXDescriptorHeapRTV* rtvDescriptorHeap;
    DirectXDescriptorHeapSRV* srvDescriptorHeap;
    DirectXResourceTexture* resourceTexture;



    Window* window;

  };
}