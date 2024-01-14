#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>

class DirectXCommon
{
public:
  void Initialize();
  void Release();
  IDXGIFactory7* GetFactory();
  ID3D12Device* GetDevice();
private:
    void InitializeDebugController();
    void InitializeFactory();
    void InitializeAdapter();
    void InitializeDevice();
    void InitializeInfoQueue();
    // new 
    void InitializeCommandQueue();
    void InitializeCommandAllocator();
    void InitializeCommandList();
    void InitializeFence();
    void InitializeCompiler();

    void CreateRootSignature();
    void CreateSwapChain();

    void PreRender();
    void Render();
    void PostRender();


    IDxcBlob* CompileShader(const std::wstring& filePath, const wchar_t* profile,IDxcUtils* dxcUtils,IDxcCompiler3* dxcCompiler,IDxcIncludeHandler* includeHandler);
    void CompileShaders();
    ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);
    void CreateGraphicsPipelineStateDesc();

    IDXGIFactory7* dxgiFactory;
    IDXGIAdapter4* useAdapter;
    ID3D12Device* device;
    ID3D12InfoQueue* infoQueue;
    ID3D12Debug1* debugController;
    ID3D12CommandQueue* commandQueue;
    D3D12_COMMAND_QUEUE_DESC commandQueueDesc;
    ID3D12CommandAllocator* commandAllocator;
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

    IDxcBlob* vertexShaderBlob;
    IDxcBlob* pixelShaderBlob;


};