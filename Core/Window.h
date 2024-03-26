#pragma once
#include <Windows.h>
#include <cstdint>

//#include <Externals/imgui/imgui_impl_dx12.h>
//#include <Externals/imgui/imgui_impl_win32.h>
#include <Utility/Type/Vector2.h>

#include <Utility/Type/Vector2Int.h>

namespace Core {
  class Window
  {
  public:
    Window();
    ~Window();
    void Initialize();
    void SetResolution(int width, int height);
    void Show();
    void Close();
    Vector2Int GetResolution();
    float GerResolutionRate();

    const HWND& GetWindowHandle();
    bool IsCallCloseMessage();
    bool IsCallQuitMessage();
    const HINSTANCE& GetWindowInstance();


  private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

    WNDCLASS wc;
    RECT rect;
    HWND hwnd;
    MSG msg;
  };
}
