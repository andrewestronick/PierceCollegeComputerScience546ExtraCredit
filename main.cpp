#include <iostream>
#include <windows.h>

#define IMAGE_SIZE 256

using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

int main()
{
	HWND hwnd = GetConsoleWindow();
	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);

	WNDCLASS  window;
	window.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	window.hCursor = LoadCursor(hInstance, IDC_ARROW);
	window.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	window.hInstance - hInstance;
	window.lpfnWndProc = WndProc;
	window.lpszClassName = TEXT("picture window");
	window.style = CS_HREDRAW | CS_VREDRAW;

	WNDCLASS wc = { 0 };
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("myWindow");
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wc))
		exit(-1);

	HWND hwndWindow = CreateWindow(TEXT("myWindow"), TEXT("the window"), WS_OVERLAPPEDWINDOW, 10, 10, IMAGE_SIZE, IMAGE_SIZE, NULL, NULL, hInstance, NULL);

	ShowWindow(hwndWindow, SW_SHOWNORMAL);
	UpdateWindow(hwndWindow);
	HDC hdc = GetDC(hwndWindow);

	// Draw some ranndom dots

	for (int i = 0; i < 1000; i++)
	{
		int x = rand() % IMAGE_SIZE;
		int y = rand() % IMAGE_SIZE;
		SetPixel(hdc, x, y, RGB(255, 255, 255));
	}

	MSG msg;
	while (GetMessage(&msg, hwndWindow, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{

	case WM_DESTROY:    // killing the window

		PostQuitMessage(0);
		exit(0);
		break;
	}

	return DefWindowProc(hwnd, message, wparam, lparam);
}
