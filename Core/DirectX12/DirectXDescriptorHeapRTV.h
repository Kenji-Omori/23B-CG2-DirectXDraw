#pragma once

#include<Core/DirectX12/DirectXDescriptorHeap.h>
namespace Core {
	class DirectXDescriptorHeapRTV :DirectXDescriptorHeap
	{
	public:
		DirectXDescriptorHeapRTV(DirectXDevice* device, UINT num);
		~DirectXDescriptorHeapRTV();

	private:

	};
}