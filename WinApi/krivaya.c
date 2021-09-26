#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const LPCTSTR str = "Hello, World!";

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // контекст устройства
    HDC hDC;

    PAINTSTRUCT ps;
    RECT *rect;
    char buff[16];
    char buff2[20];

    switch (message) {
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE)
                SendMessage(hWnd, WM_CLOSE, wParam, lParam);
            else if (wParam == VK_RETURN) {
                hDC = GetDC(hWnd);

                srand(time(NULL));
                COLORREF color = RGB(rand() % 255, rand() % 255,rand() % 255);
                MoveToEx(hDC, 100, 100, NULL);

                HPEN pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0)); // color
                SelectObject(hDC, pen);

//                {
//                    POINT p[] = {{100, 100}, {125, 75}, {150, 125}, {170, 100}, {225, 4}, {300, 150}, {250, 200}};
//                    PolyBezier(hDC, p, 7); // PolyBezierTo(hDC, p + 1, 6);
//                }

                {                            // x, y from first   // x, y from last
                    POINT p2[] = {{200, 200}, {241, 366},               {609, 137}, {500, 500}};
                    PolyBezier(hDC, p2, 3 + 1);
                }

                DeleteObject(pen);
                ReleaseDC(hWnd, hDC);
            }
            break;

        case WM_LBUTTONDOWN:
            SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, LTGRAY_BRUSH); // WHITE_PEN
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case WM_RBUTTONDOWN:
            hDC = GetDC(hWnd);

            {
                srand(time(NULL));
                COLORREF color = RGB(rand() % 255, rand() % 255,rand() % 255);
                HPEN pen = CreatePen(PS_SOLID, 2, color);

                SelectObject(hDC, pen);
                MoveToEx(hDC, 100, 100, NULL);
                LineTo(hDC, LOWORD(lParam), HIWORD(lParam));

                SetTextColor(hDC, color);
                SetBkMode(hDC, TRANSPARENT);
                DWORD sz = wsprintf(buff, "XY(%d, %d)", LOWORD(lParam), HIWORD(lParam));
                DWORD sz2 = wsprintf(buff2, "RGB(%d, %d, %d)", GetRValue(color), GetGValue(color), GetBValue(color));
                TextOut(hDC, LOWORD(lParam), HIWORD(lParam), buff, sz);
                TextOut(hDC, LOWORD(lParam), HIWORD(lParam) + 20, buff2, sz2);
            }

            // SetPixel(hDC, LOWORD(lParam), HIWORD(lParam), RGB(255,0,255));

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
            /*
            {
                HPEN pen = CreatePen(PS_SOLID, 3, RGB(0,0,0));
                SelectObject(hDC, pen);
                POINT pt[5] = {{200, 200}, {200, 100}, {200, 200}, {100, 200}, {100, 100}};
                MoveToEx(hDC, pt[0].x, pt[0].y, NULL);
                PolylineTo(hDC, pt + 1, 4);
                Arc(hDC, pt[0].x, pt[0].y, 100, 100, 300, 300, 300, 300);
                LineTo(hDC, 200, 100);
            }
            */

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
