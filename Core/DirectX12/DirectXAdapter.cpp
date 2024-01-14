#include "DirectXAdapter.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <Core/DirectX12/DirectXFactory.h>


DirectXAdapter::DirectXAdapter(DirectXFactory* factory)
{
  // 良い順にアダプタを頼む
  for (UINT i = 0; factory->Get()->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter)) != DXGI_ERROR_NOT_FOUND; ++i) {
    // アダプターの情報を取得する
    DXGI_ADAPTER_DESC3 adapterDesc{};
    HRESULT hr = adapter->GetDesc3(&adapterDesc);
    assert(SUCCEEDED(hr)); // 取得できないのは一大事
    // ソフトウェアアダプタでなければ採用！
    if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
      // 採用したアダプタの情報をログに出力。wstringの方なので注意
      //Omory::Debug::Log(std::format(L"Use Adapater:{}\n", adapterDesc.Description));
      break;
    }
    adapter = nullptr; // ソフトウェアアダプタの場合は見なかったことにする
  }
  // 適切なアダプタが見つからなかったので起動できない
  assert(adapter != nullptr);


}

DirectXAdapter::~DirectXAdapter()
{
  assert(adapter == nullptr);
}

IDXGIAdapter4* DirectXAdapter::Get() const
{
  return adapter;
}

void DirectXAdapter::Release()
{
  adapter->Release();
}
