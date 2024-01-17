#include "DirectXResources.h"

#include<d3d12.h>

DirectXResources::DirectXResources()
{
}

DirectXResources::~DirectXResources()
{
  //delete[](colorBuffers);
}

void DirectXResources::CreateColorBuffers(unsigned char bufferNum)
{
  //colorBuffers = new ID3D12Resource*[bufferNum];
  for (unsigned char i = 0; i < bufferNum; i++)
  {
   // colorBuffers[i] = new ID3D12Resource>();
  }
}

ID3D12Resource* DirectXResources::GetResource(unsigned char index)
{
  return nullptr;// colorBuffers[index].get();
}

