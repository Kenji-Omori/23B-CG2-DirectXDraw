#include "DirectXFactory.h"

#include <Core/Window.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
Core::DirectXFactory::DirectXFactory(Window* window)
{
	this->window = window;
#ifdef _DEBUG
	EnableDebugLayer();
#endif 
	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));
  assert(SUCCEEDED(hr));

	// ウィンドウサイズ変更とAlt＋Enterのフルスクリーンの禁止
	factory->MakeWindowAssociation(window->GetWindowHandle(), DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER);

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

Core::Window* Core::DirectXFactory::GetWindow() const
{
	return window;
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




