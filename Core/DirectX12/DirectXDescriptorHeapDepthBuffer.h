#pragma once
#include <Core/DirectX12/DirectXDescriptorHeap.h>
#include <wrl.h>
namespace Core
{
	class DirectXDevice;
	class Window;
	class DirectXDescriptorHeapDepthBuffer:DirectXDescriptorHeap
	{
	public:
		DirectXDescriptorHeapDepthBuffer(DirectXDevice* device, Window* window);
		~DirectXDescriptorHeapDepthBuffer();

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer;

	};


}
