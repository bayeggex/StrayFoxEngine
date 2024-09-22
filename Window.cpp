#include "Window.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window()
	:m_hInstance(GetModuleHandle(nullptr))
{
	const wchar_t* CLASS_NAME = L"STRAYFOX";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO); //Icon
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //Cursor
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	int width = 640;
	int height = 480;

	//640x480
	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	AdjustWindowRect(&rect, style, false);

	//settings
	m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"StrayFox",
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		m_hInstance,
		NULL
	);

	ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window()
{
	const wchar_t* CLASSNAME = L"StrayFox";

	UnregisterClass(CLASSNAME, m_hInstance);

}

bool Window::ProcessMessages()
{
	MSG msg = {};
	while (PeekMessage(&msg,nullptr, 0u,8u, PM_REMOVE)){}
	{
		if (msg.message == WM_QUIT) { return false; }

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}