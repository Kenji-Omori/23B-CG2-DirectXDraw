#include "Window.h"
//#include <Core/DebugGUI.h>

#include <d3d12.h>
#include <dxgi1_2.h>
#include <Core/Type/Vector2Int.h>
//#include <Externals/imgui/imgui.h>


//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


Core::Window::Window()
{
  msg = {};
  rect = { 1024,720 };
  wc = {};
  hwnd = {};
}

Core::Window::~Window()
{
}

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

Vector2Int Core::Window::GetResolution()
{
  return {
    rect.right - rect.left,
    rect.bottom - rect.top
  };
}

float Core::Window::GerResolutionRate()
{
  Vector2Int resolution = GetResolution();
  return float(resolution.x) / resolution.y;
}

const HWND& Core::Window::GetWindowHandle()
{
  return hwnd;
}

bool Core::Window::IsCallCloseMessage()
{
  if (!PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { return false; }
  TranslateMessage(&msg);
  DispatchMessage(&msg);
  return true;
}

bool Core::Window::IsCallQuitMessage()
{
  return msg.message == WM_QUIT;
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
