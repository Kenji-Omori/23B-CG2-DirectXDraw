#include "ImGui.h"
#include <Core/DirectX12/DirectXDevice.h>
#include <Core/DirectX12/DirectXSwapChain.h>
#include <d3d12.h>
#include <Externals/DirectXTex/d3dx12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <Externals/imgui/imgui.h>

Core::ImGuiWrap::ImGuiWrap(DirectXDevice* device, DirectXSwapChain* swapChain)
{ 
	HRESULT result = S_FALSE;

	// デスクリプタヒープを生成
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.NumDescriptors = 1;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	result = device->Get()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&imguiHeap_));
	assert(SUCCEEDED(result));

	// スワップチェーンの情報を取得
	DXGI_SWAP_CHAIN_DESC swcDesc = {};
	result = swapChain->GetDesc(&swcDesc);
	assert(SUCCEEDED(result));

	if (ImGui::CreateContext() == nullptr) {
		assert(0);
	}
	if (!ImGui_ImplWin32_Init(device->GetWindow()->GetHwnd())) {
		assert(0);
	}
	if (!ImGui_ImplDX12_Init(
		GetDevice(), swcDesc.BufferCount, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, imguiHeap_.Get(),
		imguiHeap_->GetCPUDescriptorHandleForHeapStart(),
		imguiHeap_->GetGPUDescriptorHandleForHeapStart())) {
		assert(0);
	}
}