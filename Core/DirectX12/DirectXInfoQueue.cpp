#include "DirectXInfoQueue.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>

#include <Core/DirectX12/DirectXDevice.h>

DirectXInfoQueue::DirectXInfoQueue(DirectXDevice* device)
{
  this->device = device;
#ifdef _DEBUG
  ID3D12InfoQueue* infoQueue = nullptr;
  if (SUCCEEDED(device->Get()->QueryInterface(IID_PPV_ARGS(&infoQueue)))) {
    // ヤバイエラー時に止まる
    infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
    // エラー時に止まる
    infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
    // 警告時に止まる
    //infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);

    // 抑制するメッセージのID
    D3D12_MESSAGE_ID denyIds[] = {
      // Windows11でのDXGIデバッグレイヤーとDX12デバッグレイヤーの相互作用バグによるエラーメッセージ
      // https://stackoverflow.com/questions/69805245/directx-12-application-is-crashing-in-windows-11
      D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
    };
    // 抑制するレベル
    D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
    D3D12_INFO_QUEUE_FILTER filter{};
    filter.DenyList.NumIDs = _countof(denyIds);
    filter.DenyList.pIDList = denyIds;
    filter.DenyList.NumSeverities = _countof(severities);
    filter.DenyList.pSeverityList = severities;
    // 指定したメッセージの表示を抑制する
    infoQueue->PushStorageFilter(&filter);

    // 解放
    infoQueue->Release();
  }
#endif
}

DirectXInfoQueue::~DirectXInfoQueue()
{
}
