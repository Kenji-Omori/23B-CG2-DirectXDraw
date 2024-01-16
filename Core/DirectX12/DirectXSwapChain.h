#pragma once

class DirectXFactory;
class DirectXResources;

class DirectXSwapChain
{
public:
	DirectXSwapChain(DirectXFactory* factory, DirectXResources* resources, unsigned char bufferNum);
	~DirectXSwapChain();
	int GetBufferNum();

private:
	void Setup();


	DirectXFactory* factory;
	DirectXResources* resources;
	unsigned char bufferNum;
};

