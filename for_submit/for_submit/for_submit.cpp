﻿// for_submit.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "for_submit.h"

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
    LoadStringW(hInstance, IDC_FORSUBMIT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FORSUBMIT));

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

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FORSUBMIT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FORSUBMIT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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
#include<vector>
#include<ctime>
#include<string>
#define BTNS 17        // 색상 버튼 갯수
#define S_BTN_x 650     // 색상 버튼 시작 x위치
#define S_BTN_y 30      // 색상 버튼 시작 y위치
#define BTN_gap 3       // 버튼 간격
#define BTN_size 30     // 버튼 크기

#define REPLAY 1500     // REPLAY 버튼 번호
#define CLEAR 1501      // CLEAR 버튼 번호
#define COMM_BTN_x 30       //command button
#define COMM_BTN_y 33       //
#define COMM_BTN_width 100  //
#define COMM_BTN_hight 30   //
#define COMM_BTN_gap 10     //

#define PLUS 2000       // PLUS 버튼 번호
#define MINUS 2001      // MINUS 버튼 번호
#define SIZE_BTN_x 290  //command button
#define SIZE_BTN_y 33   // 
#define SIZE_BTN_size 30    //
#define SIZE_BTN_gap 30     //
#define SIZE_BTN_top_width -10
#define SIZE_BTN_width 150  //
#define SIZE_BTN_hight 35   //

#define ERASER 2500     // REPLAY 버튼 번호
#define ERASER_BTN_x 580       //command button
#define ERASER_BTN_y 30       //
#define ERASER_BTN_width 80   //
#define ERASER_BTN_hight 30   //
#define ERASER_BTN_gap 10     //

#define BOUNDARY 100    // 마우스 인식 지점 

// ----------함수 선언부-----------
DWORD WINAPI drawing(LPVOID points);    // 리플레이 스레드
bool is_area(LPARAM lParam);            // 색칠 가능 영역인지 반환해주는 함수

// -----구조체, 클래스 선언부------
typedef struct btn      //색상 버튼내용을 저장할 구조체
{
    RECT rect;
    COLORREF col;
    HBRUSH brsh;
    HPEN pen;
    //HWND Wnd;
}BTN;

typedef struct point_info
{
    LPARAM lparm;   //좌표  
    int cWidth;     //굵기
    COLORREF color;     //색상
    DWORD ctime;   //시간
    UINT state;     //상태{WM_LBUTTONDOWN, }
}PINFO;

// 색상을 저장하는 배열      // ↓배열의 0번에 해당하는 부분이 프로그램에서 표시되지 않음
COLORREF cols[] = { RGB(255,0 ,255), //표시되지 않는 색(검정색 앞부분을 클릭하면 색이 변경되는거로 보아 프로그램상으로 구현은 되어있습니다)
                    RGB(0,0,0),         //검정
                    RGB(255,255,255),   //흰색
                    RGB(192,192,192),   //회색
                    RGB(255,0,0),       //빨간색
                    RGB(255,155,0),     //주황색
                    RGB(255,255,0),     //노란색
                    RGB(155,255,0),     //연두색
                    RGB(0,255,0),       //초록색
                    RGB(0,255,255),     //하늘색
                    RGB(0,0,255),       //파란색
                    RGB(155,0,255),     //자주색
                    RGB(255,0,255),     //보라색
                    RGB(255,0,155),     //연분홍
                    RGB(255,0,105),     //분홍색
                    RGB(150,75,0),      //갈색
                    RGB(128,0,0),       //적갈색
};

// --------전역 변수 선언부---------
HWND g_hWnd;
HWND g_button_replay = nullptr; // 버튼에 대한 포인터를 저장
HWND g_button_clear = nullptr;
HWND g_button_plus = nullptr;
HWND g_button_minus = nullptr;
HWND g_button_eraser = nullptr;

std::vector <PINFO> g_Pinfo;    // 선 정보 저장 벡터
bool is_replay = false;         // 현재 리플레이 상태인지 확인

