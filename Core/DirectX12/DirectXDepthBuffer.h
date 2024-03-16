#pragma once
#include <Core/DirectX12/DirectXDescriptorHeap.h>
#include <wrl.h>
namespace Core
{
	class DirectXDevice;
	class Window;
	class DirectXDepthBuffer:DirectXDescriptorHeap
	{
	public:
		DirectXDepthBuffer(DirectXDevice* device, Window* window);
		~DirectXDepthBuffer();

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer;

	};


}
