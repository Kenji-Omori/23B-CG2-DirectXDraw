#pragma once

#include<Core/DirectX12/DirectXDescriptorHeap.h>
class DirectXDescriptorHeapRTV:DirectXDescriptorHeap
{
public:
	DirectXDescriptorHeapRTV(DirectXDevice* device, UINT num);
	~DirectXDescriptorHeapRTV();

private:

};
