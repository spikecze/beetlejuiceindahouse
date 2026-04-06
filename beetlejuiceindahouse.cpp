#include <windows.h>
#include <mmsystem.h> // PlaySound and Beep
#include <cstdlib>    // rand()

#pragma comment(lib, "Winmm.lib") // Required for PlaySound

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    const char CLASS_NAME[] = "BeetlejuiceWindow";

    // Register window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    RegisterClass(&wc);

    int screenX = GetSystemMetrics(SM_CXSCREEN);
    int screenY = GetSystemMetrics(SM_CYSCREEN);

    // Full-screen transparent window
    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT, // Layered + transparent + topmost
        CLASS_NAME,
        "Beetlejuice",
        WS_POPUP,           // Borderless
        0, 0, screenX, screenY,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hwnd) return 0;

    // Fully visible (change 255 to lower for semi-transparent)
    SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // Play your song asynchronously
    PlaySound(TEXT("Erika-I-Don_t-Know-_Lyrics_.wav"), NULL, SND_FILENAME | SND_ASYNC);

    // Glitchy beeps
    for (int i = 0; i < 50; i++) {
        Beep(300 + rand() % 1000, 50 + rand() % 200);
        Sleep(50);
    }

    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
