#pragma once

#include <memory>
class ID3D12Resource;
class DirectXResources
{
public:
  DirectXResources();
  ~DirectXResources();
  void CreateColorBuffers(unsigned char bufferNum);
  ID3D12Resource* GetResource(unsigned char index);

private:
  std::unique_ptr<std::unique_ptr<ID3D12Resource>[]> colorBuffers;

};
