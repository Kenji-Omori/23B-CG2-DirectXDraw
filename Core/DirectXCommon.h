#pragma once

#include <wrl.h>
#include <vector>
#include <memory>

#include <string>

struct IDxcIncludeHandler;
struct IDxcCompiler3;
struct IDxcUtils;
struct IDxcBlob;
namespace Core {
  class Window;
  class DirectXSwapChain;
  class DirectXSwapChainBuffers;
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
  class DirectXDepthBuffer;
  class DirectXCommon
  {
  public:
    DirectXCommon(Window* window);
    ~DirectXCommon();
    void Initialize();
    void Release();
    void Draw();
  private:
    void PreDraw();
    void CurDraw();
    void PostDraw();
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
    DirectXCommandAllocator* cmdAllocator;
    DirectXCommandList* commandList;
    DirectXSwapChain* swapChain;
    DirectXDepthBuffer* depthBuffer;

    DirectXFence* fence;

    DirectXResourceTexture* resourceTexture;



    Window* window;
    static const int SWAP_CHAIN_BUFFER_NUM = 2;
  };
}