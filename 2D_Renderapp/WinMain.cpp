#include <windows.h>
#include <string>

int g_counter = 1;
int g_screenWidth  = GetSystemMetrics(SM_CXSCREEN);
int g_screenHeight = GetSystemMetrics(SM_CYSCREEN);

int g_floorcord_left = 0;
int g_floorcord_top = 300;
int g_floorcord_right = 500;
int g_floorcord_bottom = 500;



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Fill background with red recangle
        RECT rect;
        GetClientRect(hwnd, &rect);

        HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
        FillRect(hdc, &rect, brush);
        DeleteObject(brush);

        // Draw the counter text
        SetBkMode(hdc, TRANSPARENT);
        std::wstring text = L"Counter: " + std::to_wstring(g_counter);
        TextOutW(hdc, 50, 50, text.c_str(), text.length());
        
        int g_rect_left = 100;
        int g_rect_top = 100 + g_counter;
        int g_rect_right = 150;
        int g_rect_bottom = 150 + g_counter;
        
        if(g_rect_bottom < g_floorcord_top){
            Rectangle(hdc, g_rect_left, g_rect_top, g_rect_right, g_rect_bottom);
        }else{
            Rectangle(hdc, g_rect_left, g_floorcord_top - 50 ,g_rect_right , g_floorcord_top);
        }
        
        Rectangle(hdc, g_floorcord_left, g_floorcord_top, g_floorcord_right, g_floorcord_bottom);

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_TIMER:
        g_counter++;
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE InstanceId, HINSTANCE, LPSTR, int nCmdShow) {
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
        NULL
    );

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);

    SetTimer(hwnd, 1, 10, NULL);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
