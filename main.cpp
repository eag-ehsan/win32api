/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@ win32api Ver:1.03 2022-21-8    @@@@@@
@@@@@@ Created by Ehsan Ahmadi Gohari @@@@@@
@@@@@@ Email: eag.ehsan@gmail.com     @@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@                                        @@
@@    Functions:                          @@
@@            Mouse Pointer anywhere      @@
@@            Keyboard state              @@
@@                                        @@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <strsafe.h>
#define IDB_BALL 101
#define MENU_VALUE_START 1
#define MENU_VALUE_END 2
#define MENU_VALUE_EXIT 3
#define MENU_VALUE_MODE 4
#define MENU_VALUE_CHANGE_TITLE 5
#define MENU_VALUE_BUT1 6
#define MENU_VALUE_BUT2 7

LRESULT CALLBACK myWinPrc(HWND, UINT, WPARAM, LPARAM);
BOOL WINAPI FreeConsole(void);
DWORD WINAPI Thread_no_1(LPVOID);
DWORD WINAPI Thread_no_2(LPVOID);
void AddMenus(HWND);
void AddControls(HWND);
void actionButton1();
void actionButton2();
HMENU hMenu;
HWND hStati;
HWND hStati2;
HWND hStati3;
HWND hEdit1;
HWND hButton;
HWND hButton2;
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
        return 1;
    }
    CreateWindowW(L"EsiClass",
                  L"Ehsan First API app",
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  CW_USEDEFAULT,CW_USEDEFAULT,600,400,
                  NULL,NULL,NULL,NULL);


    int Data_Of_Thread_1 = 1;
    int Data_Of_Thread_2 = 2;
    HANDLE Handle_Of_Thread_1 = 0;
    HANDLE Handle_Of_Thread_2 = 0;
    // Create thread 1.
    Handle_Of_Thread_1 = CreateThread( NULL, 0, Thread_no_1, &Data_Of_Thread_1, 0, NULL);
    if ( Handle_Of_Thread_1 == NULL)  ExitProcess(Data_Of_Thread_1);
    // Create thread 2.
    Handle_Of_Thread_2 = CreateThread( NULL, 0, Thread_no_2, &Data_Of_Thread_2, 0, NULL);
    if ( Handle_Of_Thread_2 == NULL)  ExitProcess(Data_Of_Thread_2);

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
    int xMouse = 0;
    int yMouse = 0;

    switch(msg)
    {
    case WM_COMMAND:
        {
            switch(wParam)
            {
            case MENU_VALUE_START:
                MessageBeep(MB_OK);
                break;
            case MENU_VALUE_EXIT:
                //MessageBeep(MB_DEFBUTTON1);
                //DestroyWindow(hwnd);
                PostQuitMessage(0);
                break;
            case MENU_VALUE_CHANGE_TITLE:
                wchar_t strEdit[100];
                GetWindowTextW(hEdit1,strEdit,100);
                SetWindowTextW(hwnd,strEdit);
                break;
            case MENU_VALUE_BUT1:
                actionButton1();
                break;
            case MENU_VALUE_BUT2:
                actionButton2();
                break;

            }
            break;
        }
    case WM_CREATE:
        {
            AddMenus(hwnd);
            AddControls(hwnd);
            break;
        }
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
    case WM_MOUSEMOVE:
        {
            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);
            wchar_t str1[100];
            swprintf_s(str1, L"%d - %d", xMouse,yMouse);
            SetWindowTextW(hStati,str1);
            break;
        }

    default:
        return DefWindowProcW(hwnd, msg, wParam, lParam);


    }
    return 0;
}
void AddMenus(HWND hwnd1)
{
    //create All Menus
    HMENU hFileMenu;
    HMENU hFileMenuMode;
    hMenu = CreateMenu();
    hFileMenu = CreateMenu();
    hFileMenuMode = CreateMenu();
    //Add main menu items  [ File - View ]
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
    AppendMenu(hMenu, MF_STRING, NULL, "View");

    //Add [File] menu items
    AppendMenu(hFileMenu, MF_STRING, MENU_VALUE_START, "Start");
    AppendMenu(hFileMenu, MF_STRING, MENU_VALUE_END, "End");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hFileMenuMode, "Modes");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL,NULL);
    AppendMenu(hFileMenu, MF_STRING, MENU_VALUE_EXIT, "Exit");

    //Add [Modes] menu items
    AppendMenu(hFileMenuMode, MF_STRING, NULL, "Creative");
    AppendMenu(hFileMenuMode, MF_STRING, NULL, "Survival");
    AppendMenu(hFileMenuMode, MF_SEPARATOR, NULL,NULL);
    AppendMenu(hFileMenuMode, MF_STRING, MENU_VALUE_CHANGE_TITLE, "Change Title");
    SetMenu(hwnd1, hMenu);

    return ;

}

void AddControls(HWND hwnd1)
{
    hStati = CreateWindowW(L"static",L"Input text here: ",
                  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT,
                  200,50,200,20,
                  hwnd1,NULL,NULL,NULL);
    hStati2 = CreateWindowW(L"static",L"win mouse",
                  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT,
                  200,25,200,20,
                  hwnd1,NULL,NULL,NULL);
    hStati3 = CreateWindowW(L"static",L"big big",
                  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT,
                  50,165,500,60,
                  hwnd1,NULL,NULL,NULL);
    hEdit1 = CreateWindowW(L"Edit",L"...",
                  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
                  200,72,200,40,
                  hwnd1,NULL,NULL,NULL);
    hButton = CreateWindowW(L"Button",L"Click on 10x10",WS_VISIBLE | WS_CHILD,
                  250,115,100,20,
                  hwnd1,(HMENU)MENU_VALUE_BUT1,NULL,NULL);
    hButton2 = CreateWindowW(L"Button",L"Get Mouse",WS_VISIBLE | WS_CHILD,
                  250,140,100,20,
                  hwnd1,(HMENU)MENU_VALUE_BUT2,NULL,NULL);
}

void actionButton1()
{
    //MessageBeep(MB_SYSTEMMODAL);
    INPUT Inputs[3] = {0};

    Inputs[0].type = INPUT_MOUSE;
    Inputs[0].mi.dx = 10; // desired X coordinate
    Inputs[0].mi.dy = 10; // desired Y coordinate
    Inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;

    Inputs[1].type = INPUT_MOUSE;
    Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    Inputs[2].type = INPUT_MOUSE;
    Inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(3, Inputs, sizeof(INPUT));
}
void actionButton2()
{
    MessageBeep(MB_SYSTEMMODAL);
    POINT p1;

}
DWORD WINAPI Thread_no_1( LPVOID lpParam )
{
    POINT p;
    while (1)
        {
           if (GetCursorPos(&p))
           {
                wchar_t str1[100];
                swprintf_s(str1, L"%d - %d", p.x,p.y);
                SetWindowTextW(hStati2,str1);
           }
           Sleep(10);
        }


	return 0;
}
DWORD WINAPI Thread_no_2( LPVOID lpParam )
{

    while(1)
    {
        if(GetKeyState(VK_SHIFT) & 0x8000)
        {
            SetWindowTextW(hStati3,L"Shift");
        }
        else
        {
            SetWindowTextW(hStati3,L"");
        }
        Sleep(10);
    }
	return 0;
}
