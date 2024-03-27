#include "Input.h"
#include <Core/Window.h>
//#include <dinput.h>
#include <cassert>

#pragma comment(lib, "dinput8.lib")


void Input::Initialize(Core::Window* window)
{
  SetupDevice(window);
  SetupKeyboard(window);
  SetupMouse(window);

}

void Input::Update()
{
  UpdateKeyboard();
  UpdateMouse();
}

bool Input::IsKey(KeyCode key)
{
  BYTE index = KeycodeToByte(key);
  return curKey[index];
}

bool Input::IsKeyDown(KeyCode key)
{
  BYTE index = KeycodeToByte(key);
  return !preKey[index] && curKey[index];
}

bool Input::IsKeyRelease(KeyCode key)
{
  BYTE index = KeycodeToByte(key);
  return preKey[index] && !curKey[index];
}

BYTE Input::KeycodeToByte(KeyCode key)
{
  return 0;
}

bool Input::IsClick(MouseButton button)
{
  return curMouse.rgbButtons[int(button)];
}

bool Input::IsClickDown(MouseButton button)
{
  return !preMouse.rgbButtons[int(button)] && curMouse.rgbButtons[int(button)];
}

bool Input::IsClickUp(MouseButton button)
{
  return preMouse.rgbButtons[int(button)] && !curMouse.rgbButtons[int(button)];
}

void Input::SetupDevice(Core::Window* window)
{
  assert(dInput == nullptr);
  HRESULT hr = S_FALSE;
  HINSTANCE hInstance = window->GetWindowInstance();
  HWND hWnd = window->GetWindowHandle();
  hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, nullptr);
  assert(SUCCEEDED(hr));
}

void Input::SetupKeyboard(Core::Window* window)
{
  assert(dInput != nullptr);
  HRESULT hr = S_FALSE;
  HWND hWnd = window->GetWindowHandle();

  hr = dInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
  assert(SUCCEEDED(hr));

  hr = keyboard->SetDataFormat(&c_dfDIKeyboard);
  assert(SUCCEEDED(hr));

  // 排他制御レベルのセット
  hr = keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
  assert(SUCCEEDED(hr));
}

void Input::SetupMouse(Core::Window* window)
{
  assert(dInput != nullptr);
  HRESULT hr = S_FALSE;
  HWND hWnd = window->GetWindowHandle();

  hr = dInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
  assert(SUCCEEDED(hr));

  // 入力データ形式のセット
  hr = mouse->SetDataFormat(&c_dfDIMouse2); // 標準形式
  assert(SUCCEEDED(hr));

  // 排他制御レベルのセット
  hr = mouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
  assert(SUCCEEDED(hr));
}

void Input::UpdateKeyboard()
{
  HRESULT hr = keyboard->Acquire();	// キーボード動作開始
  // 前回のキー入力を保存
  memcpy(preKey, curKey, sizeof(curKey));
  // キーの入力
  hr = keyboard->GetDeviceState(sizeof(curKey), curKey);
}

void Input::UpdateMouse()
{
  HRESULT hr = mouse->Acquire();	// マウス動作開始

  // 前回の入力を保存
  preMouse = curMouse;

  // マウスの入力
  hr = mouse->GetDeviceState(sizeof(curMouse), &curMouse);
}
