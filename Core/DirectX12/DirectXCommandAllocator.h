
#pragma once

#include <wrl.h>
class DirectXDevice;
struct ID3D12CommandAllocator;

class DirectXCommandAllocator
{
public:
	DirectXCommandAllocator(DirectXDevice* device);
	~DirectXCommandAllocator();
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> Get();
	ID3D12CommandAllocator* GetRaw();
	void Release();
private:
	DirectXDevice* device;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>  allocator;
};
