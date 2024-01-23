#pragma once

#include <wrl.h>
struct ID3D12Device;
class DirectXAdapter;

class DirectXDevice
{
public:
	DirectXDevice(Microsoft::WRL::ComPtr <DirectXAdapter> adapter);
	~DirectXDevice();
	Microsoft::WRL::ComPtr<ID3D12Device> Get() const;
	void Release();

private:
	Microsoft::WRL::ComPtr<ID3D12Device> device;
};