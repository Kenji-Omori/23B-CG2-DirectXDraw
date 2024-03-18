#pragma once
#include <d3d12.h>
#include <wrl.h>
struct ID3D12CommandQueue;
namespace Core {
	class DirectXDevice;
	class DirectXCommandList;
	class DirectXCommandQueue
	{
	public:
		DirectXCommandQueue(DirectXDevice* device);
		~DirectXCommandQueue();
		void Release();
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> Get();
		ID3D12CommandQueue* GetRaw();
		void ExcuteCommand(DirectXCommandList* commandList) const;
	private:
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
		DirectXDevice* device;
	};
}