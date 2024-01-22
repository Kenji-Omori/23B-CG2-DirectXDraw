#include "DirectXDevice.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <Core/Debug.h>
#include <Core/DirectX12/DirectXAdapter.h>
#include <format>

DirectXDevice::DirectXDevice(DirectXAdapter* adapter)
{
  {  D3D_FEATURE_LEVEL featureLevels[] = {
    D3D_FEATURE_LEVEL_12_2, D3D_FEATURE_LEVEL_12_1, D3D_FEATURE_LEVEL_12_0
  };
  const char* featureLevelStrings[] = { "12.2", "12.1", "12.0" };
  // 高い順に生成できるか試していく
  for (size_t i = 0; i < _countof(featureLevels); ++i) {
    // 採用したアダプターでデバイスを生成
    HRESULT hr = D3D12CreateDevice(adapter->Get(), featureLevels[i], IID_PPV_ARGS(&device));
    // 指定した機能レベルでデバイスが生成できたかを確認
    if (SUCCEEDED(hr)) {
      // 生成できたのでログ出力を行ってループを抜ける
      Core::Debug::Log(std::format("FeatureLevel : {}\n", featureLevelStrings[i]));
      break;
    }
  }
  Core::Debug::Log("Complete create D3D12Device!!!\n");// 初期化完了のログをだす

  // デバイスの生成がうまくいかなかったので起動できない
  assert(device != nullptr);
  }
}

DirectXDevice::~DirectXDevice()
{
  assert(device == nullptr);
}

ID3D12Device* DirectXDevice::Get() const
{
  return device;
}

void DirectXDevice::Release()
{
  device->Release();
  device = nullptr;
}
