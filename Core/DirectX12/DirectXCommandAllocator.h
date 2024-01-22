
#pragma once

#include <memory>
class DirectXDevice;
struct ID3D12CommandAllocator;

class DirectXCommandAllocator
{
public:
	DirectXCommandAllocator(DirectXDevice* device);
	~DirectXCommandAllocator();
	ID3D12CommandAllocator* GetAllocator();
	void Release();
private:
	DirectXDevice* device;
	ID3D12CommandAllocator*  allocator;
};
