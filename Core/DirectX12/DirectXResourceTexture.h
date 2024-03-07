#pragma once
#include <Externals/DirectXTex/DirectXTex.h>
#include <Core/DirectX12/DirectXResource.h>
#include <string>
namespace Core {
  class DirectXResourceTexture :DirectXResource
  {
  public:
    DirectXResourceTexture(DirectXDevice* device, const std::string& filePath);
    ~DirectXResourceTexture();
    void LoadTexture(const std::string& filePath);

    /// <summary>
    /// テクスチャをWICからDDSに変換する
    /// </summary>
    /// <param name="filePath">ファイルパス</param>
    void ConvertTextureWICToDDS(const std::string& filePath);

    /// <summary>
    /// metaDataを取得する
    /// </summary>
    /// <returns></returns>
    const DirectX::TexMetadata& GetMetaData() const;

    // 最小テクスチャサイズ
    static const int MIN_WIDTH = 4;
    static const int MIN_HEIGHT = 4;

  private:
    /// <summary>
    /// マルチバイト文字列をワイド文字列に変換
    /// </summary>
    /// <param name="mString">マルチバイト文字列</param>
    /// <returns>ワイド文字列</returns>
    static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);


    /// <summary>
    /// テクスチャファイル読み込み
    /// </summary>
    /// <param name="filePath">ファイルパス</param>
    void LoadWICTextureFromFile(const std::string& filePath);

    /// <summary>
    /// フォルダパスとファイル名を分離する
    /// </summary>
    /// <param name="filePath">ファイルパス</param>
    void SeparateFilePath(const std::wstring& filePath);


    /// <summary>
    /// DDSテクスチャとしてファイル書き出し
    /// </summary>
    void SaveDDSTextureToFile();

    /// <summary>
    /// DirectXDeviceとmetadataからID3D12Resourceデータを生成する。
    /// </summary>
    void CreateTextureResource();

    /// <summary>
    /// Resrouceを作成したのち、unMapのImageにSubresourceする(？？？)
    /// </summary>
    void WriteMipMaps();
    

    DirectX::ScratchImage mipImages;

    DirectX::TexMetadata metaData;
    DirectX::ScratchImage scratchImage;


    std::wstring directoryPath;
    std::wstring fileName;
    std::wstring fileExt;
  };

}