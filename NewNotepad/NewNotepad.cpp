#include "framework.h"
#include "NewNotepad.h"
#include <CommCtrl.h>

HWND editBox;
std::wstring currentFile = L"";
HBITMAP hBitmap1, hBitmap2, hBitmap3, hBitmap4, hBitmap5, hBitmap6, hBitmap7;
HWND hImage = NULL;
HWND hButton = NULL;
bool visibilityDelayed = false;
bool crash = false;
int currentImage = 1; 

void CreateMenus(HWND hwnd) {
    HMENU hMenu = CreateMenu();
    SetMenu(hwnd, hMenu);
}

void DisplayBrother(HWND hwnd, HBITMAP bitmap) {
    RECT rect;
    GetClientRect(hwnd, &rect);
    int imageSize = 200; 
    int xPos = 0; 
    int yPos = rect.bottom - imageSize-100; 

    HWND hImage = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, xPos, yPos, imageSize, imageSize, hwnd, NULL, NULL, NULL);
    SendMessage(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);
    ShowWindow(hImage, SW_SHOW);
    SetWindowPos(hImage, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

void ChangeImage(HWND hwnd) {
    
    if (currentImage == 1) {
        SendMessage(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);
        SetWindowText(editBox, L"MILK"); 
        currentImage = 2;
    }
    else if (currentImage == 2) {
        SendMessage(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap3);
        currentImage = 3;


        int textLength = GetWindowTextLength(editBox);
        wchar_t* buffer = new wchar_t[textLength + 1];
        GetWindowText(editBox, buffer, textLength + 1);

  
        std::wstring newText = std::wstring(buffer) + L" SPONGE";
        SetWindowText(editBox, newText.c_str());

        delete[] buffer; 
    }
    else if (currentImage == 3) {
        SendMessage(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap4);
        currentImage = 4;
        DisplayBrother(hwnd, hBitmap7);
    }
    else if (currentImage == 4) {
        SendMessage(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap5);
        currentImage = 5;
        MessageBox(hwnd, L"paperclip.exe has preformed 94,708 illegal opperations and will now be shot.", L"Error", MB_OK);
    }
    else if (currentImage == 5) {
        ShowWindow(hButton, SW_HIDE);
        SendMessage(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap6);
        currentImage = 6;
        SetTimer(hwnd, 2, 3000, NULL);
    }
    else if (currentImage == 6) {
        SendMessage(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap1);
    }
}

void ShowDelayedControls(HWND hwnd) {
    RECT rect;
    GetClientRect(hwnd, &rect);
    int imageSize = 200;
    int xPos = rect.right - imageSize;
    int yPos = rect.bottom - imageSize;

    hImage = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, xPos, yPos, imageSize, imageSize, hwnd, NULL, NULL, NULL);
    SendMessage(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap1);
    ShowWindow(hImage, SW_SHOW);
    SetWindowPos(hImage, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

    hButton = CreateWindowEx(0, L"BUTTON", L"OK", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPSIBLINGS | BS_PUSHBUTTON, rect.right - 170, rect.bottom - 127, 93, 25, hwnd, NULL, NULL, NULL);
    SetWindowPos(hButton, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    ShowWindow(hButton, SW_SHOW);
}



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        hBitmap1 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
        hBitmap2 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
        hBitmap3 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP3), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
        hBitmap4 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP4), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
        hBitmap5 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP5), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
        hBitmap6 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP6), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
        hBitmap7 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP7), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

        editBox = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | ES_MULTILINE, 0, 0, 800, 600, hwnd, (HMENU)0, GetModuleHandleW(NULL), NULL);
        SetWindowPos(editBox, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        CreateMenus(hwnd);

        SetTimer(hwnd, 1, 3000, NULL);
        break;

    case WM_COMMAND:
        if ((HWND)lParam == hButton && HIWORD(wParam) == BN_CLICKED) {
            ChangeImage(hwnd);
        }
        break;

    case WM_TIMER:
        if (wParam == 1 && !visibilityDelayed) { 
            visibilityDelayed = true; 
            KillTimer(hwnd, 1); 
            ShowDelayedControls(hwnd);
        }
        if (wParam == 2 && !crash) {
            KillTimer(hwnd, 2);
            crash = true;
            MessageBox(hwnd, L"notepad.exe has performed an illegal opperation (killed a paperclip) and will now be arrested, and for that reason, closed.", L"Error", MB_OK);
            PostQuitMessage(0);

        }
        break;

    case WM_DESTROY:
        DeleteObject(hBitmap1);
        DeleteObject(hBitmap2);
        DeleteObject(hBitmap3);
        DeleteObject(hBitmap4);
        DeleteObject(hBitmap5);
        DeleteObject(hBitmap6);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow) {
    WNDCLASSEX wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.hIconSm = static_cast<HICON>(LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE));

    wcex.lpfnWndProc = WindowProc;
    wcex.hInstance = hInstance;
    wcex.lpszClassName = L"TextEditorClass";

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    HWND hwnd = CreateWindowExW(0, L"TextEditorClass", L"Untitled - Notepad", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

    if (!hwnd) {
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_COMMAND && IsWindowVisible(hButton) && HIWORD(msg.wParam) == BN_CLICKED && LOWORD(msg.wParam) == IDOK) {
            ChangeImage(hwnd);
        }
    }

    return static_cast<int>(msg.wParam);
}