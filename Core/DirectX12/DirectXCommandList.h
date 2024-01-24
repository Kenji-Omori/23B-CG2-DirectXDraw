#pragma once
#include <wrl.h>


class DirectXDevice;
class DirectXCommandAllocator;
struct ID3D12GraphicsCommandList;
class DirectXCommandList
{
public:
	DirectXCommandList(DirectXDevice* device, DirectXCommandAllocator* allocator);
	~DirectXCommandList();
	void Release();

private:
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	DirectXDevice* device;
	DirectXCommandAllocator* allocator;
};
