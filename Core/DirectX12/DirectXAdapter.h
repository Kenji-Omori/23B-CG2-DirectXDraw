#pragma once

class IDXGIAdapter4;
class DirectXFactory;

class DirectXAdapter
{
public:
	DirectXAdapter(DirectXFactory* factory);
	~DirectXAdapter();

	IDXGIAdapter4* Get() const;
	void Release();

private:
	IDXGIAdapter4* adapter;
};
