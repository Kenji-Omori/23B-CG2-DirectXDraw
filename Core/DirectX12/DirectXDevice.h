#pragma once

#include <wrl.h>
struct ID3D12Device;

namespace Core {
	class Window;
	class DirectXFactory;
	class DirectXAdapter;
	class DirectXDevice
	{
	public:
		DirectXDevice(DirectXAdapter* adapter);
		~DirectXDevice();
		Microsoft::WRL::ComPtr<ID3D12Device> Get() const;
		ID3D12Device* GetRaw();
		DirectXAdapter* GetAdapter() const;
		DirectXFactory* GetFactory() const;
		Window* GetWindow() const;
		UINT GetRTVIncrementSize();
		void Release();

	private:
		Microsoft::WRL::ComPtr<ID3D12Device> device;
		DirectXAdapter* adapter;
	};
}