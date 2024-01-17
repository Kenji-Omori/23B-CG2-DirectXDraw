
//#include <cstdint>
//#include <string>
//#include <format>
//#include <dxgidebug.h>
//#include <dxcapi.h>
//

#include <memory>
#include <Core/Window.h>

#include <Core/Type/Vector2.h>
#include <Core/Type/Vector4.h>
#include <Core/Type/Matrix4x4.h>
#include <Core/DirectXCommon.h>


#include "Externals/imgui/imgui.h"
#include "Externals/imgui/imgui_impl_dx12.h"
#include "Externals/imgui/imgui_impl_win32.h"

#include "Externals/DirectXTex/DirectXTex.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>




#pragma region comments






//IDxcBlob* CompileShader(
//  // CompilerするShaderファイルへのパス
//  const std::wstring& filePath,
//  // Compilerに使用するProfile
//  const wchar_t* profile,
//  // 初期化で生成したものを3つ
//  IDxcUtils* dxcUtils,
//  IDxcCompiler3* dxcCompiler,
//  IDxcIncludeHandler* includeHandler)
//{
//  // ここの中身をこの後書いていく
//  // 1. hlslファイルを読む
//  // これからシェーダーをコンパイルする旨をログに出す
//  //Omory::Debug::Log(ConvertString(std::format(L"Begin CompileShader, path:{}, profile:{}\n", filePath, profile)));
//  // hlslファイルを読む
//  IDxcBlobEncoding* shaderSource = nullptr;
//  HRESULT hr = dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource);
//  // 読めなかったら止める
//  assert(SUCCEEDED(hr));
//  // 読み込んだファイルの内容を設定する
//  DxcBuffer shaderSourceBuffer;
//  shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
//  shaderSourceBuffer.Size = shaderSource->GetBufferSize();
//  shaderSourceBuffer.Encoding = DXC_CP_UTF8; // UTF8の文字コードであることを通知
//
//
//  // 2. Compileする
//  LPCWSTR arguments[] = {
//    filePath.c_str(), // コンパイル対象のhlslファイル名
//    L"-E", L"main", // エントリーポイントの指定。基本的にmain以外にはしない
//    L"-T", profile, // ShaderProfileの設定
//    L"-Zi", L"-Qembed_debug",   // デバッグ用の情報を埋め込む
//    L"-Od",     // 最適化を外しておく
//    L"-Zpr",    // メモリレイアウトは行優先
//  };
//  // 実際にShaderをコンパイルする
//  IDxcResult* shaderResult = nullptr;
//  hr = dxcCompiler->Compile(
//    &shaderSourceBuffer,    // 読み込んだファイル
//    arguments,              // コンパイルオプション
//    _countof(arguments),    // コンパイルオプションの数
//    includeHandler,         // includeが含まれた諸々
//    IID_PPV_ARGS(&shaderResult) // コンパイル結果
//  );
//  // コンパイルエラーではなくdxcが起動できないなど致命的な状況
//  assert(SUCCEEDED(hr));
//
//
//  // 3. 警告・エラーがでていないか確認する
//  // 警告・エラーが出てたらログに出して止める
//  IDxcBlobUtf8* shaderError = nullptr;
//  shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);
//  if (shaderError != nullptr && shaderError->GetStringLength() != 0) {
//    //Omory::Debug::Log(shaderError->GetStringPointer());
//    // 警告・エラーダメゼッタイ
//    assert(false);
//  }
//
//
//  // 4. Compile結果を受け取って返す
//  // コンパイル結果から実行用のバイナリ部分を取得
//  IDxcBlob* shaderBlob = nullptr;
//  hr = shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
//  assert(SUCCEEDED(hr));
//  // 成功したログを出す
//  //Omory::Debug::Log(ConvertString(std::format(L"Compile Succeeded, path:{}, profile:{}\n", filePath, profile)));
//  // もう使わないリソースを解放
//  shaderSource->Release();
//  shaderResult->Release();
//  // 実行用のバイナリを返却
//  return shaderBlob;
//
//
//}
//ID3D12Resource resource;
//ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInBytes)
//{
//  // 頂点リソース用のヒープの設定
//  D3D12_HEAP_PROPERTIES uploadHeapProperties{};
//  uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;// UploadHeapを使う
//  // 頂点リソースの設定
//  D3D12_RESOURCE_DESC resourceDesc{};
//  // バッファリソース。テクスチャの場合はまた別の設定をする
//  resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
//  resourceDesc.Width = sizeInBytes;// リソースのサイズ。
//  // バッファの場合はこれらは1にする決まり
//  resourceDesc.Height = 1;
//  resourceDesc.DepthOrArraySize = 1;
//  resourceDesc.MipLevels = 1;
//  resourceDesc.SampleDesc.Count = 1;
//  // バッファの場合はこれにする決まり
//  resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
//  // 実際に頂点リソースを作る
//  ID3D12Resource* resource = nullptr;
//  HRESULT hr = device->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&resource));
//  assert(SUCCEEDED(hr));
//  return resource;
//
//}

