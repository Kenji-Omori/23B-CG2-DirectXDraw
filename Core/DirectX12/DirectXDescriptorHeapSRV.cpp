#include "DirectXDescriptorHeapSRV.h"
#include <Core/DirectX12/DirectXResourceTexture.h>
#include <Core/DirectX12/DirectXDevice.h>
#include <Externals/DirectXTex/DirectXTex.h>
#include <Externals/DirectXTex/d3dx12.h>
Core::DirectXDescriptorHeapSRV::DirectXDescriptorHeapSRV(DirectXDevice* device, UINT num):
  DirectXDescriptorHeap(device)
{
  descriptorHeapDesc =
  {
    D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,     // D3D12_DESCRIPTOR_HEAP_TYPE  Type;
      num,                                        // UINT                        NumDescriptors;
      D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,  // D3D12_DESCRIPTOR_HEAP_FLAGS Flags;
      0                                           // UINT                        NodeMask;
  };
  CreateDescriptorHeap();
}

Core::DirectXDescriptorHeapSRV::~DirectXDescriptorHeapSRV()
{
  for (auto t : resources)
  {
    if (t == nullptr) { continue; }
    delete(t);
  }
}

int Core::DirectXDescriptorHeapSRV::LoadTexture(const std::string& filePath)
{
  assert(nextResourceIndex < DESCRIPTOR_NUM);
  resources[nextResourceIndex] = new DirectXResourceTexture(GetDevice(), filePath);
  int resourceIndex = nextResourceIndex;
  nextResourceIndex++;
  return resourceIndex;
}

void Core::DirectXDescriptorHeapSRV::CreateShaderResourceView()
{
  assert(false);//この関数使うな

  UINT incrementSize = GetDevice()->Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
  for (int i = 0; i < nextResourceIndex; i++)
  {
    DirectXResourceTexture* resource = resources[i];

    // metaDataを基にSRVの設定
    DirectX::TexMetadata metadata = resource->GetMetaData();
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
    srvDesc.Format = resource->GetMetaData().format;
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
    srvDesc.Texture2D.MipLevels = UINT(metadata.mipLevels);



    //// SRVを作成するDescriptorHeapの場所を決める
    //D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU = CD3DX12_CPU_DESCRIPTOR_HANDLE(descriptorHeap->GetCPUDescriptorHandleForHeapStart(),i,incrementSize);
    //D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU = CD3DX12_GPU_DESCRIPTOR_HANDLE(descriptorHeap->GetGPUDescriptorHandleForHeapStart(),i,incrementSize);
    //// 先頭はImGuiが使っているのでその次を使う
    ////textureSrvHandleCPU.ptr += GetDevice()->Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    ////textureSrvHandleGPU.ptr += GetDevice()->Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    //// SRVの生成
    //GetDevice()->Get()->CreateShaderResourceView(textureResource, &srvDesc, textureSrvHandleCPU);
  }
}

//void Core::DirectXDescriptorHeapSRV::CreateDescriptorHeap()
//{
//  HRESULT result = S_FALSE;
//
//
//
//    D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
//    descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
//    descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; //シェーダから見えるように
//    descHeapDesc.NumDescriptors = UINT(DESCRIPTOR_NUM); // シェーダーリソースビューの数
//    result = GetDevice()->Get()->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap)); //生成
//    assert(SUCCEEDED(result));
//  }
//
//  // デスクリプタサイズを取得
//  descriptorHandleIncrementSize =
//    device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
//}
