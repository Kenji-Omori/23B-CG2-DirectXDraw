#include "DirectXResourceConstBuffer.h"
#include <Core/DirectX12/DirectXDevice.h>
#include <cassert>

Core::DirectXResourceConstBuffer::DirectXResourceConstBuffer(DirectXDevice* device, size_t size)
  :DirectXResource( 
    device,
    { // D3D12_RESOURCE_DESC
      D3D12_RESOURCE_DIMENSION_BUFFER,  // D3D12_RESOURCE_DIMENSION Dimension
      0,                                // UINT64 Alignment
      size,                             // UINT64 width
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
}

Core::DirectXResourceConstBuffer::~DirectXResourceConstBuffer()
{
}

void Core::DirectXResourceConstBuffer::CreateCommittedResource()
{
  HRESULT hr = GetDevice()->Get()->CreateCommittedResource(&properties, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&resource));
  assert(SUCCEEDED(hr));
}

