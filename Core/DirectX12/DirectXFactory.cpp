#include "DirectXFactory.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>

DirectXFactory::DirectXFactory()
{
  HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));
  assert(SUCCEEDED(hr));
}

DirectXFactory::~DirectXFactory()
{
  assert(factory == nullptr);
}

void DirectXFactory::Release()
{
  factory->Release();
}

IDXGIFactory7* DirectXFactory::Get() const
{
  return factory;
}