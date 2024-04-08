// Project1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "Project1.h"
#include <windows.h>
#include <commdlg.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    MenuDlg(HWND, UINT, WPARAM, LPARAM);    // (1단계) 다이얼로그 프로시져

HWND g_hWnd, g_hMenuWnd = NULL;                                    // (2단계) 전역변수 선언


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT1));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//

// 메인 윈도우에 대한 부분, 일반 윈도우도 이와 성질이 같기 때문에 이 구조를 일반 윈도우도 그대로 사용하면 됨
// 단 일반 윈도우에서는 lpszMenuName을 사용하지 않을 것이고, lpszClassName을 다르게 설정해 줄 것이다.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 윈도우 생성 부분의 핸들 retrun에 전역 변수를 이용
   HWND hWnd;
   // 3단계: 이 코드에서는 윈도우 크기를 고정시켰기 때문에 최대화 버튼이 필요 없어서 비활성화 시켜준다.
   g_hWnd = hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // 쓰고자 하는 클라이언트 위치 지정
    RECT rtWnd{ 0, 0, 800,400 }, rtDlg;
    // 윈도우와 다이얼로그의 크기를 저장할 변수 => static으로 선언해서 값을 유지
    static SIZE szWndSize, szDlgSize;
    OPENFILENAME  ofn;
    // static으로 선언이 안되어있으면 열기 다이얼로그가 열리지 않는다. 
    static char strFileTitle[MAX_PATH], strFileExtension[10], strFile[100];
    switch (message)
    {
    case WM_CREATE:
        // 윈도우 생성 시 모델리스 다이얼로그 생성
        // txt의 2단계 - 1) 까지 확인
        g_hMenuWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MenuDlg);
        ShowWindow(g_hMenuWnd, SW_SHOW);

        // 크기에 맞는 윈도우 생성
        AdjustWindowRect(&rtWnd, WS_OVERLAPPEDWINDOW, TRUE);
        // 윈도우의 left top과 right bottom을 알려주고 사이즈도 구할 수 있게 해줌
        GetWindowRect(g_hMenuWnd, &rtDlg);
        // 가로길이, 세로길이
        szWndSize.cx = rtWnd.right - rtWnd.left;
        szWndSize.cy = rtWnd.bottom - rtWnd.top;
        // 스크린 좌표라서 다이얼로그는 +1을 해야 길이가 됨
        szDlgSize.cx = rtDlg.right - rtDlg.left + 1;
        szDlgSize.cy = rtDlg.bottom - rtDlg.top + 1;
        // 윈도우와 그 옆에 붙은 다이얼로그 생성 가능
        MoveWindow(hWnd, 10, 10, szWndSize.cx, szWndSize.cy,TRUE);
        MoveWindow(g_hMenuWnd, 10 + szWndSize.cx, 10, szDlgSize.cx, szDlgSize.cy, TRUE);
        break;
    
    // 사이즈가 변경되면 원래대로 돌려줌
    case WM_SIZE:
        GetWindowRect(hWnd, &rtWnd);
        MoveWindow(hWnd, rtWnd.left, rtWnd.top, szWndSize.cx, szWndSize.cy, TRUE);
        break;

    // 윈도우를 움직이면 다이얼로그도 움직일 수 있게
    case WM_MOVE:
        GetWindowRect(hWnd, &rtWnd);
        MoveWindow(hWnd, rtWnd.left, rtWnd.top, szWndSize.cx, szWndSize.cy, TRUE);
        MoveWindow(g_hMenuWnd, rtWnd.right, rtWnd.top, szDlgSize.cx, szDlgSize.cy, TRUE);
        break;
 

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            // 실행과 동시에 다이얼로그 창을 띄우고 싶었는데 아래 조건으로 인해 도움말 버튼을 눌러줘야함.
            // 그래서 위의 WM_CREATE 메세지 처리기 추가
            
            // 파일 열기
            case ID_32771:
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = hWnd;
                // 프로젝트 속성에서 멀티바이트로 바꾸지 않으면 에러생김
                ofn.lpstrTitle = "파일을 선택해주세요.";
                ofn.lpstrFileTitle = strFileTitle;
                ofn.lpstrFile = strFile;
                ofn.lpstrFilter = "임시 파일(*.txt)\0*.txt\0모든 파일(*.*)\0*.*\0";
                ofn.nMaxFile = MAX_PATH;
                ofn.nMaxFileTitle = MAX_PATH;

                if (GetOpenFileName(&ofn) != 0) {
                    switch (ofn.nFilterIndex) {
                    case 1:
                        MessageBox(0, strFile, "임시 파일", MB_OK | MB_ICONINFORMATION);
                        break;
                    case 2:
                        MessageBox(0, strFile, "모든 파일", MB_OK | MB_ICONINFORMATION);
                        break;
                    }
                }
                break;

            // 파일 저장
            case ID_32772:
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = hWnd;
                // 프로젝트 속성에서 멀티바이트로 바꾸지 않으면 에러생김
                ofn.lpstrTitle = "저장할 파일을 선택해주세요.";
                ofn.lpstrFileTitle = strFileTitle;
                ofn.lpstrFile = strFile;
                ofn.lpstrFilter = "임시 파일(*.txt)\0*.txt\0모든 파일(*.*)\0*.*\0";
                ofn.nMaxFile = MAX_PATH;
                ofn.nMaxFileTitle = MAX_PATH;

                // 저장과는 이 함수만 다름
                if (GetSaveFileName(&ofn) != 0) {
                    switch (ofn.nFilterIndex) {
                    case 1:
                        MessageBox(0, strFile, "임시 파일", MB_OK | MB_ICONINFORMATION);
                        break;
                    case 2:
                        MessageBox(0, strFile, "모든 파일", MB_OK | MB_ICONINFORMATION);
                        break;
                    }
                }
                break;

            case IDM_ABOUT:
                // 전역변수 사용, MenuDlg로 변경
                g_hMenuWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MenuDlg);
                ShowWindow(g_hMenuWnd, SW_SHOW);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
       /* if (g_hMenuWnd != NULL && IsWindow(g_hMenuWnd)) {
            DestroyWindow(g_hMenuWnd);
        }*/
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


// 다이얼로그 프로시져 코드 (About을 복사해서 사용)
INT_PTR CALLBACK MenuDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        /*switch (LOWORD(wParam))
        {
            return (INT_PTR)TRUE;
        }*/
        break;
    }
    return (INT_PTR)FALSE;
}
