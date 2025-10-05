#include <windows.h>
#include <string>
#include "GameObject.h"

int g_counter = 1;
int g_screenWidth = GetSystemMetrics(SM_CXSCREEN);
int g_screenHeight = GetSystemMetrics(SM_CYSCREEN);
int g_floorId = -1;
int g_rectId = -1;

RectangleObject g_floor;
RectangleObject g_rect;

void fillBackground(HWND hwnd, HDC hdc)
{
    RECT rect;
    GetClientRect(hwnd, &rect);

    HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);
}

void drawFloorRectangle(HDC hdc) {
    if (g_floorId == -1)
    {
        int floorPos[] = {100, 100};
        int floorSize[] = {50, 50};
        COLORREF color = RGB(0, 255, 0);
        g_floorId = createRectangle(floorPos, floorSize, color, false);
        RectangleObject floor = getRectangleObjectById(g_floorId);
        drawRectangle(hdc, floor);
    }
    else
    {
        RectangleObject floor = getRectangleObjectById(g_floorId);
        drawRectangle(hdc, floor);
    }
}

void drawRect(HDC hdc) {
    if (g_rectId == -1)
    {
        int rectPos[] = {500, 500};
        int rectSize[] = {50, 50};
        COLORREF color = RGB(0, 255, 255);
        g_rectId = createRectangle(rectPos, rectSize, color, false);
        RectangleObject rect = getRectangleObjectById(g_rectId);
        drawRectangle(hdc, rect);
    }
    else
    {
        RectangleObject rect = getRectangleObjectById(g_rectId);
        drawRectangle(hdc, rect);
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        fillBackground(hwnd, hdc);

        // TODO: clean up code so we don't have this duplicate code
        drawFloorRectangle(hdc);
        drawRect(hdc);

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_TIMER:
        g_counter++;
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    case WM_DESTROY:
        freeRectObjectsMem();
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE InstanceId, HINSTANCE, LPSTR, int nCmdShow)
{

    const char CLASS_NAME[] = "MyWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = InstanceId;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "2D Render App",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, g_screenWidth, g_screenHeight,
        NULL,
        NULL,
        InstanceId,
        NULL);

    if (hwnd == NULL)
        return 0;

    ShowWindow(hwnd, nCmdShow);
    SetTimer(hwnd, 1, 50, NULL);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
