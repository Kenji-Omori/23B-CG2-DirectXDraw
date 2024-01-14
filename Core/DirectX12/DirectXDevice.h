#pragma once

class ID3D12Device;
class DirectXAdapter;

class DirectXDevice
{
public:
	DirectXDevice(DirectXAdapter* adapter);
	~DirectXDevice();
	ID3D12Device* Get() const;
	void Release();

private:
	ID3D12Device* device;
};