// 펜 크기를 보여주는 사각형 영역의 설정
// left, top, right, bottom
RECT pen_rect = { SIZE_BTN_x + SIZE_BTN_gap * 3 + SIZE_BTN_size, \
                SIZE_BTN_y + SIZE_BTN_top_width, \
                SIZE_BTN_width + SIZE_BTN_x + SIZE_BTN_gap * 3 + SIZE_BTN_size ,\
                SIZE_BTN_y + SIZE_BTN_hight };

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static std::vector<BTN> btns(BTNS); // BTNS 개의 버튼 정보저장
    static int pre_x, pre_y;    // 이전 x,y 좌표 저장
    static int col = 1;         // 현재 색상 정보 저장
    static int p_width = 10;    // 굵기
    static bool left = false;   // 왼쪽 버튼 클릭 확인
    static DWORD drow_time;     // 최근 그려진 시간이 언제인가
    static HANDLE thread = nullptr; // 쓰레드 저장

    HDC hdc;
    PINFO temp_pinfo;
    POINT po;
    DWORD g_time;
    LPMINMAXINFO MaxMin_Info; //윈도우 크기 구조체
    int x, y;


    switch (message)
    {

    case WM_CREATE:
        g_hWnd = hWnd;
        x = S_BTN_x;    // 색상 버튼 생성
        y = S_BTN_y;
        for (int i = 0; i < btns.size(); i++)
        {
            btns[i].rect.left = x;
            btns[i].rect.top = y;
            btns[i].rect.right = x + BTN_size;
            btns[i].rect.bottom = y + BTN_size;

            x += BTN_size + BTN_gap;

            btns[i].brsh = CreateSolidBrush(cols[i]);
        }

        // CLEAR REPLAY 버튼 생성
        g_button_replay = CreateWindow(L"button", L"REPLAY", WS_CHILD | WS_VISIBLE, \
            COMM_BTN_x, COMM_BTN_y, COMM_BTN_width, COMM_BTN_hight, \
            hWnd, (HMENU)REPLAY, hInst, NULL);
        g_button_clear = CreateWindow(L"button", L"CLEAR", WS_CHILD | WS_VISIBLE, \
            COMM_BTN_x + COMM_BTN_width + COMM_BTN_gap + 20, COMM_BTN_y, COMM_BTN_width, COMM_BTN_hight, \
            hWnd, (HMENU)CLEAR, hInst, NULL);

        // + - 버튼 생성
        g_button_minus = CreateWindow(L"button", L"━", WS_CHILD | WS_VISIBLE, \
            SIZE_BTN_x, SIZE_BTN_y, SIZE_BTN_size, SIZE_BTN_size, \
            hWnd, (HMENU)MINUS, hInst, NULL);
        g_button_plus = CreateWindow(L"button", L"╋", WS_CHILD | WS_VISIBLE, \
            SIZE_BTN_x + SIZE_BTN_size + SIZE_BTN_gap, SIZE_BTN_y, SIZE_BTN_size, SIZE_BTN_size, \
            hWnd, (HMENU)PLUS, hInst, NULL);

        // 지우개 버튼 생성
        g_button_eraser = CreateWindow(L"button", L"지우개", WS_CHILD | WS_VISIBLE, \
            ERASER_BTN_x, ERASER_BTN_y, ERASER_BTN_width, ERASER_BTN_hight, \
            hWnd, (HMENU)ERASER, hInst, NULL);
        break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case REPLAY:    // 리플레이 버튼 클릭시
            if (!is_replay)
                thread = CreateThread(NULL, 0, drawing, nullptr, 0, NULL);
            else
            {
                TerminateThread(thread, 0);
                thread = CreateThread(NULL, 0, drawing, nullptr, 0, NULL);
            }
            break;
        case CLEAR:     // 클리어 버튼 클릭시
            TerminateThread(thread, 0);
            is_replay = false;
            g_Pinfo.clear();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case PLUS:      // + 버튼 클릭시
            if (p_width < 10)
                p_width += 1;
            else if (p_width < 30)
                p_width += 2;
            else if (p_width < 48)
                p_width += 3;
            else
                p_width = 50;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case MINUS:     // - 버튼 클릭시
            if (p_width > 10)
                p_width -= 2;
            else if (p_width > 1)
                p_width -= 1;
            else
                p_width = 1;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case ERASER:    //지우개 버튼 클릭시
            col = 2;
            break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_KEYDOWN: // 키입력
        switch (wParam)
        {
        case VK_UP:         // 펜 크기 증가
        case VK_OEM_PLUS:   // 화살표 위, 키보드 +
            if (p_width < 10)
                p_width += 1;
            else if (p_width < 30)
                p_width += 2;
            else if (p_width < 48)
                p_width += 3;
            else
                p_width = 50;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case VK_DOWN:       //펜 크기 감소
        case VK_OEM_MINUS:  // 화살표 아래, 키보드 -
            if (p_width > 10)
                p_width -= 2;
            else if (p_width > 1)
                p_width -= 1;
            else
                p_width = 1;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        default:
            break;
        }
        break;

    case WM_LBUTTONDOWN:

        x = LOWORD(lParam);
        y = HIWORD(lParam);

        po.x = x;
        po.y = y;


        // 색 변경 버튼을 눌렀는지 확인
        for (int i = 0; i < btns.size(); i++)
        {
            if (PtInRect(&btns[i].rect, po))
            {
                //MessageBox(hWnd, L"색이 선택됐습니다.", L"상단 글자", MB_OK);
                col = i;
                InvalidateRect(hWnd, NULL, true);
                return 0;
            }
        }

        if (!is_area(lParam))   // 바운더리 영역 밖이면 종료
            return 0;

        left = true;

        // 현재 정보 벡터에 저장
        temp_pinfo.lparm = lParam;
        temp_pinfo.state = WM_LBUTTONDOWN;
        temp_pinfo.color = cols[col];
        temp_pinfo.cWidth = p_width;
        temp_pinfo.ctime = GetTickCount64();
        g_Pinfo.push_back(temp_pinfo);

        hdc = GetDC(hWnd);  //윈도우 핸들을 얻음
        MoveToEx(hdc, x, y, NULL);
        LineTo(hdc, x + 1, y + 1);
        ReleaseDC(hWnd, hdc);

        pre_x = x;
        pre_y = y;

        break;

    case WM_MOUSEMOVE:
        if (!is_area(lParam))   // 바운더리 영역 밖이면 종료
        {
            left = false;
            break;
        }
        if (left) //&& g_time > 10
        {
            HPEN npen, open;

            drow_time = GetTickCount64();

            // 현재 정보 벡터에 저장
            temp_pinfo.lparm = lParam;
            temp_pinfo.state = WM_MOUSEMOVE;
            temp_pinfo.color = cols[col];
            temp_pinfo.cWidth = p_width;
            temp_pinfo.ctime = GetTickCount64();
            g_Pinfo.push_back(temp_pinfo);

            x = LOWORD(lParam);
            y = HIWORD(lParam);

            hdc = GetDC(hWnd);
            npen = CreatePen(PS_SOLID, p_width, cols[col]);

            open = (HPEN)SelectObject(hdc, npen);
            MoveToEx(hdc, pre_x, pre_y, NULL);
            LineTo(hdc, x, y);
            DeleteObject(npen);

            ReleaseDC(hWnd, hdc);

            pre_x = x;
            pre_y = y;
        }
        break;

    case WM_LBUTTONUP:
        if (is_area(lParam))    // 바운더리 영역 안이면 실행
        {
            if (left)
            {
                // 현재 정보 벡터에 저장
                temp_pinfo.lparm = lParam;
                temp_pinfo.state = WM_LBUTTONUP;
                temp_pinfo.color = cols[col];
                temp_pinfo.cWidth = p_width;
                temp_pinfo.ctime = GetTickCount64();
                g_Pinfo.push_back(temp_pinfo);
            }
        }
        left = false;
        break;

    case WM_GETMINMAXINFO:      //창 크기 고정(16:9 = 1280 X 720)
        MaxMin_Info = (LPMINMAXINFO)lParam;
        MaxMin_Info->ptMinTrackSize.x = 1280;
        MaxMin_Info->ptMinTrackSize.y = 720;
        MaxMin_Info->ptMaxTrackSize.x = 1280;
        MaxMin_Info->ptMaxTrackSize.y = 720;

        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        HBRUSH nbrush, obrush;
        HPEN open, npen;
        RECT temp_rect = { 0,0,0,0 };
        WCHAR wc_pen_size[2];   // 펜 크기를 문자열로 저장할 배열

        // 펜 정보 출력
        y = pen_rect.top + (pen_rect.bottom - pen_rect.top) / 2; // 펜에 대해 출력할 y를 정함
        // 펜크기를 문자열로 변환
        wc_pen_size[0] = p_width / 10 + '0';    // 10의 자리
        wc_pen_size[1] = p_width % 10 + '0';    // 0의 자리
        TextOut(hdc, 330, y - 7, wc_pen_size, 2);   // 펜 크기 숫자로 출력

        Rectangle(hdc, pen_rect.left, pen_rect.top, pen_rect.right, pen_rect.bottom);   // 펜 사각형 출력
        npen = CreatePen(PS_SOLID, p_width, cols[col]);     // 현재 펜 색상으로 변경
        open = (HPEN)SelectObject(hdc, npen);
        DeleteObject(open);

        MoveToEx(hdc, pen_rect.left + 20, y, NULL);     // 펜 형태 출력
        LineTo(hdc, pen_rect.right - 20, y);

        npen = CreatePen(PS_SOLID, 1, RGB(195, 195, 195));
        open = (HPEN)SelectObject(hdc, npen);
        DeleteObject(open);

        // BOUNDARY 라인 그리기
        GetClientRect(hWnd, &temp_rect);
        MoveToEx(hdc, 0, BOUNDARY, NULL);
        LineTo(hdc, temp_rect.right, BOUNDARY);

        // 색상 버튼 그리기
        for (int i = 1; i < btns.size(); i++)
        {
            Rectangle(hdc, btns[i].rect.left - 1, btns[i].rect.top - 1, btns[i].rect.right + 1, btns[i].rect.bottom + 1);
            SelectObject(hdc, btns[i].brsh);
            Rectangle(hdc, btns[i].rect.left, btns[i].rect.top, btns[i].rect.right, btns[i].rect.bottom);
        }

        if (!is_replay)     // 현재 리플레이 되고 있는 상황이 아니라면
        {
            // 사용자가 입력한 그림을 다시 그림
            for (int i = 0; i < g_Pinfo.size(); i++)
            {
                switch (g_Pinfo[i].state)
                {
                case WM_LBUTTONDOWN:
                    //MessageBox(hWnd, L"실행", L"L버튼", MB_OK);
                    DeleteObject(npen);
                    npen = CreatePen(PS_SOLID, g_Pinfo[i].cWidth, g_Pinfo[i].color);
                    SelectObject(hdc, npen);

                    x = LOWORD(g_Pinfo[i].lparm);
                    y = HIWORD(g_Pinfo[i].lparm);

                    MoveToEx(hdc, x, y, NULL);
                    LineTo(hdc, x + 1, y + 1);  //점찍기
                    break;

                case WM_MOUSEMOVE:
                case WM_LBUTTONUP:

                    LineTo(hdc, LOWORD(g_Pinfo[i].lparm), HIWORD(g_Pinfo[i].lparm));
                    break;

                default:
                    break;
                }
            }
        }

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        DestroyWindow(g_button_replay);
        DestroyWindow(g_button_clear);
        DestroyWindow(g_button_minus);
        DestroyWindow(g_button_plus);

        // 색상 버튼 소멸
        for (int i = 0; i < BTNS; i++)
        {
            DeleteObject(btns[i].brsh);
        }

        // 벡터 소멸
        btns.clear();
        g_Pinfo.clear();

        // 스레드는 hWnd 소속이므로 hWnd가 소멸될 때 자동 소멸
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

// 리플레이 스레드
DWORD WINAPI drawing(LPVOID points)
{
    HDC hdc;
    HPEN npen;
    int x, y;
    hdc = GetDC(g_hWnd);
    is_replay = true;

    npen = CreatePen(PS_SOLID, 10, RGB(255, 255, 255));

    while (true)
    {
        InvalidateRect(g_hWnd, NULL, TRUE);
        for (int i = 0; i < g_Pinfo.size() - 1; i++)
        {
            switch (g_Pinfo[i].state)
            {
            case WM_LBUTTONDOWN:
                //MessageBox(hWnd, L"실행", L"L버튼", MB_OK);
                DeleteObject(npen);
                npen = CreatePen(PS_SOLID, g_Pinfo[i].cWidth, g_Pinfo[i].color);
                SelectObject(hdc, npen);

                x = LOWORD(g_Pinfo[i].lparm);
                y = HIWORD(g_Pinfo[i].lparm);

                MoveToEx(hdc, x, y, NULL);
                LineTo(hdc, x + 1, y + 1);  //점찍기
                break;

            case WM_MOUSEMOVE:
                LineTo(hdc, LOWORD(g_Pinfo[i].lparm), HIWORD(g_Pinfo[i].lparm));
                if (g_Pinfo[i + 1].state == WM_MOUSEMOVE)  // 다음벡터도 WM_MOUSEMOVE일 경우에만 sleep 
                    Sleep(g_Pinfo[i + 1].ctime - g_Pinfo[i].ctime);
                break;
            case WM_LBUTTONUP:
                LineTo(hdc, LOWORD(g_Pinfo[i].lparm), HIWORD(g_Pinfo[i].lparm));
                break;

            default:
                break;
            }

        }
        Sleep(3000);
    }
    ReleaseDC(g_hWnd, hdc);
    is_replay = false;
    return 0;
}

// 색칠 가능 영역인지 반환해주는 함수
bool is_area(LPARAM lParam)
{
    if (HIWORD(lParam) > BOUNDARY)   // y좌표가 색칠 가능 영역이라면 
        return true;
    return false;
}