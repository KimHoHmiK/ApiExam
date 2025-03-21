#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("callback");

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
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
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
	PAINTSTRUCT ps;
	static TCHAR str[128];

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		lstrcpy(str, TEXT("���� ��ư�� �������ϴ�"));
		InvalidateRect(hWnd, NULL, TRUE);
		SetTimer(hWnd, 1, 3000, NULL);
		return 0;
	case WM_TIMER:
		KillTimer(hWnd, 1);
		lstrcpy(str, TEXT(""));
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_CREATE:
		SetTimer(hWnd, 1, 100, NULL);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
