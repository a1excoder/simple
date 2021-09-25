#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

static const LPCTSTR str = "Hello, World!";
static const int y = 720, x = 1280;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow)
{
    HWND hMainWnd;
    const CHAR *szClassName = "MainClass";
    MSG msg;
    WNDCLASSEX ws;

    ws.cbSize = sizeof(ws);
    ws.style = CS_HREDRAW | CS_VREDRAW; //  | CS_DROPSHADOW | CS_NOCLOSE
    ws.lpfnWndProc = WndProc;
    // not necessarily
    {
        ws.cbClsExtra = 0;
        ws.cbWndExtra = 0;
    }
    ws.hInstance = hInstance;
    ws.hIcon = LoadIcon(NULL, IDI_ERROR);
    ws.hCursor = LoadCursor(NULL, IDC_ARROW);
    ws.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    ws.lpszMenuName = NULL;
    ws.lpszClassName = szClassName;
    ws.hIconSm = LoadIcon(NULL, IDI_INFORMATION);

    if (!RegisterClassEx(&ws)) {
        MessageBox(NULL, "Class was not created.", "oops", MB_ICONWARNING);
        return 1;
    }

    hMainWnd = CreateWindow(
            szClassName, "First winapi application", WS_OVERLAPPEDWINDOW, // WS_EX_APPWINDOW
            CW_USEDEFAULT, 0, x, y,
            NULL, NULL, hInstance, NULL);

    if (!hMainWnd) {
        MessageBox(NULL, "Window was not created.", "oops 2", MB_ICONWARNING);
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
    RECT *rect;
    char buff[16];
    int sz;

    switch (message) {
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE)
                SendMessage(hWnd, WM_CLOSE, wParam, lParam);
            break;

        case WM_LBUTTONDOWN:
            SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, LTGRAY_BRUSH); // WHITE_PEN
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case WM_RBUTTONDOWN:
            hDC = GetDC(hWnd);

            srand(time(NULL));
            COLORREF color = RGB(rand() % 255, rand() % 255,rand() % 255);
            HPEN pen = CreatePen(PS_SOLID, 2, color);

            SetTextColor(hDC, color);
            SetBkMode(hDC, TRANSPARENT);
            sz = wsprintf(buff, "(%d, %d)", LOWORD(lParam), HIWORD(lParam));
            TextOut(hDC, LOWORD(lParam), HIWORD(lParam), buff, sz);

            SelectObject(hDC, pen);
            //SetPixel(hDC, LOWORD(lParam), HIWORD(lParam), RGB(255,0,255));

            
            SelectObject(hDC, pen);
            MoveToEx(hDC, 100, 100, NULL);
            LineTo(hDC, LOWORD(lParam), HIWORD(lParam));

            ReleaseDC(hWnd, hDC);
            break;

        case WM_MOUSEMOVE:
            printf("[MOUSE] (x(%d), y(%d))\n", LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_PAINT:
            hDC = BeginPaint(hWnd, &ps);

            SetTextColor(hDC, 0x000000FF);
            SetBkMode(hDC, TRANSPARENT);

            GetClientRect(hWnd, (LPRECT)&rect);

            DrawText(hDC, str, strlen(str), (LPRECT)&rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

            {
                HPEN pen = CreatePen(PS_SOLID, 3, RGB(0,0,0));
                SelectObject(hDC, pen);
                POINT pt[5] = {{200, 200}, {200, 100}, {200, 200}, {100, 200}, {100, 100}};
                MoveToEx(hDC, pt[0].x, pt[0].y, NULL);
                PolylineTo(hDC, pt + 1, 4);
                Arc(hDC, 200, 200, 100, 100, 300, 300, 300, 300);
                LineTo(hDC, 200, 100);
            }

            EndPaint(hWnd, &ps);
            break;

        case WM_CLOSE:
            CloseWindow(hWnd);
            if (MessageBox(hWnd, "Close app?", "PRESS F", MB_YESNO) == IDYES)
                DestroyWindow(hWnd);
            else
                PostMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, FALSE);

            SetWindowTextA(hWnd, "FUCK YOU!");
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
