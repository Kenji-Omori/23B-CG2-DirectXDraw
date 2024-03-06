#pragma once

#include <d3d12.h>

namespace Core {
	class DirectXSwapChain;
	class DirectXCommand;
	class DirectXResourceBarrier
	{
	public:
		DirectXResourceBarrier(DirectXCommand* command, DirectXSwapChain* swapChain);
		~DirectXResourceBarrier();
		void InitializeDescs();
		void SwitchWriteMode();
		void SwitchViewMode();

	private:
		D3D12_RESOURCE_BARRIER writeModeDesc = {};
		D3D12_RESOURCE_BARRIER viewModeDesc = {};
		DirectXCommand* command;
		DirectXSwapChain* swapChain;
	};
}


