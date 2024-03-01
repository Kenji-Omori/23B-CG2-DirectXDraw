#include "DirectXShader.h"

#include <cassert>
#include <algorithm>
#include <dxcapi.h>
#include <format>

#include <Core/Type/String.h>
#include <Core/Utilitys.h>
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

void DirectXShader::CreateGraphicPipeline()
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

IDxcBlob* DirectXShader::CompileShader(const std::string& filePath, ShaderType shaderType)
{

  std::wstring wFilePath = StrToWStr(filePath);
  const wchar_t* profile;

  switch (shaderType)
  {
  case DirectXShader::ShaderType::VertexShader:
    profile = L"vs_6_0";
    break;
  case DirectXShader::ShaderType::PixelShader:
    profile = L"ps_6_0";
    break;
  default:
    assert(false);
    profile = nullptr;
    break;
  }



  IDxcBlobEncoding* shaderSource = nullptr;
  Utilitys::Log(std::format(L"Begin CompileShader, path:{}, profile:{}\n", filePath, profile));
  HRESULT hr = dxcUtils->LoadFile(wFilePath.c_str(), nullptr, &shaderSource);
  // 読めなかったら止める
  assert(SUCCEEDED(hr));
  // 呼んだシェーダファイルの設定
  DxcBuffer shaderSourceBuffer;
  shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
  shaderSourceBuffer.Size = shaderSource->GetBufferSize();
  shaderSourceBuffer.Encoding = DXC_CP_UTF8; // UTF8の文字コードであることを通知




  LPCWSTR arguments[] = {
    wFilePath.c_str(), // コンパイル対象のhlslファイル名
    L"-E", L"main", // エントリーポイントの指定。基本的にmain以外にはしない
    L"-T", profile, // ShaderProfileの設定
    L"-Zi", L"-Qembed_debug",   // デバッグ用の情報を埋め込む
    L"-Od",     // 最適化を外しておく
    L"-Zpr",    // メモリレイアウトは行優先
  };

  // 実際にShaderをコンパイルする
  IDxcResult* compiledResult = nullptr;
  hr = dxcCompiler->Compile(
    &shaderSourceBuffer,    // 読み込んだファイル
    arguments,              // コンパイルオプション
    _countof(arguments),    // コンパイルオプションの数
    includeHandler,         // includeが含まれた諸々
    IID_PPV_ARGS(&compiledResult) // コンパイル結果
  );
  // コンパイルエラーではなくdxcが起動できないなど致命的な状況
  assert(SUCCEEDED(hr));
  bool isError = CheckIsCompileError(compiledResult);
  if (!isError) {
    Utilitys::Log(std::format(L"Compile Succeeded, path:{}, profile:{}\n", filePath, profile));

  }
  IDxcBlob* shaderBlob = nullptr;
  hr = compiledResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
  assert(SUCCEEDED(hr));

  shaderSource->Release();
  compiledResult->Release();
  return shaderBlob;
}

bool DirectXShader::CheckIsCompileError(IDxcResult* result)
{
  // 3. 警告・エラーがでていないか確認する
// 警告・エラーが出てたらログに出して止める
  IDxcBlobUtf8* shaderError = nullptr;
  result->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);
  if (shaderError != nullptr && shaderError->GetStringLength() != 0) {
    Utilitys::Log(shaderError->GetStringPointer());
    // 警告・エラーダメゼッタイ
    assert(false);
    return true;
  }
  return false;
}
