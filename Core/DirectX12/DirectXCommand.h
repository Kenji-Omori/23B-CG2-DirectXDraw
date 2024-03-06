#pragma once

struct ID3D12CommandQueue;
struct ID3D12CommandAllocator;
struct ID3D12GraphicsCommandList;

namespace Core {
  class DirectXDevice;
  class DirectXCommand
  {
  public:
    DirectXCommand(DirectXDevice* device);
    ~DirectXCommand();

    void Setup();

  private:
    void CreateQueue();
    void CreateList();

    DirectXDevice* device;
    ID3D12CommandQueue* queue;
    ID3D12GraphicsCommandList* list;
    //D3D12_COMMAND_QUEUE_DESC desc;
  };
}