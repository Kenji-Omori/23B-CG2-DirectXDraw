#pragma once
#include <wrl.h>
class DirectXFactory;
class DirectXCommandQueue;
struct IDXGISwapChain4;

namespace Core {
	class Window;
	class DirectXSwapChain
	{
	public:
		DirectXSwapChain(Window* window, DirectXFactory* factory, DirectXCommandQueue* commandQueue);
		~DirectXSwapChain();
		int GetBufferNum();

	private:
		void Setup();

		Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
		DirectXFactory* factory;
		DirectXCommandQueue* resources;
		unsigned char bufferNum;
	};

}