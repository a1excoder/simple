#include <windows.h>

static LPCTSTR str = L"Привет мир!";

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hMainWnd;
	wchar_t szClassName[] = L"MySlass";
	MSG msg;
	WNDCLASSEX ws;

	ws.cbSize = sizeof(ws);
	//ws.style = NULL;
	ws.style = CS_HREDRAW | CS_VREDRAW;
	ws.lpfnWndProc = WndProc;
	ws.cbClsExtra = 0;
	ws.cbWndExtra = 0;
	ws.hInstance = hInstance;
	ws.hIcon = LoadIcon(NULL, IDI_ERROR);
	ws.hCursor = LoadCursor(NULL, IDC_ARROW);
	ws.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	ws.lpszMenuName = NULL;
	ws.lpszClassName = szClassName;
	ws.hIconSm = LoadIcon(NULL, IDI_INFORMATION);

	if (!RegisterClassEx(&ws)) {
		MessageBox(NULL, L"Class was not created.", L"oops", MB_ICONWARNING);
		return 1;
	}

	hMainWnd = CreateWindow(
		szClassName, L"Первое winapi приложение", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 480, 340,
		NULL, NULL, hInstance, NULL);

	if (!hMainWnd) {
		MessageBox(NULL, L"Window was not created.", L"oops 2", MB_ICONWARNING);
		return 2;
	}

	ShowWindow(hMainWnd, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// контекст устройства
	HDC hDC;

	PAINTSTRUCT ps;
	RECT rect;

	switch (message) {
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		SetTextColor(hDC, WHITENESS);
		SetBkMode(hDC, TRANSPARENT);

		// получение x y
		GetClientRect(hWnd, &rect);
		// использование x y, 
		// wcslen(str) == -1 in this example
		DrawText(hDC, str, wcslen(str), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		MessageBox(hWnd, L"Лады пока(", L"PRESS F", MB_OK);

		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		//MessageBox(NULL, L"Лады пока(", L"PRESS F", MB_OK);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
