// keyboardHook.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "keyboardHook.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	char text[] = "Error loading DLL!";
	char title[] = "Key Tracer";
	BOOL error = FALSE;
	HINSTANCE dllhinst;
	typedef VOID(CALLBACK* LPFNDLLFUNC1)(VOID);
	LPFNDLLFUNC1 lpfnDllFunc1;

	dllhinst = LoadLibrary("keyHook.dll");
	if (dllhinst != NULL)
	{
		lpfnDllFunc1 = (LPFNDLLFUNC1)GetProcAddress(dllhinst, "SetKbHook");
		if (!lpfnDllFunc1)
		{
			FreeLibrary(dllhinst);
			error = TRUE;
		}
		else
		{
			lpfnDllFunc1();
		}
	}
	else error = TRUE;

	if (error)
		MessageBox(GetDesktopWindow(), text, title, MB_OK);

	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	};

	return msg.wParam;
}
