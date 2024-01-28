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
		DirectXSwapChain(Window* window, DirectXFactory* factory, DirectXCommandQueue* commandQueue, int bufferNum);
		~DirectXSwapChain();
		int GetBufferNum();

	private:
		void Setup();

		Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
		DirectXFactory* factory;
		DirectXCommandQueue* resources;
		int bufferNum;
	};

}