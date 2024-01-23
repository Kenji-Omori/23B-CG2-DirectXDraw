#pragma once
#include <wrl.h>
struct IDXGIFactory7;

class DirectXFactory
{
public:
	DirectXFactory();
	~DirectXFactory();
	void Release();
	Microsoft::WRL::ComPtr<IDXGIFactory7> Get() const;

private:
 Microsoft::WRL::ComPtr<IDXGIFactory7> factory;
};
