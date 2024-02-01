#include "DirectXDescriptorHeapRTV.h"

DirectXDescriptorHeapRTV::DirectXDescriptorHeapRTV(DirectXDevice* device, UINT num): DirectXDescriptorHeap(device)
{
  descriptorHeapDesc = { // D3D12_DESCRIPTOR_HEAP_DESC
    D3D12_DESCRIPTOR_HEAP_TYPE_RTV,   // D3D12_DESCRIPTOR_HEAP_TYPE  Type;
    num,                              // UINT                        NumDescriptors;
    D3D12_DESCRIPTOR_HEAP_FLAG_NONE,  // D3D12_DESCRIPTOR_HEAP_FLAGS Flags;
    0                                 // UINT                        NodeMask;
  };
  Create();
}

DirectXDescriptorHeapRTV::~DirectXDescriptorHeapRTV()
{
}
