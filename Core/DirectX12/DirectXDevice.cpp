#include "DirectXDevice.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <Utility/Debug.h>
#include <Core/DirectX12/DirectXAdapter.h>
#include <Core/DirectX12/DirectXFactory.h>
#include <Core/Window.h>
#include <format>

Core::DirectXDevice::DirectXDevice(DirectXAdapter* adapter)
{
  this->adapter = adapter;
  D3D_FEATURE_LEVEL featureLevels[] = {
    D3D_FEATURE_LEVEL_12_2, D3D_FEATURE_LEVEL_12_1, D3D_FEATURE_LEVEL_12_0
  };
  const char* featureLevelStrings[] = { "12.2", "12.1", "12.0" };
  // 高い順に生成できるか試していく
  for (size_t i = 0; i < _countof(featureLevels); ++i) {
    // 採用したアダプターでデバイスを生成
    HRESULT hr = D3D12CreateDevice(adapter->GetRaw(), featureLevels[i], IID_PPV_ARGS(&device));
    // 指定した機能レベルでデバイスが生成できたかを確認
    if (SUCCEEDED(hr)) {
      // 生成できたのでログ出力を行ってループを抜ける
      Utility::Debug::Log(std::format("FeatureLevel : {}\n", featureLevelStrings[i]));
      break;
    }
  }
  Utility::Debug::Log("Complete create D3D12Device!!!\n");// 初期化完了のログをだす

  // デバイスの生成がうまくいかなかったので起動できない
  assert(device != nullptr);
}

Core::DirectXDevice::~DirectXDevice()
{
}

Microsoft::WRL::ComPtr <ID3D12Device> Core::DirectXDevice::Get() const
{
  return device;
}

Core::DirectXAdapter* Core::DirectXDevice::GetAdapter() const
{
    return adapter;
}

Core::DirectXFactory* Core::DirectXDevice::GetFactory() const
{
  return adapter->GetFactory();
}

Core::Window* Core::DirectXDevice::GetWindow() const
{
  return GetFactory()->GetWindow();
}

void Core::DirectXDevice::Release()
{
  device->Release();
}
