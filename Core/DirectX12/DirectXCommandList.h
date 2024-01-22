#pragma once

class DirectXDevice;
struct ID3D12GraphicsCommandList;
class DirectXCommandList
{
public:
	DirectXCommandList(DirectXDevice* device);
	~DirectXCommandList();
	void Release();

private:
	ID3D12GraphicsCommandList* commandList;
	DirectXDevice* device;
};
