#include "TextureConverter.h"
#include <Windows.h>

using namespace DirectX;


DirectX::ScratchImage TextureConverter::LoadTexture(const std::string& filePath)
{
  // テクスチャファイルを読んでプログラムで扱えるようにする
//  DirectX::ScratchImage image{};
  std::wstring wFilePath = ConvertMultiByteStringToWideString(filePath);
  SeparateFilePath(wFilePath);

  HRESULT hr;


  int result = wcscmp(fileExt_.c_str(), L"dds");

  if(result == 0)
  {
   hr = LoadFromDDSFile(wFilePath.c_str(), DDS_FLAGS_NONE, &metaData_, scratchImage_);
  }
  else
  {
    hr = LoadFromWICFile(wFilePath.c_str(), WIC_FLAGS_NONE, &metaData_, scratchImage_);
  }

  assert(SUCCEEDED(hr));

  // ミップマップの作成
  //DirectX::ScratchImage mipImages{};
  //hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
  //assert(SUCCEEDED(hr));

  // ミップマップ付きのデータを返す;
  return std::move(scratchImage_);
}

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath)
{
  printf(filePath.c_str());
  printf("\n");
  //①テクスチャファイルを読み込む
  LoadWICTextureFromFile(filePath);

  //②DDS形式に変換して書き出す
  SaveDDSTextureToFile();
}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{
  int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);
  std::wstring wString;
  wString.resize(filePathBufferSize);

  MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], filePathBufferSize);
  return wString;
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
  // ①ファイルパスをワイド文字列に変換
  std::wstring wFilePath = ConvertMultiByteStringToWideString(filePath);
  // ②テクスチャを読み込む
  //WICテクスチャのロード
  HRESULT result = LoadFromWICFile(wFilePath.c_str(), WIC_FLAGS_NONE, &metaData_, scratchImage_);
  assert(SUCCEEDED(result));

  // フォルダパスとファイル名を分離する
  SeparateFilePath(wFilePath);
}

void TextureConverter::SeparateFilePath(const std::wstring& filePath)
{
  size_t pos1;
  std::wstring exceptExt;

  pos1 = filePath.rfind('.');
  if (pos1 != std::wstring::npos)
  {
    fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
    exceptExt = filePath.substr(0, pos1);
  }
  else
  {
    fileExt_ = L"";
    exceptExt = filePath;
  }

  // 区切り文字 '\\' が出てくる一番最後の部分を検索
  pos1 = exceptExt.rfind('\\');
  if (pos1 != std::wstring::npos) {
    // 区切り文字の前までをディレクトリパスとして保存
    directoryPath_ = exceptExt.substr(0, pos1 + 1);
    // 区切り文字の後ろをファイル名として保存
    fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
    return;
  }

  // 区切り文字 '/' が出てくる一番最後の部分を検索
  pos1 = exceptExt.rfind('/');
  if (pos1 != std::wstring::npos) {

    // 区切り文字の前までをディレクトリパスとして保存
    directoryPath_ = exceptExt.substr(0, pos1 + 1);
    // 区切り文字の後ろをファイル名として保存
    fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);



  }
  // 区切り文字がないのでファイル名のみとして扱う
  directoryPath_ = L"";
  fileName_ = exceptExt;

}

void TextureConverter::SaveDDSTextureToFile()
{
  metaData_.format = MakeSRGB(metaData_.format);

  std::wstring filePath = directoryPath_ + fileName_ + L".dds";

  HRESULT result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metaData_, DDS_FLAGS_NONE, filePath.c_str());
  assert(SUCCEEDED(result));
}


