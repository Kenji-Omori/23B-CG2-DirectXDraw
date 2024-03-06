#pragma once


#include <d3d12.h>
#include <vector>
#include <string>
#include <wrl.h>
#include <dxcapi.h>
//#include <d3d12.h>
struct IDxcBlob;
struct IDxcUtils;
struct IDxcCompiler3;
struct ID3D12RootSignature;
struct ID3D12PipelineState;
namespace Core {
  class DirectXDevice;
  class DirectXShader
  {
  public:
    enum class ShaderType
    {
      VertexShader,
      PixelShader
    };

    struct PipelinePair
    {
      Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
      Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineSate;
    };
  public:
    DirectXShader(DirectXDevice* device);
    ~DirectXShader();

    void LoadVertexShader(const std::string& path);
    void LoadPixelShader(const std::string& path);
    int AddElemet(const D3D12_INPUT_ELEMENT_DESC& desc);
    /// <summary>
    /// elementを追加する
    /// </summary>
    /// <param name="semanticName">セマンティクス名</param>
    /// <param name="semanticIndex">セマンティクスインデックス</param>
    /// <param name="format">フォーマット</param>
    /// <param name="inputSlot">インプットスロット。0-15</param>
    /// <param name="alignedByteOffset">頂点からここまでのオフセットバイト。省略可</param>
    /// <param name="inputSlotClass">1 つの入力スロットの入力データ クラスを識別する 値</param>
    /// <param name="instanceDataStepRate">1 つの要素によってバッファーに進む前に、同じインスタンスごとのデータを使用して描画するインスタンスの数。 </param>
    int AddElemet(
      LPCSTR semanticName,
      UINT semanticIndex,
      DXGI_FORMAT format,
      UINT inputSlot,
      UINT alignedByteOffset,
      D3D12_INPUT_CLASSIFICATION inputSlotClass,
      UINT instanceDataStepRate
    );
    void CreateGraphicPipeline();

  private:
    void CreateRootSignature();
    void SetBlendDesc();
    void SetRasterizerDesc();
    IDxcBlob* CompileShader(const std::string& filePath, ShaderType shaderType);
    bool CheckIsCompileError(IDxcResult* result);

    DirectXDevice* device = nullptr;
    IDxcUtils* dxcUtils = nullptr;
    IDxcCompiler3* dxcCompiler = nullptr;

    ID3DBlob* signatureBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;

    IDxcBlob* vertexShaderBlob = nullptr;
    IDxcBlob* pixelShaderBlob = nullptr;
    IDxcIncludeHandler* includeHandler = nullptr;


    D3D12_INPUT_LAYOUT_DESC inputLayout = {};
    UINT variableElementsIndex = 0;
    static const int MAX_ELEMENT_NUM = 16;
    D3D12_INPUT_ELEMENT_DESC elementsArray[MAX_ELEMENT_NUM] = {};

    D3D12_BLEND_DESC blendDesc = {};
    D3D12_RASTERIZER_DESC rasterizerDesc = {};

    ID3D12RootSignature* rootSignature = nullptr;
    ID3D12PipelineState* graphicsPipelineState = nullptr;

  };
}
