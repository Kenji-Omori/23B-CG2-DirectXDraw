
#pragma once

#include <wrl.h>
struct ID3D12CommandAllocator;

namespace Core {
	class DirectXDevice;
	class DirectXCommandAllocator
	{
	public:
		DirectXCommandAllocator(DirectXDevice* device);
		~DirectXCommandAllocator();
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> Get();
		ID3D12CommandAllocator* GetRaw();
		void Reset();
		void Release();
	private:
		DirectXDevice* device;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator>  allocator;
	};
}