//BoxerGameDemo.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "BoxerGameDemo.h"
#include "game.h"
#include "mmsystem.h"       //(多媒体设备接口)
#pragma comment(lib,"winmm.lib")

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HWND hWnd;                                      //窗口句柄

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,                              //主函数变了  不再是main()  这是windows窗口程序的主函数wWinMain()
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // TODO: 在此放置代码。
	

	//PlaySound(L"music.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);
    //mp3
	//mciSendString(L"open music.mp3 alias BGM", 0, 0, 0);
	//mciSendString(L"play BGM", 0, 0, 0);
	// 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BOXERGAMEDEMO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BOXERGAMEDEMO));
	mciSendString(L"open music.mp3 alias BGM", 0, 0, 0);
	mciSendString(L"play BGM repeat", 0, 0, 0);   //repeat循环播放
	if (!Game_Init(hWnd))
		return -1;
	


	MSG msg = {0};

    // 主消息循环: 
    while (msg.message!=WM_QUIT)//(GetMessage(&msg, nullptr, 0, 0))
    {
        if (PeekMessage(&msg,0,0,0,PM_REMOVE))//(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else
		{
			g_tNow = GetTickCount();
			if(g_tNow-g_tPre>=60)
			Game_Paint(hWnd);
		}
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));  //窗口左上角像标
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;      // MAKEINTRESOURCEW(IDC_BOXERGAMEDEMO);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));   //屏幕下方状态栏像标

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 800, 500, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			if (g_heroX >= 0)
				g_heroX -= 10;
			break;
		case VK_RIGHT:
			if (g_heroX <= 800 - 60)
				g_heroX += 10;
			break;
		case 0x56:     //V
			flag = 1;
			while (1)
			{
				g_skillnow = GetTickCount();
				if (g_skillnow - g_skillpre >= 20)
				{
					Game_Paint(hWnd);
					nskill1++;
					if (nskill1 == 34)
						break;
				}
			}
			nskill1 = 0;
			flag = 0;
			break;

		default:
			break;
		}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 分析菜单选择: 
		switch (wmId)
		{
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
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

		return 0;
	}
}

// “关于”框的消息处理程序。
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


BOOL Game_Init(HWND hWnd)
{
	//绘图环境
	g_hdc = GetDC(hWnd);
	g_memdc = CreateCompatibleDC(g_hdc);
	g_bufdc = CreateCompatibleDC(g_hdc);
	bmp = CreateCompatibleBitmap(g_hdc, 800, 500);

	//数据
	g_background = (HBITMAP)LoadImage(NULL, L"background.bmp", IMAGE_BITMAP, 7200, 500, LR_LOADFROMFILE);
	g_staybmp= (HBITMAP)LoadImage(NULL, L"stay.bmp", IMAGE_BITMAP, 900, 141, LR_LOADFROMFILE);
	g_skill1 = (HBITMAP)LoadImage(NULL, L"skill1.bmp", IMAGE_BITMAP, 11200, 240, LR_LOADFROMFILE);
	
	//bmp-->g_memdc
	SelectObject(g_memdc, bmp);


	return true;
}

VOID  Game_Paint(HWND hWnd)
{
	//背景图片
	//g_background-->g_bufdc
	SelectObject(g_bufdc, g_background);
	//g_bufdc-->g_memdc
	BitBlt(g_memdc, 0, 0, 800, 500, g_bufdc, nback*800, 0, SRCCOPY);     //把图片从一个设备转移到另一个设备
	if (flag == 0)
	{
		//人物站立图片
		SelectObject(g_bufdc, g_staybmp);
		//BitBlt(g_memdc, 100, 340, 100, 141, g_bufdc, nstay * 100, 0, SRCCOPY);
		TransparentBlt(g_memdc, g_heroX, g_heroY, 60, 90, g_bufdc, nstay * 100, 0, 100, 141, RGB(255, 255, 0));
		if (++nstay >= 9)
			nstay = 0;
		BitBlt(g_hdc, 0, 0, 800, 500, g_memdc, 0, 0, SRCCOPY);
		if (++nback >= 9)
			nback = 0;
		g_tPre = GetTickCount();
	}
	else if (flag == 1)
	{
		//人物站立图片
		SelectObject(g_bufdc, g_skill1);
		//BitBlt(g_memdc, 100, 340, 100, 141, g_bufdc, nstay * 100, 0, SRCCOPY);
		TransparentBlt(g_memdc, g_heroX-30, g_heroY-145, 320, 240, g_bufdc, nskill1 * 320, 0, 320, 240, RGB(255, 255, 0));
		if (++nstay >= 9)
			nstay = 0;
		BitBlt(g_hdc, 0, 0, 800, 500, g_memdc, 0, 0, SRCCOPY);
		if (++nback >= 9)
			nback = 0;
		g_skillpre = GetTickCount();
		g_tPre = GetTickCount();
	}


}