//ID3D12DescriptorHeap* CreateDescriptorHeap(
//  ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible)
//{
//  ID3D12DescriptorHeap* descriptorHeap = nullptr;
//  D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc{};
//  descriptorHeapDesc.Type = heapType;
//  descriptorHeapDesc.NumDescriptors = numDescriptors;
//  descriptorHeapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
//  HRESULT hr = device->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&descriptorHeap));
//  assert(SUCCEEDED(hr));
//  return descriptorHeap;
//}

//DirectX::ScratchImage LoadTexture(const std::string& filePath)
//{
//  
//
//  // テクスチャファイルを読んでプログラムで扱えるようにする
//  DirectX::ScratchImage image{};
//  std::wstring filePathW = ConvertString(filePath);
//  HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
//  assert(SUCCEEDED(hr));
//
//  // ミップマップの作成
//  DirectX::ScratchImage mipImages{};
//  hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
//  assert(SUCCEEDED(hr));
//
//  // ミップマップ付きのデータを返す
//  return mipImages;
//}

//ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata)
//{
//  // 1. metadataを基にResourceの設定
//  // // metadataを基にResourceの設定
//  D3D12_RESOURCE_DESC resourceDesc{};
//  resourceDesc.Width = UINT(metadata.width); // Textureの幅
//  resourceDesc.Height = UINT(metadata.height); // Textureの高さ
//  resourceDesc.MipLevels = UINT16(metadata.mipLevels); // mipmapの数
//  resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize); // 奥行き or 配列Textureの配列数
//  resourceDesc.Format = metadata.format; // TextureのFormat
//  resourceDesc.SampleDesc.Count = 1; // サンプリングカウント。1固定。
//  resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension); // Textureの次元数。普段使っているのは2次元
//
//
//
//  // 2. 利用するHeapの設定
//  // 利用するHeapの設定。非常に特殊な運用。02_04exで一般的なケース版がある
//  D3D12_HEAP_PROPERTIES heapProperties{};
//  heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM; // 細かい設定を行う
//  heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK; // WriteBackポリシーでCPUアクセス可能
//  heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0; //　プロセッサの近くに配置
//
//  // 3. Resourceを生成する
//  // Resourceの生成
//  ID3D12Resource* resource = nullptr;
//  HRESULT hr = device->CreateCommittedResource(
//    &heapProperties, // Heapの設定
//    D3D12_HEAP_FLAG_NONE, // Heapの特殊な設定。特になし。
//    &resourceDesc,  // Resourceの設定
//    D3D12_RESOURCE_STATE_GENERIC_READ,  // 初回のResourceState。Textureは基本読むだけ
//    nullptr, // Clear最適値。使わないのでnullptr
//    IID_PPV_ARGS(&resource)); // 作成するResourceポインタへのポインタ
//  assert(SUCCEEDED(hr));
//  return resource;
//
//}
//
//void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages)
//{
//  // Meta情報を取得
//  const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
//  // 全MipMapについて
//  for (size_t mipLevel = 0; mipLevel < metadata.mipLevels; ++mipLevel) {
//    // MipMapLevelを指定して各Imageを取得
//    const DirectX::Image* img = mipImages.GetImage(mipLevel, 0, 0);
//    // Textureに転送
//    HRESULT hr = texture->WriteToSubresource(
//      UINT(mipLevel),
//      nullptr,              // 全領域へコピー
//      img->pixels,          // 元データアドレス
//      UINT(img->rowPitch),  // 1ラインサイズ
//      UINT(img->slicePitch) // 1枚サイズ
//    );
//    assert(SUCCEEDED(hr));
//  }
//}







#pragma endregion 


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

  HRESULT result = CoInitializeEx(0, COINIT_MULTITHREADED);
  assert(SUCCEEDED(result));

  OutputDebugStringA("Hello, DirectX!\n");
  Core::Window* window;
  Core::DirectXCommon* renderer;
  
  window = new Core::Window();
  window->Initialize();
  renderer = new Core::DirectXCommon(window);

  renderer->Initialize();

  window->Show();
  renderer->Draw();


  delete(renderer);
  delete(window);
  CoUninitialize();
  return 0;
}
