#include "DirectXCommandList.h"
#include <cassert>
#include <d3d12.h>
#include <Externals/DirectXTex/d3dx12.h>
#include <Core/DirectX12/DirectXDevice.h>
#include <Core/DirectX12/DirectXCommandAllocator.h>
#include <Core/DirectX12/DirectXSwapChain.h>
#include <Core/DirectX12/DirectXDescriptorHeap.h>
#include <Core/Window.h>
#include <Utility/Type/Color.h>
#include <Utility/Type/Vector2Int.h>

//クリア背景色
const Color Core::DirectXSwapChain::clearColor = Color( 0.1f,0.25f, 0.5f,0.0f ); 


Core::DirectXCommandList::DirectXCommandList(DirectXDevice* device, DirectXCommandAllocator* allocator)
{
  this->device = device;
  this->allocator = allocator;
  HRESULT hr = device->Get()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator->GetRaw() , nullptr, IID_PPV_ARGS(&commandList));
  // コマンドリストの生成がうまくいかなかったので起動できない
  assert(SUCCEEDED(hr));
}

Core::DirectXCommandList::~DirectXCommandList()
{
}

ID3D12GraphicsCommandList* Core::DirectXCommandList::GetCommandList()
{
  return commandList.Get();
}



void Core::DirectXCommandList::SetResourceBarrier(DirectXSwapChain* swapChain, UINT barrierNum)  
{
  CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
    swapChain->GetBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET,
    D3D12_RESOURCE_STATE_PRESENT);
  commandList->ResourceBarrier(1, &barrier);


}

void Core::DirectXCommandList::SetOutputMergeRenderTargets(DirectXDescriptorHeap* rtvHeap, DirectXDescriptorHeap* dsvHeap, UINT backBufferIndex)
{
  // レンダーターゲットビュー用ディスクリプタヒープのハンドルを取得
  CD3DX12_CPU_DESCRIPTOR_HANDLE rtvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(
    rtvHeap->GetCPUDescriptorHandleForHeapStart(), backBufferIndex,
    device->GetRTVIncrementSize());
  // 深度ステンシルビュー用デスクリプタヒープのハンドルを取得
  CD3DX12_CPU_DESCRIPTOR_HANDLE dsvH =
    CD3DX12_CPU_DESCRIPTOR_HANDLE(dsvHeap->GetCPUDescriptorHandleForHeapStart());
  // レンダーターゲットをセット
  commandList->OMSetRenderTargets(1, &rtvH, false, &dsvH);
}

void Core::DirectXCommandList::ClearRenderTarget(DirectXDescriptorHeap* rtvHeap, UINT backBufferIndex,const Color& clearColor)
{
  float bgColor[] = {
    clearColor.GetR(),
    clearColor.GetG(),
    clearColor.GetB(),
    clearColor.GetA()
  };


  // レンダーターゲットビュー用ディスクリプタヒープのハンドルを取得
  CD3DX12_CPU_DESCRIPTOR_HANDLE rtvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(
    rtvHeap->GetCPUDescriptorHandleForHeapStart(), backBufferIndex,
    device->GetRTVIncrementSize());

  commandList->ClearRenderTargetView(rtvH, bgColor, 0, nullptr);

}

void Core::DirectXCommandList::ClearDepthBuffer(DirectXDescriptorHeap* dsvHeap)
{
  // 深度ステンシルビュー用デスクリプタヒープのハンドルを取得
  CD3DX12_CPU_DESCRIPTOR_HANDLE dsvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(dsvHeap->GetCPUDescriptorHandleForHeapStart());
  // 深度バッファのクリア
  commandList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void Core::DirectXCommandList::SetResourceViewports(UINT viewportNum)
{
  Vector2Int windowResolution = device->GetWindow()->GetResolution();
  // ビューポートの設定
  CD3DX12_VIEWPORT viewport =
    CD3DX12_VIEWPORT(0.0f, 0.0f, float(windowResolution.x), float(windowResolution.y));
  commandList->RSSetViewports(viewportNum, &viewport);
}

void Core::DirectXCommandList::SetResourceScissorRects(UINT viewportNum)
{
  Vector2Int windowResolution = device->GetWindow()->GetResolution();
  // シザリング矩形の設定
  CD3DX12_RECT rect = CD3DX12_RECT(0, 0, windowResolution.x, windowResolution.y);
  commandList->RSSetScissorRects(viewportNum, &rect);
}

void Core::DirectXCommandList::SetDescriptorHeap(ID3D12DescriptorHeap* descriptorHeap)
{
  ID3D12DescriptorHeap* ppHeaps[] = { descriptorHeap };
  commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}

void Core::DirectXCommandList::SetDescriptorHeap(DirectXDescriptorHeap* descriptorHeap)
{
  SetDescriptorHeap(descriptorHeap->GetDescriptorHeap());
}

void Core::DirectXCommandList::Reset()
{
  commandList->Reset(allocator->GetRaw(), nullptr);
}


void Core::DirectXCommandList::Close()
{
  commandList->Close();
}

void Core::DirectXCommandList::Release()
{
  commandList->Release();
}
