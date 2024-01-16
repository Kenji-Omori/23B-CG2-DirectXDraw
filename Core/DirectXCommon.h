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

struct Plane {
  Vector2 position;
  Vector2 size;
};

namespace Core {
  class DirectXCommon
  {
  public:
    DirectXCommon(const Window* window);
    void Initialize();
    void Release();
  private:
    void InitializeDebugController();
    // new 
    void InitializeCompiler();

    void CreateRootSignature();
    void CreateSwapChain();

    // PreRenderer群
    void PreRenderer();
    void CreateVertexResource(int vertexNum);
    // Renderer群
    void Renderer();
    // PostRenderer群
    void PostRenderer();


    IDxcBlob* CompileShader(const std::wstring& filePath, const wchar_t* profile, IDxcUtils* dxcUtils, IDxcCompiler3* dxcCompiler, IDxcIncludeHandler* includeHandler);
    void CompileShaders();
    ID3D12Resource* CreateBufferResource(size_t sizeInBytes);
    void CreateGraphicsPipelineStateDesc();

    std::unique_ptr<DirectXAdapter> adapter;
    std::unique_ptr<DirectXCommand> command;
    std::unique_ptr<DirectXDevice> device;
    std::unique_ptr<DirectXFactory> factory;
    std::unique_ptr<DirectXFence> fence;
    std::unique_ptr<DirectXInfoQueue> infoQueue;

    /*
    IDXGIFactory7* dxgiFactory;
    IDXGIAdapter4* useAdapter;
    ID3D12Device* device;
    ID3D12InfoQueue* infoQueue;
    ID3D12Debug1* debugController;
    ID3D12CommandQueue* commandQueue;
    D3D12_COMMAND_QUEUE_DESC commandQueueDesc;
    ID3D12CommandAllocator* commandAllocator;

    std::vector<ID3D12CommandList*> commandLists;
    ID3D12GraphicsCommandList* commandList;

    ID3D12Fence* fence;
    HANDLE fenceEvent;
    IDxcUtils* dxcUtils;
    IDxcCompiler3* dxcCompiler;
    D3D12_BLEND_DESC blendDesc;
    D3D12_RASTERIZER_DESC rasterizerDesc;


    IDXGISwapChain4* swapChain;


    D3D12_INPUT_LAYOUT_DESC inputLayoutDesc;


    ID3D12RootSignature* rootSignature;
    IDxcIncludeHandler* includeHandler;



    D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature;
    D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc;

    ID3D12Resource* vertexResource;
    IDxcBlob* vertexShaderBlob;
    IDxcBlob* pixelShaderBlob;
    */

    int planeNum;
    int vertexNum;
    VertexData* vertexData;
    Plane planes[10];
    const Window* window;

  };
}