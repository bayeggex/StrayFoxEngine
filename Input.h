#pragma once

#include <Windows.h>
#include <iostream>
#include <array>
#include <string>

class Input
{
public:
	Input();
	Input(const Input&) = delete;
	Input& operator =(const Input&) = delete;
	~Input();
	void KeyCought();

	bool ProcessMessages();
	bool IsKeyPressed(unsigned char keycode) const;

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	std::array<bool, 256> m_keyStates;
};