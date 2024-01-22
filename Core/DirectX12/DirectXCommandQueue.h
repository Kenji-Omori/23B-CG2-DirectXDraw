#pragma once
#include <d3d12.h>
#include <memory>
class DirectXDevice;
struct ID3D12CommandQueue;
class DirectXCommandQueue
{
public:
	DirectXCommandQueue(DirectXDevice* device);
	~DirectXCommandQueue();
	void Release();

private:
	ID3D12CommandQueue* commandQueue;
	DirectXDevice* device;
};

