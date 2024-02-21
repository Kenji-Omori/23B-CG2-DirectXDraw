#pragma once

#include <Core/DirectX12/DirectXDescriptorHeap.h>
#include <vector>
#include <string>


class DirectXResourceTexture;
class DirectXDescriptorHeapSRV:DirectXDescriptorHeap
{
public:
	DirectXDescriptorHeapSRV(DirectXDevice* device, UINT num);
	~DirectXDescriptorHeapSRV();

	int LoadTexture( const std::string& filePath);
private:
	std::vector<DirectXResourceTexture*> textures;
};
