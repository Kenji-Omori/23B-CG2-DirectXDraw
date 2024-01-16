#include "DirectXSwapChain.h"


#include <Core/DirectX12/DirectXFactory.h>
#include <Core/DirectX12/DirectXResources.h>


DirectXSwapChain::DirectXSwapChain(DirectXFactory* factory, DirectXResources* resources, unsigned char bufferNum)
{
  this->factory = factory;
  this->bufferNum = bufferNum;
  this->resources = resources;
}

DirectXSwapChain::~DirectXSwapChain()
{
}

int DirectXSwapChain::GetBufferNum()
{
  return bufferNum;
}

void DirectXSwapChain::Setup()
{

}
