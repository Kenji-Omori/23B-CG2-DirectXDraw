#pragma once

#include <memory>
struct ID3D12Resource;
class DirectXResources
{
public:
  DirectXResources();
  ~DirectXResources();
  void CreateColorBuffers(unsigned char bufferNum);
  ID3D12Resource* GetResource(unsigned char index);

private:
  //ID3D12Resource* colorBuffers[];

};
