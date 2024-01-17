#pragma once

#include <memory>
class DirectXDevice;
struct ID3D12CommandAllocator;

class DirectXCommandAllocator
{
public:
	DirectXCommandAllocator(DirectXDevice* device, unsigned char allocatorNum);
	~DirectXCommandAllocator();
	ID3D12CommandAllocator* GetAllocator(unsigned char index);
private:
	DirectXDevice* device;
	std::unique_ptr<ID3D12CommandAllocator* []> allocators;

	unsigned char allocatorNum;
};
