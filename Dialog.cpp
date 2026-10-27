#include<windows.h>
#include "resource.h"

#define ID_FILE_DIALOG 1003
//#define ID_DIALOG1

LRESULT DlgProc(HWND hDlg, UINT msgId, WPARAM wParam, LPARAM lParam)
{
	switch (msgId)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case IDOK:
			EndDialog(hDlg, IDOK);
			break;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			break;
		}
		break;
	}

	return 0L;
}

LRESULT WndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
{
	switch (msgId)
	{
	case WM_CREATE:
	{
		HMENU hMenuSmp = CreatePopupMenu();
		HMENU hMenuBar = CreateMenu();

		AppendMenu(hMenuSmp, MF_STRING, ID_FILE_DIALOG, "DIALOG");

		AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hMenuSmp, "&File");

		SetMenu(hWnd, hMenuBar);
		break;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_DIALOG:
		{
			int result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
			if (result == IDOK)
			{
				MessageBox(NULL, "Clicked Ok", "OK", NULL);
			}
			if (result == IDCANCEL)
			{
				MessageBox(NULL, "CLicked Cancel", "CANCEL", NULL);
			}
			break;
		}
		}
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(1);
		break;
	default:
		return DefWindowProc(hWnd, msgId, wParam, lParam);

	}
	return 0L;

}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR CmndLine, int nShowCmnd)
{
	WNDCLASSEX wx;

	wx.cbSize = sizeof(WNDCLASSEX);
	wx.hInstance = hInstance;
	wx.lpfnWndProc = WndProc;
	wx.cbClsExtra = NULL;
	wx.cbWndExtra = NULL;
	wx.lpszClassName = "MyWindow";
	wx.lpszMenuName = "Untitled";
	wx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wx.style = NULL;
	wx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	RegisterClassEx(&wx);

	HWND hWnd = CreateWindowEx(NULL, "MyWIndow", "Untitled", WS_OVERLAPPEDWINDOW, 100, 200, 300, 400, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, 1);

	MSG msg;

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return 0;
}