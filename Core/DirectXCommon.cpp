#include "DirectXCommon.h"

#include <dxgidebug.h>
#include <dxcapi.h>
#include <format>
#include <cassert>
#include <Core/Debug.h>
#include <Core/Type/Matrix4x4.h>
#include <Core/Type/Vector4.h>
#include <Core/Type/VertexData.h>

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

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")


namespace Core {
  DirectXCommon::DirectXCommon(Microsoft::WRL::ComPtr<Window> window)
  {
    this->window = window;
    factory = nullptr;
    adapter = nullptr;
    device = nullptr;
    allocator = nullptr;
    commandList = nullptr;
    commandQueue = nullptr;
    fence = nullptr;
    infoQueue = nullptr;

  }

  DirectXCommon::~DirectXCommon()
  {
  }

  void DirectXCommon::Initialize()
  {
    // Device
    factory = new DirectXFactory();
    adapter = new DirectXAdapter(factory);
    device = new DirectXDevice(adapter);
    infoQueue = new DirectXInfoQueue(device);
    commandQueue = new DirectXCommandQueue(device);
    allocator = new DirectXCommandAllocator(device);
    commandList = new DirectXCommandList(device, allocator);
    fence = new DirectXFence(device);


    Debug::Log("Complete create D3D12Device!!!\n");// 初期化完了のログをだす
  }


  void DirectXCommon::Release()
  {
    fence->Release();
    commandList->Release();
    allocator->Release();
    commandQueue->Release();
    device->Release();
    adapter->Release();
    factory->Release();

#ifdef _DEBUG
    //debugController->Release();
#endif
  }

  void DirectXCommon::Draw()
  {
    PreRenderer();
    Renderer();
    PostRenderer();
  }

  void DirectXCommon::PreRenderer()
  {

    float onePixel = 2.f / 512.f;
    float texSize = 512;
    float sizes[] = {
      texSize * onePixel / 1.f,
      texSize * onePixel / 2.f,
      texSize * onePixel / 4.f,
      texSize * onePixel / 8.f,
      texSize * onePixel / 16.f,
      texSize * onePixel / 32.f,
      texSize * onePixel / 64.f,
      texSize * onePixel / 128.f,
      texSize * onePixel / 256.f,
      texSize * onePixel / 512.f,
    };
  }
  void DirectXCommon::Renderer()
  {

 
    }
  void DirectXCommon::PostRenderer()
  {
  }
}
 