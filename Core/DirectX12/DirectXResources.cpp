#include "DirectXResources.h"

#include<d3d12.h>

DirectXResources::DirectXResources()
{
}

DirectXResources::~DirectXResources()
{
}

void DirectXResources::CreateColorBuffers(unsigned char bufferNum)
{
  colorBuffers = std::make_unique<std::unique_ptr<ID3D12Resource>[]>(bufferNum);
  for (unsigned char i = 0; i < bufferNum; i++)
  {
    colorBuffers[i] = std::make_unique<ID3D12Resource>();
  }
}

ID3D12Resource* DirectXResources::GetResource(unsigned char index)
{
  return colorBuffers[index].get();
}

