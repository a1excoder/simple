#include <windows.h>
#include <stdio.h>

static const LPCTSTR str = "Hello, World!";
static const int y = 720, x = 1280;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void test_timer(HWND hwnd) {
    static int i = 0;
    printf("i is %d\n", i);
    i++;
    KillTimer(hwnd, 0);
}

int WINAPI WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow)
{
    HWND hMainWnd;
    const CHAR *szClassName = "MySlass";
    MSG msg;
    WNDCLASSEX ws;

    ws.cbSize = sizeof(ws);
    //ws.style = NULL;
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

    static int w, h;

    switch (message) {
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE)
                SendMessage(hWnd, WM_CLOSE, wParam, lParam);
            break;

        case WM_LBUTTONDOWN:
            SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, LTGRAY_BRUSH);
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case WM_RBUTTONDOWN:
            SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, WHITE_PEN);
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case WM_MOUSEMOVE:
            printf("(%d, %d)\n", LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_PAINT:
            hDC = BeginPaint(hWnd, &ps);

            SetTextColor(hDC, 0x000000FF); // white = 0x00FFFFFF
            SetBkMode(hDC, TRANSPARENT);

            // получение x y
            GetClientRect(hWnd, (LPRECT)&rect);

            // использование x y,
            // wcslen(str) == -1 in this example
            DrawText(hDC, str, strlen(str), (LPRECT)&rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

            // void (*func)(HWND);
            // func = test_timer;

            // timer works
            //SetTimer(hWnd, 0, 3000, (TIMERPROC) test_timer);

            // output in console x, y positions
            //printf("(%ld, %ld)\n", rect.right, rect.bottom);
            EndPaint(hWnd, &ps);
            break;

        case WM_CLOSE:
            CloseWindow(hWnd);
            if (MessageBox(hWnd, "Close app?", "PRESS F", MB_YESNO) == IDYES)
                DestroyWindow(hWnd);
            else
                SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, FALSE);
                // ShowWindow(hWnd, SW_MAXIMIZE);

            SetWindowTextA(hWnd, "FUCK YOU!");
            break;
        case WM_DESTROY:
            //MessageBox(NULL, "Hi)", "", MB_OK);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
