#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int main() {
    srand((unsigned int)time(NULL));

    // Register window class
    const char CLASS_NAME[] = "SalineWinStarter";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // Create window
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "SalineWin Starter",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
        NULL, NULL, GetModuleHandle(NULL), NULL
    );

    if (!hwnd) return 0;

    ShowWindow(hwnd, SW_SHOW);

    // Main loop
    MSG msg = {};
    while (true) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) return 0;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Randomly draw glitchy pixels
        HDC hdc = GetDC(hwnd);
        int x = rand() % 640;
        int y = rand() % 480;
        COLORREF color = RGB(rand()%256, rand()%256, rand()%256);
        SetPixel(hdc, x, y, color);
        ReleaseDC(hwnd, hdc);

        // Random beep
        if (rand() % 50 == 0) Beep(1000 + rand()%2000, 50);

        Sleep(1); // small delay to not overload CPU
    }

    return 0;
}