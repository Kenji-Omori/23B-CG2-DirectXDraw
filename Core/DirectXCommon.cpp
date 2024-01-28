#include "DirectXCommon.h"

#include <dxgidebug.h>
#include <dxcapi.h>
#include <format>
#include <cassert>
#include <Core/Debug.h>
#include <Core/Type/Matrix4x4.h>
#include <Core/Type/Vector4.h>
#include <Core/Type/VertexData.h>

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
#include <Core/DirectX12/DirectXSwapChain.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")




Core::DirectXCommon::DirectXCommon(Window* window)
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
  swapChain = nullptr;

}

Core::DirectXCommon::~DirectXCommon()
{
}

void Core::DirectXCommon::Initialize()
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
  //swapchain * 1;
  swapChain = new DirectXSwapChain(window, factory, commandQueue,2);


  //descriptor(Resources) * (rtv, srv, dsv)
  //pipeline * ShaderNum;
  //rootSignature * pipeline



  //PreDraw
  //pipeline更新
  //rootSignature 更新
  //descriptor(Resources) 更新

  //Draw
  //各描画処理


  //PostDraw
  //

  Debug::Log("Complete create D3D12Device!!!\n");// 初期化完了のログをだす
}


void Core::DirectXCommon::Release()
{
  delete(fence);
  delete(commandList);
  delete(allocator);
  delete(commandQueue);
  delete(device);
  delete(adapter);
  delete(factory);

#ifdef _DEBUG
  //debugController->Release();
#endif
}

void Core::DirectXCommon::Draw()
{
  PreRenderer();
  Renderer();
  PostRenderer();
}

void Core::DirectXCommon::PreRenderer()
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
void Core::DirectXCommon::Renderer()
{


}
void Core::DirectXCommon::PostRenderer()
{
}

