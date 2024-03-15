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
class Window;

#include <Core/Window.h>
#include <string>
//#include <Core/DirectX12/DirectXAdapter.h>
//#include <Core/DirectX12/DirectXCommand.h>
//#include <Core/DirectX12/DirectXDevice.h>
//#include <Core/DirectX12/DirectXFactory.h>
//#include <Core/DirectX12/DirectXFence.h>
//#include <Core/DirectX12/DirectXInfoQueue.h>
//#include <Core/DirectX12/DirectXSwapChain.h>
//#include <Core/DirectX12/DirectXCommandQueue.h>
//#include <Core/DirectX12/DirectXCommandAllocator.h>
//#include <Core/DirectX12/DirectXCommandList.h>
//#include <Core/DirectX12/DirectXDescriptorHeapRTV.h>
//#include <Core/DirectX12/DirectXDescriptorHeapSRV.h>
//#include <Core/DirectX12/DirectXResourceTexture.h>

struct IDxcIncludeHandler;
struct IDxcCompiler3;
struct IDxcUtils;
struct IDxcBlob;
namespace Core {
  class DirectXSwapChain;
  class DirectXDescriptorHeapSwapChainBuffers;
  class DirectXAdapter;
  class DirectXCommand;
  class DirectXFactory;
  class DirectXDevice;
  class DirectXInfoQueue;
  class DirectXCommandQueue;
  class DirectXCommandAllocator;
  class DirectXCommandList;
  class DirectXFence;
  class DirectXDescriptorHeapRTV;
  class DirectXDescriptorHeapSRV;
  class DirectXResourceTexture;

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
    void CreateCommandClasses();
    IDxcBlob* CompileShader(
      // CompilerするShaderファイルへのパス
      const std::wstring& filePath,
      // Compilerに使用するProfile
      const wchar_t* profile,
      // 初期化で生成したものを3つ
      IDxcUtils* dxcUtils,
      IDxcCompiler3* dxcCompiler,
      IDxcIncludeHandler* includeHandler);
   // void ShaderSetup();
    void ModelSetup();


    DirectXFactory* factory;
    DirectXAdapter* adapter;
    DirectXDevice* device;
    DirectXInfoQueue* infoQueue;

    DirectXCommandQueue* commandQueue;
    DirectXCommandAllocator* allocator;
    DirectXCommandList* commandList;
    DirectXSwapChain* swapChain;
    DirectXDescriptorHeapSwapChainBuffers* backBuffers;

    DirectXFence* fence;
    DirectXDescriptorHeapRTV* rtvDescriptorHeap;
    DirectXDescriptorHeapSRV* srvDescriptorHeap;
//    DirectXResourceTexture* resourceTexture;



    Window* window;
    static const int SWAP_CHAIN_BUFFER_NUM = 2;
  };
}