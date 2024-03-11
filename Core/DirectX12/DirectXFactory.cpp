#include "DirectXFactory.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>

Core::DirectXFactory::DirectXFactory()
{
#ifdef _DEBUG
	EnableDebugLayer();
#endif 
	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));
  assert(SUCCEEDED(hr));



	D3D_FEATURE_LEVEL levels[] = {
	D3D_FEATURE_LEVEL_12_1,
	D3D_FEATURE_LEVEL_12_0,
	D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL_11_0,
	};








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

void Core::DirectXFactory::EnableDebugLayer()
{
#ifdef _DEBUG
	Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
	//デバッグレイヤーをオンに
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
	}
	// DREDレポートをオンに
	Microsoft::WRL::ComPtr<ID3D12DeviceRemovedExtendedDataSettings> dredSettings;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&dredSettings)))) {
		dredSettings->SetAutoBreadcrumbsEnablement(D3D12_DRED_ENABLEMENT_FORCED_ON);
		dredSettings->SetPageFaultEnablement(D3D12_DRED_ENABLEMENT_FORCED_ON);
	}
#endif
}




