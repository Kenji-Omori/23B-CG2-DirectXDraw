#pragma once
#include <d3d12.h>

class DirectXDevice;
class ID3D12CommandQueue;
class ID3D12CommandAllocator;
class ID3D12GraphicsCommandList;

class DirectXCommand
{
public:
	DirectXCommand(DirectXDevice* device);
	~DirectXCommand();

	void Setup();

private:
	void CreateAllocator();
	void CreateQueue();
	void CreateList();

	DirectXDevice* device;
	ID3D12CommandAllocator* allocator;
	ID3D12CommandQueue* queue;
	ID3D12GraphicsCommandList* list;
	D3D12_COMMAND_QUEUE_DESC desc;
};