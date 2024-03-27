
//#include <cstdint>
//#include <string>
//#include <format>
//#include <dxgidebug.h>
//#include <dxcapi.h>
//

#include <memory>
#include <Core/Window.h>

#include <Utility/Type/Vector2.h>
#include <Utility/Type/Vector4.h>
#include <Utility/Type/Matrix4x4.h>
#include <Core/DirectXCommon.h>


#include "Externals/imgui/imgui.h"
#include "Externals/imgui/imgui_impl_dx12.h"
#include "Externals/imgui/imgui_impl_win32.h"

#include "Externals/DirectXTex/DirectXTex.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <Utility/Input.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

  HRESULT result = CoInitializeEx(0, COINIT_MULTITHREADED);
  assert(SUCCEEDED(result));

  OutputDebugStringA("Hello, DirectX!\n");
  Core::Window* window;
  Core::DirectXCommon* renderer;
  Input* input = Input::GetInstance();
  
  window = new Core::Window();
  window->Initialize();
  renderer = new Core::DirectXCommon(window);

  renderer->Initialize();

  window->Show();

  while (!window->IsCallQuitMessage())
  {
    input->Update();
    renderer->Draw();
    if (window->IsCallCloseMessage()) { continue; }
  }

  renderer->Release();
  delete(renderer);
  delete(window);
  CoUninitialize();
  return 0;
}
