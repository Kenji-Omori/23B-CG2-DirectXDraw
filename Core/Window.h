#pragma once
#include <Windows.h>
#include <cstdint>

//#include <Externals/imgui/imgui_impl_dx12.h>
//#include <Externals/imgui/imgui_impl_win32.h>



namespace Core {
  class Window
  {
  public:
    void Initialize();
    void SetResolution(int width, int height);
    void Show();
    void Close();
    int GetWidth();
    int GetHeight();
    const HWND& GetWindowHandle();

  private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

    WNDCLASS wc;
    RECT rect;
    HWND hwnd;
  };
}