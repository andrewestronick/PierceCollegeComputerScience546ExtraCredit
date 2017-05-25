#include <iostream>
#include <windows.h>


using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

int main()
{

#pragma region _REGION_A_ - get HWND of console

	char t[500];
	GetConsoleTitleA(t, 500);
	HWND hwndConsole = FindWindowA(NULL, t);
	MoveWindow(hwndConsole, 20, 20, 500, 500, true);

#pragma endregion

#pragma region _REGION_B - get HINSTANCE and create a window!

	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwndConsole, GWL_HINSTANCE);

	WNDCLASS wc = { 0 };
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("Andrew");
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wc))
	{
		cout << "Problem with your WNDCLASS, foo." << endl;
		return 1;
	}

	HWND hwndWindow = CreateWindow(TEXT("Andrew"), TEXT("the window"), WS_OVERLAPPEDWINDOW, 520, 20, 300, 300, NULL, NULL, hInstance, NULL);

	ShowWindow(hwndWindow, SW_SHOWNORMAL);
	UpdateWindow(hwndWindow);
#pragma endregion

#pragma region _REGION_C - message loop
	MSG msg;
	while (GetMessage(&msg, hwndWindow, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
#pragma endregion

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_CREATE:
		cout << "WINDOW SPEAKING TO YOU THROUGH THE CONSOLE." << endl;
		cout << "I'm alive!" << endl << endl;
		Beep(40, 40);
		return 0;
		break;

	case WM_PAINT:
	{
		cout << "PAINT EVENT!  time to repaint!!" << endl;
		PAINTSTRUCT ps;
		HDC hdc;
		BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		Beep(40, 40);
		return 0;
	}
	break;

	case WM_DESTROY:    // killing the window
		cout << "NOOO!!  I . . . shall . . . return !!" << endl;
		PostQuitMessage(0);
		return 0;
		break;
	}

	return DefWindowProc(hwnd, message, wparam, lparam);
}
