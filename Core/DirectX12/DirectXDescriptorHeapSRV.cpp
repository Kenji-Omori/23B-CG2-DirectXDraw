#include "DirectXDescriptorHeapSRV.h"
#include <Core/DirectX12/DirectXResourceTexture.h>

Core::DirectXDescriptorHeapSRV::DirectXDescriptorHeapSRV(DirectXDevice* device, UINT num):
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

Core::DirectXDescriptorHeapSRV::~DirectXDescriptorHeapSRV()
{
  for (auto t : textures)
  {
    delete(t);
  }
  textures.clear();
}

int Core::DirectXDescriptorHeapSRV::LoadTexture(const std::string& filePath)
{
  DirectXResourceTexture* texture = new DirectXResourceTexture(GetDevice());
  texture->LoadTexture(filePath);
  textures.push_back(texture);
  return int(textures.size());
}
