#pragma once
#include <wrl.h>
struct IDXGIFactory7;
namespace Core {
  class Window;
  class DirectXFactory
  {
  public:
    DirectXFactory(Window* window);
    ~DirectXFactory();
    void Release();
    Microsoft::WRL::ComPtr<IDXGIFactory7> Get() const;

  private:
    void EnableDebugLayer();
    Microsoft::WRL::ComPtr<IDXGIFactory7> factory;
    Window* window;
  };
}