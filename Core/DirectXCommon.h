#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>

class DirectXCommon
{
public:
  void Initialize();
  void Release();
  IDXGIFactory7* GetFactory();
  ID3D12Device* GetDevice();
private:
    void InitializeFactory();
    void InitializeAdapter();
    void InitializeDevice();


    IDXGIFactory7* dxgiFactory;
    IDXGIAdapter4* useAdapter;
    ID3D12Device* device;

};