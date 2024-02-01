#pragma once

#include <d3d12.h>


class DirectXDevice;
struct ID3D12DescriptorHeap;
class DirectXDescriptorHeap
{
public:
	DirectXDescriptorHeap(DirectXDevice* device, D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc);
	DirectXDescriptorHeap(DirectXDevice* device);
	~DirectXDescriptorHeap();
	ID3D12DescriptorHeap* Get();
protected:
  void Create();
	D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc;
private:
	DirectXDevice* device;
	ID3D12DescriptorHeap* descriptorHeap;

};


