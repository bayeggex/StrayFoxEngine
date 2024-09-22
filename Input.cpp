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
	MSG msg;

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
    while (true) {
        for (int keyCode = 0; keyCode < 256; ++keyCode) {
            if (GetAsyncKeyState(keyCode) & 0x8000) {
                std::string keyName;

                switch (keyCode) {
                case VK_SPACE:
                    keyName = "SPACE";
                    break;
                case VK_SHIFT:
                    keyName = "SHIFT";
                    break;
                case VK_CONTROL:
                    keyName = "CTRL";
                    break;
                case VK_MENU:
                    keyName = "ALT";
                    break;
                case VK_ESCAPE:
                    keyName = "ESCAPE";
                    break;
                default:
                    if (keyCode >= 'A' && keyCode <= 'Z') {
                        keyName = std::string(1, static_cast<char>(keyCode));
                    }
                    else if (keyCode >= '0' && keyCode <= '9') {
                        keyName = std::string(1, static_cast<char>(keyCode));
                    }
                    else {
                        keyName = "Key Code: " + std::to_string(keyCode);
                    }
                    break;
                }

                std::cout << "Caught: " << keyName
                    << " (Key Code: " << keyCode << ")"
                    << std::endl;
                if (keyCode == VK_ESCAPE) {
                    return;
                }
            }
        }

        Sleep(100);
    }
}