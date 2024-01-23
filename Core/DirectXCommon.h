#pragma once

// #include <d3d12.h>
// #include <dxgi1_6.h>
//#include <Core/Window.h>
#include <wrl.h>
#include <vector>
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
class Window;


namespace Core {
  class DirectXCommon
  {
  public:
    DirectXCommon(Microsoft::WRL::ComPtr<Window> window);
    ~DirectXCommon();
    void Initialize();
    void Release();
    void Draw();
  private:
    void PreRenderer();
    void Renderer();
    void PostRenderer();



    Microsoft::WRL::ComPtr<DirectXFactory> factory;
    Microsoft::WRL::ComPtr<DirectXAdapter> adapter;
    Microsoft::WRL::ComPtr<DirectXDevice> device;
    Microsoft::WRL::ComPtr<DirectXInfoQueue> infoQueue;
    Microsoft::WRL::ComPtr<DirectXCommandQueue> commandQueue;
    Microsoft::WRL::ComPtr<DirectXCommandAllocator> allocator;
    Microsoft::WRL::ComPtr<DirectXCommandList> commandList;
    Microsoft::WRL::ComPtr<DirectXFence> fence;

    Microsoft::WRL::ComPtr<Window> window;

  };
}