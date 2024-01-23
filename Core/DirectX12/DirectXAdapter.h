#pragma once
#include <wrl.h>
struct IDXGIAdapter4;
class DirectXFactory;

class DirectXAdapter
{
public:
	DirectXAdapter(Microsoft::WRL::ComPtr<DirectXFactory> factory);
	~DirectXAdapter();

	Microsoft::WRL::ComPtr<IDXGIAdapter4> Get() const;
	IDXGIAdapter4* GetRaw() const;
	void Release();

private:
	Microsoft::WRL::ComPtr<IDXGIAdapter4> adapter;
};
