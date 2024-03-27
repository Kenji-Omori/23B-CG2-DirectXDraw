#pragma once
#include <Core/PatternTemplate/Singleton.h>
#include <Utility/Type/Vector2Int.h>
#include <wrl.h>

#define DIRECTINPUT_VERSION     0x0800          // DirectInputのバージョン指定
#include <dinput.h>

enum class KeyCode
{
	Escape				= 0x01,
	Alpha1				= 0x02,
	Alpha2				= 0x03,
	Alpha3				= 0x04,
	Alpha4				= 0x05,
	Alpha5				= 0x06,
	Alpha6				= 0x07,
	Alpha7				= 0x08,
	Alpha8				= 0x09,
	Alpha9				= 0x0A,
	Alpha0				= 0x0B,
	Minus					= 0x0C,    /* - on main keyboard */
	Equals				= 0x0D,
	BackSpace			= 0x0E,    /* backspace */
	Tab						= 0x0F,
	Q							= 0x10,
	W							= 0x11,
	E							= 0x12,
	R							= 0x13,
	T							= 0x14,
	Y							= 0x15,
	U							= 0x16,
	I							= 0x17,
	O							= 0x18,
	P							= 0x19,
	Lbracket			= 0x1A,
	Rbracket			= 0x1B,
	Return				= 0x1C,    /* Enter on main keyboard */
	Lcontrol			= 0x1D,
	A							= 0x1E,
	S							= 0x1F,
	D							= 0x20,
	F							= 0x21,
	G							= 0x22,
	H							= 0x23,
	J							= 0x24,
	K							= 0x25,
	L							= 0x26,
	Semicolon			= 0x27,
	Apostrophe		= 0x28,
	Grave					= 0x29,    /* accent grave */
	Lshift				= 0x2A,
	Backslash			= 0x2B,
	Z							= 0x2C,
	X							= 0x2D,
	C							= 0x2E,
	V							= 0x2F,
	B							= 0x30,
	N							= 0x31,
	M							= 0x32,
	Comma					= 0x33,
	Period				= 0x34,    /* . on main keyboard */
	Slash					= 0x35,    /* / on main keyboard */
	Rshift				= 0x36,
	NumpadStar		= 0x37,    /* * on numeric keypad */
	LAlt					= 0x38,    /* left Alt */
	Space					= 0x39,
	CapsLock			= 0x3A,
	F1						= 0x3B,
	F2						= 0x3C,
	F3						= 0x3D,
	F4						= 0x3E,
	F5						= 0x3F,
	F6						= 0x40,
	F7						= 0x41,
	F8						= 0x42,
	F9						= 0x43,
	F10						= 0x44,
	Numlock				= 0x45,
	Scroll				= 0x46,    /* Scroll Lock */
	Numpad7				= 0x47,
	Numpad8				= 0x48,
	Numpad9				= 0x49,
	NumpadMinus		= 0x4A,    /* - on numeric keypad */
	Numpad4				= 0x4B,
	Numpad5				= 0x4C,
	Numpad6				= 0x4D,
	NumpadPlus		= 0x4E,    /* + on numeric keypad */
	Numpad1				= 0x4F,
	Numpad2				= 0x50,
	Numpad3				= 0x51,
	Numpad0				= 0x52,
	NumpadPeriod	= 0x53,    /* . on numeric keypad */
	Oem_102				= 0x56,    /* <> or \| on RT 102-key keyboard (Non-U.S.) */
	F11						= 0x57,
	F12						= 0x58,
	F13						= 0x64,    /*                     (NEC PC98) */
	F14						= 0x65,    /*                     (NEC PC98) */
	F15						= 0x66,    /*                     (NEC PC98) */
	Kana					= 0x70,    /* (Japanese keyboard)            */
	Abnt_C1				= 0x73,    /* /? on Brazilian keyboard */
	Convert				= 0x79,    /* (Japanese keyboard)            */
	Noconvert			= 0x7B,    /* (Japanese keyboard)            */
	Yen						= 0x7D,    /* (Japanese keyboard)            */
	Abnt_C2				= 0x7E,    /* Numpad . on Brazilian keyboard */
	Numpadequals	= 0x8D,    /* = on numeric keypad (NEC PC98) */
	Prevtrack			= 0x90,    /* Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) */
	At						= 0x91,    /*                     (NEC PC98) */
	Colon					= 0x92,    /*                     (NEC PC98) */
	Underline			= 0x93,    /*                     (NEC PC98) */
	Kanji					= 0x94,    /* (Japanese keyboard)            */
	Stop					= 0x95,    /*                     (NEC PC98) */
	Ax						= 0x96,    /*                     (Japan AX) */
	Unlabeled			= 0x97,    /*                        (J3100) */
	Nexttrack			= 0x99,    /* Next Track */
	Numpadenter		= 0x9C,    /* Enter on numeric keypad */
	Rcontrol			= 0x9D,
	Mute					= 0xA0,    /* Mute */
	Calculator		= 0xA1,    /* Calculator */
	Playpause			= 0xA2,    /* Play / Pause */
	Mediastop			= 0xA4,    /* Media Stop */
	Volumedown		= 0xAE,    /* Volume - */
	Volumeup			= 0xB0,    /* Volume + */
	Webhome				= 0xB2,    /* Web home */
	Numpadcomma		= 0xB3,    /* , on numeric keypad (NEC PC98) */
	NumpadSlash		= 0xB5,    /* / on numeric keypad */
	Sysrq					= 0xB7,
	RAlt					= 0xB8,    /* right Alt */
	Pause					= 0xC5,    /* Pause */
	Home					= 0xC7,    /* Home on arrow keypad */
	UpArrow				= 0xC8,    /* UpArrow on arrow keypad */
	PageUp				= 0xC9,    /* PgUp on arrow keypad */
	LeftArrow			= 0xCB,    /* LeftArrow on arrow keypad */
	RightArrow		= 0xCD,    /* RightArrow on arrow keypad */
	End						= 0xCF,    /* End on arrow keypad */
	DownArrow			= 0xD0,    /* DownArrow on arrow keypad */
	PageDown			= 0xD1,    /* PgDn on arrow keypad */
	Insert				= 0xD2,    /* Insert on arrow keypad */
	Delete				= 0xD3,    /* Delete on arrow keypad */
	Lwin					= 0xDB,    /* Left Windows key */
	Rwin					= 0xDC,    /* Right Windows key */
	Apps					= 0xDD,    /* AppMenu key */
	Power					= 0xDE,    /* System Power */
	Sleep					= 0xDF,    /* System Sleep */
	Wake					= 0xE3,    /* System Wake */
	Websearch			= 0xE5,    /* Web Search */
	Webfavorites	= 0xE6,    /* Web Favorites */
	Webrefresh		= 0xE7,    /* Web Refresh */
	Webstop				= 0xE8,    /* Web Stop */
	Webforward		= 0xE9,    /* Web Forward */
	Webback				= 0xEA,    /* Web Back */
	Mycomputer		= 0xEB,    /* My Computer */
	Mail					= 0xEC,    /* Mail */
	Mediaselect		= 0xED    /* Media Select */

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
