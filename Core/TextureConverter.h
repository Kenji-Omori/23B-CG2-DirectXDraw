#pragma once
#include <string>
#include <Externals/DirectXTex/DirectXTex.h>
class TextureConverter
{

public:

  DirectX::ScratchImage LoadTexture(const std::string& filePath);

  /// <summary>
  /// テクスチャをWICからDDSに変換する
  /// </summary>
  /// <param name="filePath">ファイルパス</param>
  void ConvertTextureWICToDDS(const std::string& filePath);


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



private:
  DirectX::TexMetadata metaData_;
  DirectX::ScratchImage scratchImage_;


  std::wstring directoryPath_;
  std::wstring fileName_;
  std::wstring fileExt_;
};