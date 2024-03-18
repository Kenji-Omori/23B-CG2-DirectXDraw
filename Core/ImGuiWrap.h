#pragma once
#include <wrl.h>
struct ID3D12DescriptorHeap;
namespace Core {
	class DirectXDevice;
	class DirectXSwapChain;
	class ImGuiWrap
	{
	public:
		ImGuiWrap(DirectXDevice* device, DirectXSwapChain* swapChain);
		~ImGuiWrap();

	private:
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> imguiDescriptorHeap;
	};
}
