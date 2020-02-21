// Vadim_Romanyuk_Lab1.cpp : Defines the entry point for the application.
//

//1.8 Используя функции Windows API разработать программу, отображающую внутри клиентской области своего главного окна две диагональные линии
//из верхнего левого в правый нижний угол и из правого верхнего в левый нижний угол соответственно. Цвет линий выбирается с помощью стандартного
//системного окна выбора цвета, которое можно вызвать либо с помощью меню главного окна, либо с помощью всплывающего меню, активизирующегося при
//нажатии правой кнопки мыши в клиентской области, либо нажатием сочетания клавиш Alt + С, а их толщина задается с помощью окна диалога, появляющегося
//при выборе соответствующего пункта меню либо при нажатии Ctrl + S. Программа должна корректно реагировать на изменение размеров окна.Необходимо также
//предусмотреть, чтобы окно нельзя было уменьшать меньше чем до 100x100 пикселов.

#include "stdafx.h"
#include "Vadim_Romanyuk_Lab1.h"

#define MAX_LOADSTRING 100

// Variables for thickness edge
#define MIN_THICKNESS 1
#define MAX_THICKNESS 12

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
COLORREF crCustColors[16];                      // array of custom colors
DWORD currentColor;
DWORD currentThickness = MIN_THICKNESS;

struct ThicknessInfo    // struct for thickness choose
{
	int thicknessValue;
	int thicknessResult;
};

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK SetThickness(HWND, UINT, WPARAM, LPARAM);
BOOL                ChooseThickness(ThicknessInfo* thickInfoб, HWND* hwnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_VADIM_ROMANYUK_LAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VADIM_ROMANYUK_LAB1));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VADIM_ROMANYUK_LAB1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_VADIM_ROMANYUK_LAB1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case ID_LINEOPTIONS_COLOR:
			{
				CHOOSECOLOR cc;
				ZeroMemory(&cc, sizeof(cc));
				cc.lStructSize = sizeof(cc);
				cc.hwndOwner = hWnd;
				cc.lpCustColors = (LPDWORD)crCustColors;
				cc.Flags = CC_RGBINIT | CC_FULLOPEN;
				cc.rgbResult = currentColor;
				if (ChooseColor(&cc))
				{
					currentColor = cc.rgbResult;
					InvalidateRect(hWnd, NULL, TRUE);
					UpdateWindow(hWnd);
				}
				break;
			}
			
			case ID_LINEOPTIONS_THICKNESS:
				ThicknessInfo thickinfo;
				thickinfo.thicknessValue = currentThickness;
				if (ChooseThickness(&thickinfo, &hWnd)) // if user set new color we should redraw the clientrect
				{
					currentThickness = thickinfo.thicknessResult;
					InvalidateRect(hWnd, NULL, TRUE);
					UpdateWindow(hWnd);
				}
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
			RECT clientRect;
			GetClientRect(hWnd, &clientRect);
            HDC hdc = BeginPaint(hWnd, &ps);
			HPEN pen = CreatePen(PS_SOLID, currentThickness, currentColor);
			HGDIOBJ penForLines = SelectObject(hdc, pen);

			// draw lines

			MoveToEx(hdc, 0, 0, NULL);
			LineTo(hdc, clientRect.right, clientRect.bottom);

			MoveToEx(hdc, clientRect.right, clientRect.top, NULL);
			LineTo(hdc, clientRect.left, clientRect.bottom);
			
			SelectObject(hdc, penForLines);
			DeleteObject(penForLines);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_RBUTTONDOWN:
	{   // load window menu and get third submenu
		HMENU hMenu = GetSubMenu(LoadMenu((HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDC_VADIM_ROMANYUK_LAB1)), 2);
		POINT mousePos;
		if (GetCursorPos(&mousePos))
		{ 
			//displays the context menu in the specified location on the screen and sets the selection of items in the menu
			TrackPopupMenu(hMenu, TPM_TOPALIGN | TPM_LEFTALIGN, mousePos.x, mousePos.y, 0, hWnd, NULL);
		}
		break;
	}
	case WM_GETMINMAXINFO:
	{// set min window size (can use WM_SIZE, but in this case additional variables must be initialize(length and width))
		((MINMAXINFO*)lParam)->ptMinTrackSize = { WNDMINSIZE, WNDMINSIZE };
		break;
	}
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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

BOOL  ChooseThickness(ThicknessInfo* thickInfo, HWND* hwnd)
{                         //Converts an integer value to a resource type compatible with the resource-management functions.
	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_THICKBOX), *hwnd, SetThickness, (LPARAM)thickInfo);
	return thickInfo->thicknessResult != thickInfo->thicknessValue;
}


// message handler for thickness box
INT_PTR CALLBACK SetThickness(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND SliderControl = GetDlgItem(hDlg, IDC_SLIDER1); // get handle for sliderbar
	static ThicknessInfo* info = NULL;
	static int thickValue = MIN_THICKNESS;
	switch (message)
	{
	case WM_INITDIALOG:
	{
		info = (ThicknessInfo*)lParam;
		thickValue = info->thicknessResult = info->thicknessValue;

		SendMessage(SliderControl, TBM_SETRANGEMIN, FALSE, MIN_THICKNESS); // set range for thickness
		SendMessage(SliderControl, TBM_SETRANGEMAX, FALSE, MAX_THICKNESS);
		SendMessage(SliderControl, TBM_SETTICFREQ, FALSE, 1);
		SendMessage(SliderControl, TBM_SETPOS, TRUE, thickValue); // set start position for sliderbar
		SetDlgItemInt(hDlg, IDC_EDIT1, thickValue, FALSE); // set value in editbox
		return (INT_PTR)TRUE;
	}
	case WM_HSCROLL: // scrolling logic
		if (SliderControl == (HWND)lParam)
		{
			thickValue = SendMessage(SliderControl, TBM_GETPOS, 0, 0); // get sliderbar position 
			SetDlgItemInt(hDlg, IDC_EDIT1, thickValue, FALSE); // change sliderbar position => change value in editbox
			return (INT_PTR)TRUE;
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			info->thicknessResult = thickValue;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}