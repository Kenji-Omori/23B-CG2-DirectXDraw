#pragma once

#include <Core/DirectX12/DirectXDescriptorHeap.h>
#include <vector>
#include <string>

namespace Core {
	class DirectXResourceTexture;
	class DirectXDescriptorHeapSRV :DirectXDescriptorHeap
	{
	public:
		static const int DESCRIPTOR_NUM = 128;
		DirectXDescriptorHeapSRV(DirectXDevice* device, UINT num);
		~DirectXDescriptorHeapSRV();

		int LoadTexture(const std::string& filePath);
	private:
		void CreateShaderResourceView();
		void CreateDescriptorHeap();

		UINT descriptorHandleIncrementSize = 0;
		int nextResourceIndex = 0;

		DirectXResourceTexture* resources[DESCRIPTOR_NUM];
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap;
	};
}