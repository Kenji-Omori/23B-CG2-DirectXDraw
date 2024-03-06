#include "DirectXResourceTexture.h"
#include <Core/DirectX12/DirectXDevice.h>
#include <Externals/DirectXTex/DirectXTex.h>

Core::DirectXResourceTexture::DirectXResourceTexture(DirectXDevice* device, const DirectX::TexMetadata& metaData)
  :DirectXResource( 
    device,
    { // D3D12_RESOURCE_DESC
      D3D12_RESOURCE_DIMENSION_BUFFER,  // D3D12_RESOURCE_DIMENSION Dimension
      0,                                // UINT64 Alignment
      16,                             // UINT64 width
      1,                                // UINT height
      1,                                // UINTR16 DepthOrArraySize
      1,                                // UINT16 MipLevels
      DXGI_FORMAT_UNKNOWN,              // DXGI_FORMAT Format
    {                                 // DXGI_SAMPLE_DESC SampleDesc
      1,                                // UINT count
      0                                 // UINT Quality
    },
    D3D12_TEXTURE_LAYOUT_ROW_MAJOR,   // D3D12_TEXTURE_LAYOUT Layout
    D3D12_RESOURCE_FLAG_NONE          // D3D12_RESOURCE_FLAGS Flags
    },
    { // D3D12_HEAP_PROPERTIES
      D3D12_HEAP_TYPE_UPLOAD,           // D3D12_HEAP_TYPE Type
      D3D12_CPU_PAGE_PROPERTY_UNKNOWN,  // D3D12_CPU_PAGE_PROPERTY CPUPageProperty;
      D3D12_MEMORY_POOL_UNKNOWN,        // D3D12_MEMORY_POOL MemoryPoolPreference;
      0,                                // UINT CreationNodeMask;
      0                                 // UINT VisibleNodeMask;
    }
  )
{
  this->metaData = metaData;
}

Core::DirectXResourceTexture::~DirectXResourceTexture()
{
}

void Core::DirectXResourceTexture::LoadTexture(const std::string& filePath)
{
  // テクスチャファイルを読んでプログラムで扱えるようにする
  //  DirectX::ScratchImage image{};
  std::wstring wFilePath = ConvertMultiByteStringToWideString(filePath);
  SeparateFilePath(wFilePath);

  HRESULT hr;


  int result = wcscmp(fileExt_.c_str(), L"dds");

  if(result == 0)
  {
    hr = LoadFromDDSFile(wFilePath.c_str(), DDS_FLAGS_NONE, &metaData, scratchImage_);
  }
  else
  {
    hr = LoadFromWICFile(wFilePath.c_str(), WIC_FLAGS_NONE, &metaData, scratchImage_);
  }

  assert(SUCCEEDED(hr));

  // ミップマップの作成
  //DirectX::ScratchImage mipImages{};
  //hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
  //assert(SUCCEEDED(hr));

  // ミップマップ付きのデータを返す;
  mipImages = std::move(scratchImage_);
  metaData = mipImages.GetMetadata();

  // DeviceとmetaDataの準備ができたのでResrouceを作る
  CreateTextureResource();
  UploadTextureData();


}

void Core::DirectXResourceTexture::ConvertTextureWICToDDS(const std::string& filePath)
{
  //①テクスチャファイルを読み込む
  LoadWICTextureFromFile(filePath);

  //②DDS形式に変換して書き出す
  SaveDDSTextureToFile();
}

std::wstring Core::DirectXResourceTexture::ConvertMultiByteStringToWideString(const std::string& mString)
{
  int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);
  std::wstring wString;
  wString.resize(filePathBufferSize);

  MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], filePathBufferSize);
  return wString;
}

void Core::DirectXResourceTexture::LoadWICTextureFromFile(const std::string& filePath)
{
  // ①ファイルパスをワイド文字列に変換
  std::wstring wFilePath = ConvertMultiByteStringToWideString(filePath);
  // ②テクスチャを読み込む
  //WICテクスチャのロード
  HRESULT result = LoadFromWICFile(wFilePath.c_str(), WIC_FLAGS_NONE, &metaData, scratchImage_);
  assert(SUCCEEDED(result));

  // フォルダパスとファイル名を分離する
  SeparateFilePath(wFilePath);
}

void Core::DirectXResourceTexture::SeparateFilePath(const std::wstring& filePath)
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

void Core::DirectXResourceTexture::SaveDDSTextureToFile()
{
  metaData.format = MakeSRGB(metaData.format);

  std::wstring filePath = directoryPath_ + fileName_ + L".dds";

  HRESULT result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metaData, DDS_FLAGS_NONE, filePath.c_str());
  assert(SUCCEEDED(result));
}

void Core::DirectXResourceTexture::CreateTextureResource()
{
  assert(GetDevice()!=nullptr);
  assert(metaData.width >= MIN_WIDTH && metaData.height >= MIN_HEIGHT);

  D3D12_RESOURCE_DESC resourceDesc{};
  resourceDesc.Width = UINT(metaData.width); // Textureの幅
  resourceDesc.Height = UINT(metaData.height); // Textureの高さ
  resourceDesc.MipLevels = UINT16(metaData.mipLevels); // mipmapの数
  resourceDesc.DepthOrArraySize = UINT16(metaData.arraySize); // 奥行き or 配列Textureの配列数
  resourceDesc.Format = metaData.format; // TextureのFormat
  resourceDesc.SampleDesc.Count = 1; // サンプリングカウント。1固定。
  resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metaData.dimension); // Textureの次元数。普段使っているのは2次元



  // 2. 利用するHeapの設定
  // 利用するHeapの設定。非常に特殊な運用。02_04exで一般的なケース版がある
  D3D12_HEAP_PROPERTIES heapProperties{};
  heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM; // 細かい設定を行う
  heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK; // WriteBackポリシーでCPUアクセス可能
  heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0; //　プロセッサの近くに配置

  // 3. Resourceを生成する
  // Resourceの生成
  HRESULT hr = GetDevice()->Get()->CreateCommittedResource(
    &heapProperties, // Heapの設定
    D3D12_HEAP_FLAG_NONE, // Heapの特殊な設定。特になし。
    &resourceDesc,  // Resourceの設定
    D3D12_RESOURCE_STATE_GENERIC_READ,  // 初回のResourceState。Textureは基本読むだけ
    nullptr, // Clear最適値。使わないのでnullptr
    IID_PPV_ARGS(&resource)); // 作成するResourceポインタへのポインタ
  assert(SUCCEEDED(hr));
}

void Core::DirectXResourceTexture::UploadTextureData()
{
  assert(resource != nullptr);
  // Meta情報を取得
  const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
  // 全MipMapについて
  for (size_t mipLevel = 0; mipLevel < metadata.mipLevels; ++mipLevel) {
    // MipMapLevelを指定して各Imageを取得
    const DirectX::Image* img = mipImages.GetImage(mipLevel, 0, 0);
    // Textureに転送
    HRESULT hr = resource->WriteToSubresource(
      UINT(mipLevel),
      nullptr,              // 全領域へコピー
      img->pixels,          // 元データアドレス
      UINT(img->rowPitch),  // 1ラインサイズ
      UINT(img->slicePitch) // 1枚サイズ
    );
    assert(SUCCEEDED(hr));
  }
}
