#include "DirectXSwapChain.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <Core/Window.h>
#include <Core/DirectX12/DirectXFactory.h>
#include <Core/DirectX12/DirectXCommandQueue.h>

namespace Core {
  DirectXSwapChain::DirectXSwapChain(Window* window, DirectXFactory* factory, DirectXCommandQueue* commandQueue)
  {
    this->factory = factory;
    this->bufferNum = bufferNum;
    this->resources = resources;

    swapChainDesc.Width = window->GetResolution().x; // 画面の幅。ウィンドウのクライアント領域を同じものにしておく
    swapChainDesc.Height = window->GetResolution().y;   // 画面の高さ。ウィンドウのクライアント領域を同じものにしておく
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // 色の形式
    swapChainDesc.SampleDesc.Count = 1; // マルチサンプルしない
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 描画のターゲットとして利用する
    swapChainDesc.BufferCount = 2;  // ダブルバッファ
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // モニタにうつしたら、中身を破棄
    // コマンドキュー、ウィンドウハンドル、設定を渡して生成する
    Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain1;
    HRESULT hr = factory->Get()->CreateSwapChainForHwnd(commandQueue->GetRaw(), window->GetWindowHandle(), &swapChainDesc, nullptr, nullptr, &swapChain1);
    assert(SUCCEEDED(hr));
    swapChain1.As(&swapChain);


  }

  DirectXSwapChain::~DirectXSwapChain()
  {
  }

  int DirectXSwapChain::GetBufferNum()
  {
    return bufferNum;
  }

  void DirectXSwapChain::Setup()
  {

  }
}