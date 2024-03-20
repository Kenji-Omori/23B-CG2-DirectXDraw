#pragma once
#include <Core/DirectX12/DirectXDescriptorHeap.h>
namespace Core
{
	class DirectXDevice;
	class Window;
	class DirectXDepthBuffer:public DirectXDescriptorHeap
	{
	public:
		DirectXDepthBuffer(DirectXDevice* device, Window* window);
		~DirectXDepthBuffer();

	private:
		ID3D12Resource* depthBuffer;

	};


}
