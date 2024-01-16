#pragma once
#include <d3d12.h>
#include <memory>
class DirectXDevice;
class DirectXCommandQueue
{
public:
	DirectXCommandQueue(DirectXDevice* device, unsigned char allocatorNum);
	~DirectXCommandQueue();

private:
	DirectXDevice* device;
	D3D12_COMMAND_QUEUE_DESC desc;
	unsigned char allocatorNum;
};

