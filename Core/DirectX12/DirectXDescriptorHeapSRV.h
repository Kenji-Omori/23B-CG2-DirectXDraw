#pragma once

#include <Core/DirectX12/DirectXDescriptorHeap.h>

class DirectXDescriptorHeapSRV:DirectXDescriptorHeap
{
public:
	DirectXDescriptorHeapSRV(DirectXDevice* device, UINT num);
	~DirectXDescriptorHeapSRV();

private:

};
