#include "DirectX12Shader.h"

#include <cassert>
#include <algorithm>
#include <dxcapi.h>
#include <Core/Type/String.h>
#include <Core/DirectX12/DirectXDevice.h>

DirectXShader::DirectXShader(DirectXDevice* device)
{
  this->device  = device;
  HRESULT hr;
  // Utilsの初期化
  hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils));
  assert(SUCCEEDED(hr));
  // Compilerの初期化
  hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler));
  assert(SUCCEEDED(hr));
  // IncludeHandlerの初期化
  hr = dxcUtils->CreateDefaultIncludeHandler(&includeHandler);
  assert(SUCCEEDED(hr));
}

DirectXShader::~DirectXShader()
{

}

void DirectXShader::LoadVertexShader(const std::string& path)
{
  IDxcBlobEncoding* shaderSource = nullptr;
  HRESULT hr = dxcUtils->LoadFile( StrToWStr(path).c_str(), nullptr, &shaderSource);
  assert(SUCCEEDED(hr));

  // 読み込んだファイルの内容を設定する
  DxcBuffer shaderSourceBuffer;
  shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
  shaderSourceBuffer.Size = shaderSource->GetBufferSize();
  shaderSourceBuffer.Encoding = DXC_CP_UTF8; // UTF8の文字コードであることを通知

  // Todo:ShaderLoader周りがんばれ


}

void DirectXShader::LoadPixelShader(const std::string& path)
{

}

int DirectXShader::AddElemet(D3D12_INPUT_ELEMENT_DESC desc)
{
  assert(MAX_ELEMENT_NUM < variableElementsIndex);
  elementsArray[variableElementsIndex] = desc;
  variableElementsIndex++;
  return variableElementsIndex-1;
}


int DirectXShader::AddElemet(LPCSTR semanticName, UINT semanticIndex, DXGI_FORMAT format, UINT inputSlot, UINT alignedByteOffset, D3D12_INPUT_CLASSIFICATION inputSlotClass, UINT instanceDataStepRate)
{
  return AddElemet({
    semanticName,
    semanticIndex,
    format,
    inputSlot,
    alignedByteOffset,
    inputSlotClass,
    instanceDataStepRate
  });
}

void DirectXShader::Compile()
{
  
  D3D12_INPUT_LAYOUT_DESC inputLayoutDesc = 
  {
    elementsArray,
    variableElementsIndex+1
  };
  SetBlendDesc();
  SetRasterizerDesc();

  D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
  graphicsPipelineStateDesc.pRootSignature = rootSignature;// RootSignature
  graphicsPipelineStateDesc.InputLayout = inputLayoutDesc;// InputLayout
  graphicsPipelineStateDesc.VS = { vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize() };// VertexShader
  graphicsPipelineStateDesc.PS = { pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize() };// PixelShader
  graphicsPipelineStateDesc.BlendState = blendDesc;// BlendState
  graphicsPipelineStateDesc.RasterizerState = rasterizerDesc;// RasterizerState
  // 書き込むRTVの情報
  graphicsPipelineStateDesc.NumRenderTargets = 1;
  graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
  // 利用するトポロジ（形状）のタイプ。三角形
  graphicsPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
  // どのように画面に色を打ち込むかの設定（気にしなくて良い）
  graphicsPipelineStateDesc.SampleDesc.Count = 1;
  graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;


  HRESULT hr = device->Get()->CreateGraphicsPipelineState(&graphicsPipelineStateDesc, IID_PPV_ARGS(&graphicsPipelineState));
  assert(SUCCEEDED(hr));
}

void DirectXShader::CreateRootSignature()
{
  HRESULT hr = device->Get()->CreateRootSignature(0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
  assert(SUCCEEDED(hr));
}

void DirectXShader::SetBlendDesc()
{
  blendDesc = {};
  blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
}

void DirectXShader::SetRasterizerDesc()
{
  rasterizerDesc = {};
  rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
  rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
}
