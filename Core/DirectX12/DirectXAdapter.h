#pragma once
#include <wrl.h>
struct IDXGIAdapter4;
namespace Core {
  class DirectXFactory;
  class DirectXAdapter
  {
  public:
    DirectXAdapter(DirectXFactory* factory);
    ~DirectXAdapter();

    Microsoft::WRL::ComPtr<IDXGIAdapter4> Get() const;
    IDXGIAdapter4* GetRaw() const;
    DirectXFactory* GetFactory() const;
    void Release();

  private:
    DirectXFactory* factory;
    Microsoft::WRL::ComPtr<IDXGIAdapter4> adapter;
  };
}