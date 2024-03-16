#include "DirectXAdapter.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <Core/DirectX12/DirectXFactory.h>
#include <Utility/Debug.h>
#include <format>
#include <vector>


Core::DirectXAdapter::DirectXAdapter(DirectXFactory* factory)
{
  this->factory = factory;

  // アダプターの列挙用
  std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter4>> adapters;
  // Factoryからアダプター一覧を取得する
  // パフォーマンスが高いものから順に、全てのアダプターを列挙する
  Microsoft::WRL::ComPtr<IDXGIAdapter4> tmpAdapter;
  for (UINT i = 0; factory->Get()->EnumAdapterByGpuPreference(
    i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&tmpAdapter)) !=
    DXGI_ERROR_NOT_FOUND;
    i++) {
    // 動的配列に追加する
    adapters.push_back(tmpAdapter);
  }

  HRESULT result = S_FALSE;



  // 良い順にアダプタを頼む
  for (UINT i = 0; factory->Get()->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter)) != DXGI_ERROR_NOT_FOUND; ++i) {
    // アダプターの情報を取得する
    DXGI_ADAPTER_DESC3 adapterDesc{};
    HRESULT hr = adapter->GetDesc3(&adapterDesc);
    assert(SUCCEEDED(hr)); // 取得できないのは一大事
    // ソフトウェアアダプタでなければ採用！
    if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
      // 採用したアダプタの情報をログに出力。wstringの方なので注意
      Utility::Debug::Log(std::format(L"Use Adapater:{}\n", adapterDesc.Description));
      break;
    }
    adapter = nullptr; // ソフトウェアアダプタの場合は見なかったことにする
  }
  // 適切なアダプタが見つからなかったので起動できない
  assert(adapter != nullptr);


}

Core::DirectXAdapter::~DirectXAdapter()
{
}

Microsoft::WRL::ComPtr <IDXGIAdapter4> Core::DirectXAdapter::Get() const
{
  return adapter;
}

IDXGIAdapter4* Core::DirectXAdapter::GetRaw() const
{
  return adapter.Get();
}

Core::DirectXFactory* Core::DirectXAdapter::GetFactory() const
{
    return factory;
}

void Core::DirectXAdapter::Release()
{
  adapter->Release();
}
