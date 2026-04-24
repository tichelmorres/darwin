#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <windows.h>

#define UNUSED(value)     (void)(value)
#define UNUSED_FUNC       __attribute__((unused))

#define WIDTH      800
#define HEIGHT     600
#define BACKGROUND 0xFFFFFFFF

typedef uint32_t Pixel32;

#ifdef _WIN32
HBITMAP hbmp;
HANDLE hTickThread;
HWND hwnd;
HDC hdcMem;
#endif

static Pixel32 *pixels;

static void draw_background(Pixel32 *pixels, size_t width, size_t height, Pixel32 background)
{
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            pixels[y*width + x] = background;
        }
    }
}

typedef struct {
    int px, py;
} Point;

static UNUSED_FUNC void render_scene(Pixel32 *pixels, size_t width, size_t height, Pixel32 background)
{
    // implement the rotating point
}

DWORD WINAPI tickThreadProc(HANDLE handle)
{
    UNUSED(handle);
    Sleep(50);
    ShowWindow(hwnd, SW_SHOW);
    ShowCursor(FALSE);

    HDC hdc = GetDC(hwnd);

    hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmp);

    for (;;) {
        POINT p;
        if (GetCursorPos(&p) && ScreenToClient(hwnd, &p)) {
            draw_background(pixels, WIDTH, HEIGHT, BACKGROUND);
            BitBlt(hdc, 0, 0, WIDTH, HEIGHT, hdcMem, 0, 0, SRCCOPY);
        }
    }

    SelectObject(hdcMem, hbmOld);
    DeleteDC(hdc);
}

void MakeSurface(HWND hwnd)
{
    BITMAPINFO bmi;
    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmi.bmiHeader.biWidth = WIDTH;
    bmi.bmiHeader.biHeight = -HEIGHT;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = 0;
    bmi.bmiHeader.biXPelsPerMeter = 0;
    bmi.bmiHeader.biYPelsPerMeter = 0;
    bmi.bmiHeader.biClrUsed = 0;
    bmi.bmiHeader.biClrImportant = 0;
    bmi.bmiColors[0].rgbBlue = 0;
    bmi.bmiColors[0].rgbGreen = 0;
    bmi.bmiColors[0].rgbRed = 0;
    bmi.bmiColors[0].rgbReserved = 0;

    HDC hdc = GetDC(hwnd);

    hbmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void **)&pixels, NULL, 0);
    DeleteDC(hdc);

    hTickThread = CreateThread(NULL, 0, &tickThreadProc, NULL, 0, NULL);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_CREATE: {
        MakeSurface(hwnd);
    }
    break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        BitBlt(hdc, 0, 0, WIDTH, HEIGHT, hdcMem, 0, 0, SRCCOPY);
        EndPaint(hwnd, &ps);
    }
    break;
    case WM_CLOSE: {
        DestroyWindow(hwnd);
    }
    break;
    case WM_DESTROY: {
        TerminateThread(hTickThread, 0);
        PostQuitMessage(0);
    }
    break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    UNUSED(hPrevInstance);
    UNUSED(lpCmdLine);
    UNUSED(nShowCmd);
    WNDCLASSEX wc;
    MSG msg;

    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hbrBackground = CreateSolidBrush(0);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = "animation_class";
    wc.lpszMenuName = NULL;
    wc.style = 0;

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Failed to register window class.", "Error", MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
               WS_EX_APPWINDOW,
               "animation_class",
               "grass",
               WS_MINIMIZEBOX | WS_SYSMENU | WS_POPUP | WS_CAPTION,
               CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
               NULL, NULL, hInstance, NULL);

    while (GetMessage(&msg, 0, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
