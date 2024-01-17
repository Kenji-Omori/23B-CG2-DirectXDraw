#pragma once
#include <d3d12.h>
#include <memory>
class DirectXDevice;
class DirectXCommandAllocator;

class DirectXCommandQueue
{
public:
	DirectXCommandQueue(DirectXDevice* device, DirectXCommandAllocator* allocator);
	~DirectXCommandQueue();

private:
	DirectXDevice* device;
	DirectXCommandAllocator* allocator;
//	D3D12_COMMAND_QUEUE_DESC desc;
//	unsigned char allocatorNum;
};

