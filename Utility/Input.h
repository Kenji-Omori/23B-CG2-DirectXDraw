#pragma once
#include <Core/PatternTemplate/Singleton.h>
#include <Utility/Type/Vector2Int.h>
#include <wrl.h>

#define DIRECTINPUT_VERSION     0x0800          // DirectInputのバージョン指定
#include <dinput.h>

enum class KeyCode
{
	aa,
};

enum class MouseButton
{
	Left		= 0,
	Right		= 1,
	Middle	= 2
};


namespace Core
{
	class Window;
}



class Input : public Core::Singleton<Input>
{
public:
	void Initialize(Core::Window* window);
	void Update();
	bool IsKey(KeyCode key);
	bool IsKeyDown(KeyCode key);
	bool IsKeyRelease(KeyCode key);
	BYTE KeycodeToByte(KeyCode key);
	bool IsClick(MouseButton button);
	bool IsClickDown(MouseButton button);
	bool IsClickUp(MouseButton button);
	Input():Singleton() {}
	~Input() {}
private:
	void SetupDevice(Core::Window* window);
	void SetupKeyboard(Core::Window* window);
	void SetupMouse(Core::Window* window);
	void UpdateKeyboard();
	void UpdateMouse();


	Microsoft::WRL::ComPtr<IDirectInput8> dInput;
	Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard;
	BYTE curKey[256] = {};
	BYTE preKey[256] = {};
	Microsoft::WRL::ComPtr<IDirectInputDevice8> mouse;
	DIMOUSESTATE2 curMouse = {};
	DIMOUSESTATE2 preMouse = {};

	Vector2Int mousePosition = {};

};

Input* Core::Singleton<Input>::isntance_ = nullptr;
