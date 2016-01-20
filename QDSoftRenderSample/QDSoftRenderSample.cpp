// QDSoftRenderSample.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "QDSoftRenderSample.h"
#include "QDSoftRender\Device.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
int wndClientRectWidth = 1024;					// the main window client rect width
int wndClientRectHeight = 768;					// the main window client rect height
HWND hWnd = NULL;								// current window handle
HDC hWndDC = NULL;
HDC hWndCompatibleDC = NULL;					// current window compatible device content
HBITMAP hDIB = NULL;							// DIB
HBITMAP hOldBITMAP = NULL;						// old BITMAP
unsigned char *ptrFrameBuffer = NULL;			// frame buffer
long frameBufferPitch = 0;
QDSoftRender::DeviceSP g_spDevice = nullptr;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL				InitFrameBuffer();
VOID				CloseWnd();
VOID				InitDevice();

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_QDSOFTRENDERSAMPLE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	InitDevice();
	// Main message loop:
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			static ULONGLONG lastDrawTick = 0;
			ULONGLONG curTick = GetTickCount64();
			double deltaTime = static_cast<double>(curTick - lastDrawTick) * 0.001;
			if (deltaTime < 1.0 / 60.0 )
			{
				Sleep(0);
				continue;
			}

			if (nullptr != g_spDevice)
			{
				g_spDevice->Clear(QDSoftRender::CLEAR_ALL);
				g_spDevice->Draw();
				g_spDevice->Present(ptrFrameBuffer);
				BitBlt(hWndDC, 0, 0, wndClientRectWidth, wndClientRectHeight, hWndCompatibleDC, 0, 0, SRCCOPY);
			}
			lastDrawTick = curTick;
		}
	}

	CloseWnd();
	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QDSOFTRENDERSAMPLE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName	= nullptr;// MAKEINTRESOURCE(IDC_QDSOFTRENDERSAMPLE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   if (!InitFrameBuffer())
	   return FALSE;

   RECT realRect = { 0, 0, wndClientRectWidth, wndClientRectHeight };
   AdjustWindowRect(&realRect, WS_OVERLAPPEDWINDOW, FALSE);   

   int width = realRect.right - realRect.left;
   int height = realRect.bottom - realRect.top;
   
   MoveWindow(hWnd, GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2, 
	   GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2, width, height, FALSE);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

BOOL InitFrameBuffer()
{
	if (!hWnd)
		return FALSE;

	hWndDC = GetDC(hWnd);
	hWndCompatibleDC = CreateCompatibleDC(hWndDC);
	//ReleaseDC(hWnd, hDC);

	BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), wndClientRectWidth, -wndClientRectHeight, 1, 32, BI_RGB,
		wndClientRectWidth * wndClientRectHeight * 4, 0, 0, 0, 0 } };
	LPVOID ptr;
	hDIB = CreateDIBSection(hWndCompatibleDC, &bi, DIB_RGB_COLORS, &ptr, 0, 0);
	if (!hDIB)
		return FALSE;
	hOldBITMAP = (HBITMAP)SelectObject(hWndCompatibleDC, hDIB);
	ptrFrameBuffer = (unsigned char *)ptr;
	frameBufferPitch = wndClientRectWidth * 4;
	return TRUE;
}

VOID CloseWnd()
{
	if (hWndCompatibleDC)
	{
		if (hOldBITMAP)
		{
			SelectObject(hWndCompatibleDC, hOldBITMAP);
			hOldBITMAP = NULL;
		}
		DeleteDC(hWndCompatibleDC);
		hWndCompatibleDC = NULL;
	}

	if (hDIB)
	{
		DeleteObject(hDIB);
		hDIB = NULL;
	}

	if (hWndDC)
	{
		ReleaseDC(hWnd, hWndDC);
		hWndDC = NULL;
	}

	if (hWnd)
	{
		CloseWindow(hWnd);
		hWnd = NULL;
	}
}

VOID InitDevice()
{
	g_spDevice = QDSoftRender::Device::CreateDevice(wndClientRectWidth, wndClientRectHeight,
		QDSoftRender::COLOR_R8G8B8A8, 0xFFFF0000);
}

