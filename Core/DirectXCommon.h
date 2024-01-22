#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <vector>
#include <Core/Window.h>
#include <memory>

class DirectXAdapter;
class DirectXCommand;
class DirectXDevice;
class DirectXFactory;
class DirectXFence;
class DirectXInfoQueue;
class DirectXCommandQueue;
class DirectXCommandAllocator;
class DirectXCommandList;



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

    Window* window;

  };
}