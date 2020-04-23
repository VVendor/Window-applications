// WinLab2.cpp : Defines the entry point for the application.
//



#include "stdafx.h"
#include <cmath>
#include "WinLab2.h"

#define MAX_LOADSTRING 100
#define SIMPLE_SHIFT 10
#define DIAG_SHIFT   5*sqrt(2)

// Global Variables:
HINSTANCE hInst;                                // current instance
HWND hWnd = nullptr;

struct CaptionSettings // struct for update caption
{
	char* captionText;
	int len;
} *settings;

// Forward declarations of functions included in this code module:
BOOL                InitInstance(HINSTANCE, int);
BOOL  UpdateCaption(CaptionSettings* textCaption, HWND* hwnd);
INT_PTR CALLBACK SetCaption(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    MainWndProc(HWND, UINT, WPARAM, LPARAM);
void ScaleElements(HWND hDlg);
void UpdateWindowPosition(HWND, int vertShift, int horizShift);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINLAB2));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
			if (!IsDialogMessage(hWnd, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
    }

    return (int) msg.wParam;
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   settings = new CaptionSettings();
   hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, MainWndProc);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


// handle for main dialog window
INT_PTR CALLBACK MainWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
		ScaleElements(hDlg);
		return (INT_PTR)TRUE;
	case WM_SIZE: 
	{
		ScaleElements(hDlg);
	}
		break;
    case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:   // caption button
			{
			if (UpdateCaption(settings, &hDlg))
			{
				SetWindowText(hDlg, (LPCWSTR)settings->captionText);
			}
				return (INT_PTR)TRUE;
			}

		case IDC_BUTTON2:
			{
				UpdateWindowPosition(hDlg, -DIAG_SHIFT, -DIAG_SHIFT);
				break;
			}

		case IDC_BUTTON3:
			{
			UpdateWindowPosition(hDlg, -SIMPLE_SHIFT, 0);
			break;
			}

		case IDC_BUTTON4: 
			{
			UpdateWindowPosition(hDlg, -DIAG_SHIFT, DIAG_SHIFT);
			break;
			}

		case IDC_BUTTON5:
			{
			UpdateWindowPosition(hDlg, 0, -SIMPLE_SHIFT);
			break;
			}

		case IDC_BUTTON6:
			{
			UpdateWindowPosition(hDlg, 0, SIMPLE_SHIFT);
			break;
			}

		case IDC_BUTTON7:
			{
			UpdateWindowPosition(hDlg, DIAG_SHIFT, -DIAG_SHIFT);
			break;
			}

		case IDC_BUTTON8:
			{
			UpdateWindowPosition(hDlg, SIMPLE_SHIFT, 0);
			break;
			}

		case IDC_BUTTON9:
			{
			UpdateWindowPosition(hDlg, DIAG_SHIFT, DIAG_SHIFT);
			break;
			}

		case IDCANCEL:
			{
				DestroyWindow(hDlg);
				return (INT_PTR)TRUE;
			}
			break;
		}
		break;
	case WM_GETMINMAXINFO:
	{
		((MINMAXINFO*)lParam)->ptMinTrackSize = { WNDMINSIZE, WNDMINSIZE };
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		return (INT_PTR)TRUE;
    }
    return (INT_PTR)FALSE;
}

BOOL  UpdateCaption(CaptionSettings* textCaption, HWND* hwnd)
{
	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), *hwnd, SetCaption, NULL);
	return settings->len != 0 && settings->captionText != NULL;
}

//handle for caption window
INT_PTR CALLBACK SetCaption(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND editControlHandle = GetDlgItem(hDlg, IDC_EDIT1);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			settings->len = SendMessage(editControlHandle, WM_GETTEXTLENGTH, 0, 0);
			delete[] settings->captionText;
			settings->captionText = new char[settings->len];
			SendMessage(editControlHandle, WM_GETTEXT, (WPARAM)settings->len + 1, (LPARAM)settings->captionText);
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void UpdateWindowPosition(HWND hDlg, int vertShift, int horizShift)
{
	RECT rect;
	GetWindowRect(hDlg, &rect);
	SetWindowPos(hDlg, NULL, rect.left + horizShift, rect.top + vertShift,
		rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
}

void ScaleElements(HWND hDlg)
{
	RECT rect;
	GetClientRect(hDlg, &rect);
	int elements[3][3] = {{IDC_BUTTON2, IDC_BUTTON3, IDC_BUTTON4},
	{IDC_BUTTON5, IDC_BUTTON1, IDC_BUTTON6},
	{IDC_BUTTON7, IDC_BUTTON8, IDC_BUTTON9} };
	int butWidth = (rect.right - rect.left) / 3 + 1; // plus 1 for better scaling
	int butHeight = (rect.bottom - rect.top) / 3 + 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SetWindowPos(GetDlgItem(hDlg, elements[i][j]), NULL, rect.left + j*butWidth, rect.top + i*butHeight,
				butWidth, butHeight, SWP_SHOWWINDOW);
		}
	}
}
