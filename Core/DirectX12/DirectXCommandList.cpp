#include "DirectXCommandList.h"
#include <cassert>
#include <d3d12.h>
#include <Externals/DirectXTex/d3dx12.h>
#include <Core/DirectX12/DirectXDevice.h>
#include <Core/DirectX12/DirectXCommandAllocator.h>
#include <Core/DirectX12/DirectXSwapChain.h>
#include <Core/DirectX12/DirectXDescriptorHeap.h>
#include <Utility/Type/Color.h>

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

ID3D12CommandList* Core::DirectXCommandList::GetCommandList()
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

void Core::DirectXCommandList::SetOutputMergeRenderTargets(DirectXDescriptorHeap* rtvHeap, DirectXDescriptorHeap* dsvHeap)
{
  // レンダーターゲットビュー用ディスクリプタヒープのハンドルを取得
  CD3DX12_CPU_DESCRIPTOR_HANDLE rtvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(
    rtvHeap_->GetCPUDescriptorHandleForHeapStart(), bbIndex,
    device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
  // 深度ステンシルビュー用デスクリプタヒープのハンドルを取得
  CD3DX12_CPU_DESCRIPTOR_HANDLE dsvH =
    CD3DX12_CPU_DESCRIPTOR_HANDLE(dsvHeap_->GetCPUDescriptorHandleForHeapStart());
  // レンダーターゲットをセット
  commandList_->OMSetRenderTargets(1, &rtvH, false, &dsvH);
}

void Core::DirectXCommandList::ClearRenderTarget(DirectXDescriptorHeap* rtvHeap, UINT backBufferIndex, const Color& clearColor)
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


void Core::DirectXCommandList::Close()
{
  commandList->Close();
}

void Core::DirectXCommandList::Release()
{
  commandList->Release();
}
