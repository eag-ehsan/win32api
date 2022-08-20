#include <windows.h>

LRESULT CALLBACK myWinPrc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hIns, HINSTANCE pIns, LPSTR lpCmdLine, int nShow)
{
    //MessageBox(NULL,"My Prog is here","Ehsan Ahmadi",MB_OK);
    WNDCLASSW wc = {0};
    wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance      = hIns;
    wc.lpszClassName  = L"EsiClass";
    wc.lpfnWndProc    = myWinPrc;

    if (!RegisterClassW(&wc))
    {
        MessageBox(NULL,
            "Call to RegisterClassW failed!",
            "Win32 Guided Tour",
            NULL);
        return -1;
    }
    CreateWindowW(L"EsiClass",
                  L"Ehsan First API app",
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  CW_USEDEFAULT,CW_USEDEFAULT,600,400,
                  NULL,NULL,NULL,NULL);
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK myWinPrc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hwnd, msg, wParam, lParam);


    }
}
