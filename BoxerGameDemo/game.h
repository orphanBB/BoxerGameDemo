#pragma once
#include "windows.h"
#pragma comment(lib,"Msimg32.lib")
HDC			 g_hdc, g_memdc,g_bufdc;       //���ڻ�ͼ���  �ڴ���豸������
HBITMAP		 bmp, g_background,g_staybmp,g_skill1;    //��λͼ�ͱ���ͼƬ
DWORD        g_tPre, g_tNow;
DWORD        g_skillpre, g_skillnow;
int nback = 0, nstay = 0, nskill1=0;
int g_heroX = 100, g_heroY = 350;
int flag=0;

BOOL Game_Init(HWND hWnd);
VOID Game_Paint(HWND hWnd);