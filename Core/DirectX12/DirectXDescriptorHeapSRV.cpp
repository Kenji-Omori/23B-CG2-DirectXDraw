#include "DirectXDescriptorHeapSRV.h"

DirectXDescriptorHeapSRV::DirectXDescriptorHeapSRV(DirectXDevice* device, UINT num):
  DirectXDescriptorHeap(device)
{
  descriptorHeapDesc =
  {
    D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,     // D3D12_DESCRIPTOR_HEAP_TYPE  Type;
      num,                                        // UINT                        NumDescriptors;
      D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,  // D3D12_DESCRIPTOR_HEAP_FLAGS Flags;
      0                                           // UINT                        NodeMask;
  };
  Create();
}

DirectXDescriptorHeapSRV::~DirectXDescriptorHeapSRV()
{
}
