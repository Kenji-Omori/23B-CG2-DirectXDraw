#pragma once
#include <d3d12.h>
#include <wrl.h>
class DirectXDevice;
struct ID3D12CommandQueue;
class DirectXCommandQueue
{
public:
	DirectXCommandQueue(Microsoft::WRL::ComPtr<DirectXDevice> device);
	~DirectXCommandQueue();
	void Release();

private:
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	Microsoft::WRL::ComPtr<DirectXDevice> device;
};

