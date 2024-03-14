#pragma once

#include <d3d12.h>

struct ID3D12DescriptorHeap;

namespace Core {
	class DirectXDevice;
	class DirectXDescriptorHeap
	{
	public:
		DirectXDescriptorHeap(DirectXDevice* device, D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc);
		DirectXDescriptorHeap(DirectXDevice* device);
		~DirectXDescriptorHeap();
		ID3D12DescriptorHeap* Get();
	protected:
		void CreateDescriptorHeap();
		DirectXDevice* GetDevice() const;
		D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc;
		ID3D12DescriptorHeap* descriptorHeap;
	private:
		DirectXDevice* device;

	};
}