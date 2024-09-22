#include "Input.h"

SHORT GetAsyncKeyState(_In_ int vKey);

Input::Input()
{
	m_keyStates.fill(false);
}

Input::~Input()
{
}

bool Input::ProcessMessages()
{
    MSG msg = { };

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_QUIT)
        {
            return false;
        }

        if (msg.message == WM_KEYDOWN)
        {
            unsigned char keycode = static_cast<unsigned char>(msg.wParam);
            m_keyStates[keycode] = true;
        }

        if (msg.message == WM_KEYUP)
        {
            unsigned char keycode = static_cast<unsigned char>(msg.wParam);
            m_keyStates[keycode] = false;
        }
    }

	return true;
}

bool Input::IsKeyPressed(unsigned char keycode) const
{
	return m_keyStates[keycode];
}

void Input::KeyCought()
{
    for (int keyCode = 0; keyCode < 256; ++keyCode) {
        if (GetAsyncKeyState(keyCode) & 0x8000) {
            char keyName[128] = { 0 };

            UINT scanCode = MapVirtualKey(keyCode, MAPVK_VK_TO_VSC);
            if (keyCode >= VK_LEFT && keyCode <= VK_DOWN) {
                scanCode |= 0x100; // 0x100 veya 256 idc
            }

            wchar_t keyNameW[128] = { 0 };
            if (GetKeyNameTextW(scanCode << 16, keyNameW, sizeof(keyNameW) / sizeof(wchar_t)) > 0) {
                std::wstring keyNameWide(keyNameW);
                std::string keyName(keyNameWide.begin(), keyNameWide.end());
                std::cout << "Caught: " << keyName
                    << " (Key Code: " << keyCode << ")"
                    << std::endl;
            }
            else {
                std::cout << "nill Key: (Key Code: " << keyCode << ")" << std::endl;
            }

            if (keyCode == VK_ESCAPE) {
                return;
            }
        }
    }
}