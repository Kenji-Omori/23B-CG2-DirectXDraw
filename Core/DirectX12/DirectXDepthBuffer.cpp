#include "DirectXDepthBuffer.h"
#include <Core/DirectX12/DirectXDevice.h>
#include <Core/Window.h>
#include <Externals/DirectXTex/d3dx12.h>
#include <cassert>

Core::DirectXDepthBuffer::DirectXDepthBuffer(DirectXDevice* device, Window* window):DirectXDescriptorHeap(device)
{
	HRESULT result = S_FALSE;

	// ヒーププロパティ
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	// リソース設定
	CD3DX12_RESOURCE_DESC depthResDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_D32_FLOAT, window->GetResolution().x, window->GetResolution().y, 1, 0, 1, 0,
		D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);
	CD3DX12_CLEAR_VALUE clearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);
	// リソースの生成
	result = device->Get()->CreateCommittedResource(
		&heapProps, D3D12_HEAP_FLAG_NONE, &depthResDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE, // 深度値書き込みに使用
		&clearValue, IID_PPV_ARGS(&depthBuffer));
	assert(SUCCEEDED(result));

	// 深度ビュー用デスクリプタヒープ作成
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;                    // 深度ビューは1つ
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // デプスステンシルビュー
	result = device->Get()->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&descriptorHeap));
	assert(SUCCEEDED(result));

	// 深度ビュー作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	device->Get()->CreateDepthStencilView(
		depthBuffer.Get(), &dsvDesc, descriptorHeap->GetCPUDescriptorHandleForHeapStart());
}

Core::DirectXDepthBuffer::~DirectXDepthBuffer()
{
}
