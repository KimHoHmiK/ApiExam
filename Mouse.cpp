#include <Windows.h>

#define LOWORD(i) ((WORD)(i))
#define HIWORD(i) ((WORD)(((DWORD)(i) >> 16)&0xFFFF))
#define LOBYTE(w) ((BYTE)(w))
#define HIBYTE(w) ((BYTE)(((WORD)(w) >> 8) & 0xFFFF))

#define MAKEWORD(a,b) ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define KAMELONG(a,b) ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Mouse");

int APIENTRY WinMain(HINSTANCE hinstance, HINSTANCE hPrevlnstance, LPSTR lpszCmdParam, int nCmdShow) {

	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hinstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hinstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, (WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL),
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hinstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	HDC hdc;
	static int x;
	static int y;
	static BOOL bNowDraw = FALSE;


	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		bNowDraw = TRUE;
		return 0;
	case WM_MOUSEMOVE:
		if (bNowDraw == TRUE) {
			hdc = GetDC(hWnd);
			MoveToEx(hdc, x, y, NULL);
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			LineTo(hdc, x, y);
			ReleaseDC(hWnd, hdc);
		}
		return 0;
	case WM_LBUTTONUP:
		bNowDraw = FALSE;
		return 0;
	case WM_LBUTTONDBLCLK:
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}