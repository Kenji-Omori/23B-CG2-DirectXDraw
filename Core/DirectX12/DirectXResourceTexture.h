#pragma once
#include <Externals/DirectXTex/DirectXTex.h>
#include <Core/DirectX12/DirectXResource.h>

class DirectXResourceTextre:DirectXResource
{
public:
	DirectXResourceTextre(DirectXDevice* device, const DirectX::TexMetadata& metadata);
	~DirectXResourceTextre();

private:
	DirectX::TexMetadata metadata;
};

