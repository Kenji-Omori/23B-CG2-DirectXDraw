#pragma once

class IDXGIFactory7;

class DirectXFactory
{
public:
	DirectXFactory();
	~DirectXFactory();
	void Release();
	IDXGIFactory7* Get() const;

private:
	IDXGIFactory7* factory;
};
