#include "Window.h"
//#include <Core/DebugGUI.h>

#include <d3d12.h>
#include <dxgi1_2.h>
//#include <Externals/imgui/imgui.h>


//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


void Core::Window::Initialize()
{
  SetResolution(512, 512);
  wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.lpszClassName = L"CG2WindowClass";
  wc.hInstance = GetModuleHandle(nullptr);
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  RegisterClass(&wc);
  hwnd = CreateWindow(
    wc.lpszClassName,
    L"CG2",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    rect.right - rect.left,
    rect.bottom - rect.top,
    nullptr,
    nullptr,
    wc.hInstance,
    nullptr
  );

}

void Core::Window::SetResolution(int width, int height)
{
  rect = { 0, 0, width, height };
  AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU, false);
}

void Core::Window::Show()
{
  ShowWindow(hwnd, SW_SHOW);
}

void Core::Window::Close()
{
  CloseWindow(hwnd);
}

int Core::Window::GetWidth()
{
  return rect.right - rect.left;
}

int Core::Window::GetHeight()
{
  return rect.bottom - rect.top;
}

const HWND& Core::Window::GetWindowHandle()
{
  return hwnd;
}



LRESULT CALLBACK Core::Window::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  //if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
  //  return true;
  //}

  switch (msg)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  default:
    break;
  }
  return DefWindowProc(hwnd, msg, wparam, lparam);
}
