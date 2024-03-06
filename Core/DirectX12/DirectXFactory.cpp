#include "DirectXFactory.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>

Core::DirectXFactory::DirectXFactory()
{
  HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));
  assert(SUCCEEDED(hr));
}

Core::DirectXFactory::~DirectXFactory()
{
}

void Core::DirectXFactory::Release()
{
  factory->Release();
}

Microsoft::WRL::ComPtr<IDXGIFactory7> Core::DirectXFactory::Get() const
{
  return factory;
}



