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
//class DirectXSwapChain;

//struct Plane {
//  Vector2 position;
//  Vector2 size;
//};

namespace Core {
  class DirectXCommon
  {
  public:
    DirectXCommon(Window* window);
    void Initialize();
    void Release();
    void Draw();
  private:
    //void InitializeDebugController();
    //// new 
    //void InitializeCompiler();

    //void CreateRootSignature();

    // PreRenderer群
    void PreRenderer();
//    void CreateVertexResource(int vertexNum);
    // Renderer群
    void Renderer();
    // PostRenderer群
    void PostRenderer();


    //IDxcBlob* CompileShader(const std::wstring& filePath, const wchar_t* profile, IDxcUtils* dxcUtils, IDxcCompiler3* dxcCompiler, IDxcIncludeHandler* includeHandler);
    //void CompileShaders();
    //ID3D12Resource* CreateBufferResource(size_t sizeInBytes);
    //void CreateGraphicsPipelineStateDesc();

    DirectXFactory* factory;
    DirectXAdapter* adapter;
    DirectXDevice* device;


    //std::unique_ptr<DirectXFactory> factory;
    //std::unique_ptr<DirectXAdapter> adapter;
    //std::unique_ptr<DirectXDevice> device;
    //std::unique_ptr<DirectXCommand> command;
    //std::unique_ptr<DirectXFence> fence;
    //std::unique_ptr<DirectXInfoQueue> infoQueue;
//    std::unique_ptr<DirectXSwapChain> swapChain;

    //int planeNum;
    //int vertexNum;
    //VertexData* vertexData;
    //Plane planes[10];
    Window* window;

  };
}