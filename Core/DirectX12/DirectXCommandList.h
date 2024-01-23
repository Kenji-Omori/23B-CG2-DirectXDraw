#pragma once
#include <wrl.h>


class DirectXDevice;
class DirectXCommandAllocator;
struct ID3D12GraphicsCommandList;
class DirectXCommandList
{
public:
	DirectXCommandList(Microsoft::WRL::ComPtr<DirectXDevice> device, Microsoft::WRL::ComPtr<DirectXCommandAllocator> allocator);
	~DirectXCommandList();
	void Release();

private:
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<DirectXDevice> device;
	Microsoft::WRL::ComPtr<DirectXCommandAllocator> allocator;
};
