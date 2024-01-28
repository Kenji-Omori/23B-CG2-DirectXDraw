#include "DirectXResourceTexture.h"

DirectXResourceTextre::DirectXResourceTextre(DirectXDevice* device, const DirectX::TexMetadata& metadata)
  :DirectXResource( 
    device,
    { // D3D12_RESOURCE_DESC
      D3D12_RESOURCE_DIMENSION_BUFFER,  // D3D12_RESOURCE_DIMENSION Dimension
      0,                                // UINT64 Alignment
      0,                             // UINT64 width
      1,                                // UINT height
      1,                                // UINTR16 DepthOrArraySize
      1,                                // UINT16 MipLevels
      DXGI_FORMAT_UNKNOWN,              // DXGI_FORMAT Format
    {                                 // DXGI_SAMPLE_DESC SampleDesc
      1,                                // UINT count
      0                                 // UINT Quality
    },
    D3D12_TEXTURE_LAYOUT_ROW_MAJOR,   // D3D12_TEXTURE_LAYOUT Layout
    D3D12_RESOURCE_FLAG_NONE          // D3D12_RESOURCE_FLAGS Flags
    },
    { // D3D12_HEAP_PROPERTIES
      D3D12_HEAP_TYPE_UPLOAD,           // D3D12_HEAP_TYPE Type
      D3D12_CPU_PAGE_PROPERTY_UNKNOWN,  // D3D12_CPU_PAGE_PROPERTY CPUPageProperty;
      D3D12_MEMORY_POOL_UNKNOWN,        // D3D12_MEMORY_POOL MemoryPoolPreference;
      0,                                // UINT CreationNodeMask;
      0                                 // UINT VisibleNodeMask;
    }
  )
{
  this->metadata = metadata;
}

DirectXResourceTextre::~DirectXResourceTextre()
{
}
