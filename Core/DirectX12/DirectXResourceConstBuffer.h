#pragma once

#include <Core/DirectX12/DirectXResource.h>

class DirectXResourceConstBuffer: DirectXResource
{
public:
	DirectXResourceConstBuffer(DirectXDevice* device, size_t size);
	~DirectXResourceConstBuffer();

private:

};
