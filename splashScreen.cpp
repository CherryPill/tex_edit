#include <Windows.h>
#include <gdiplus.h>
#include <stdio.h>
#include <cassert>
#include "globalVars.h"
#include "splashScreen.h"
#include "appconst.h"
void registerSplashClass(void)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)splashWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = ghInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = SplashWndClass;
	wcex.hIconSm = NULL;

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, TEXT("Window class registration failed"), TEXT("Error"), MB_ICONERROR);
	}
}
void createSplashScreen(void)
{
	 splashScreen = CreateWindowEx(WS_EX_TOOLWINDOW,
		SplashWndClass,
		NULL,
		WS_OVERLAPPED | SS_BITMAP,
		wpInitPosX,
		wpInitPosY,
		splashScreenWidth,
		splashScreenHeight,
		NULL,
		NULL,
		ghInstance,
		NULL);
	 if (!splashScreen)
	 {
		 MessageBox(NULL, TEXT("Window creation failed"), TEXT("Error"), MB_ICONERROR);
	 }
	 lpSplashWndProc = (WNDPROC)SetWindowLongPtr(splashScreen, GWL_WNDPROC, (LONG_PTR)&splashWindowProc);
}

LRESULT CALLBACK splashWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_NCCALCSIZE:  //CAPTURE THIS MESSAGE AND RETURN NULL
		return NULL;
	case WM_CREATE:
		SetTimer(hWnd, ID_TIMER_INIT, 1000, NULL);
		SetTimer(hWnd, ID_TIMER_LOAD, 2000, NULL);
		SetTimer(hWnd, ID_TIMER_DONE, 4000, NULL);
		SetTimer(hWnd, ID_TIMER_CLOSE, 5000, NULL);
		break;
	case WM_PAINT:
	{
					 PAINTSTRUCT ps = { 0 };
					 RECT rect = { 0 };
					 HDC hDC = BeginPaint(hWnd, &ps);
					 GetClientRect(hWnd, &rect);
					 InflateRect(&rect, -2, -2);
					 Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
					 InflateRect(&rect, -15, -15);
					 HFONT hFont = CreateFont(-35, -35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Arial"));
					 HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
					 DrawText(hDC, SZ_SPLASH, lstrlen(SZ_SPLASH), &rect, DT_WORDBREAK);
					 SelectObject(hDC, hOldFont);
					 EndPaint(hWnd, &ps);
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_TIMER:
	{
					 HDC hDC = GetDC(hWnd);
					 RECT rect = { 0 };
					 GetClientRect(hWnd, &rect);
					 KillTimer(hWnd, wParam);
					 switch (wParam)
					 {
					 case ID_TIMER_CLOSE:
						 DestroyWindow(hWnd);
						 break;
					 case ID_TIMER_INIT:
						 TextOut(hDC, rect.right - 200, rect.bottom - 20, SZ_INIT, lstrlen(SZ_INIT));
						 break;
					 case ID_TIMER_LOAD:
						 TextOut(hDC, rect.right - 200, rect.bottom - 20, SZ_LOAD, lstrlen(SZ_LOAD));
						 break;
					 case ID_TIMER_DONE:
						 TextOut(hDC, rect.right - 200, rect.bottom - 20, SZ_CLOSE, lstrlen(SZ_CLOSE));
						 break;
					 }
					 ReleaseDC(hWnd, hDC);
	}
		break;
	default:
	{
			   break;
	}
	}
	return (DefWindowProcW(hWnd, message, wParam, lParam));
}
void showSplashScreen(void)
{
	registerSplashClass();
	createSplashScreen();
}