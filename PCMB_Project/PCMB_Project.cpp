#include"PCMB_Project.h"
#include"ExplicitServer.h"
#include<math.h>
#define PI 3.142

double RefractiveIndex(double n1, double n2, double angle1, double angle2)
{
	double result = 0.0;
	double t_angle1 = 0.0, t_angle2 = 0.0;

	if (n1 == 0.0)
	{
		angle1 = angle1 *(PI / 180.0);
		angle2 = angle2 *(PI / 180.0);
		t_angle1 = sin(angle1);
		t_angle2 = sin(angle2);
		result = (n2* t_angle1) / t_angle2;
	}
	else if (n2 == 0.0)
	{
		angle1 = angle1 *(PI / 180.0);
		angle2 = angle2 *(PI / 180.0);
		t_angle1 = sin(angle1);
		t_angle2 = sin(angle2);
		result = (n1*t_angle2) / t_angle1;
	}
	else
	{
		MessageBox(NULL, L"Unexpected Error", L"ERROR", MB_OK);
		exit(EXIT_FAILURE);
	}
	return (result);
}


struct physics {
	TCHAR Str1[50];
	TCHAR Str2[50];
	TCHAR Str3[50];
	TCHAR Str4[50];
	TCHAR Str5[50];
};
struct physics2 {
	double RefractiveIndex1;
	double RefractiveIndex2;
	double theta1;
	double theta2;
	double Ans;
};


physics in1;
physics2 inn1;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclassex;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("01-Bitmap");
	

	wndclassex.cbSize = sizeof(WNDCLASSEX);
	wndclassex.cbClsExtra = 0;
	wndclassex.cbWndExtra = 0;
	wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassex.hIcon = LoadIcon(hInstance,L"MYICON");
	wndclassex.hIconSm = LoadIcon(hInstance,L"MYICON2");
	wndclassex.hInstance = hInstance;
	wndclassex.style = CS_HREDRAW | CS_VREDRAW;
	wndclassex.lpszMenuName = NULL;
	wndclassex.lpszClassName = szClassName;
	wndclassex.lpfnWndProc = WndProc;
	wndclassex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);


	if (!RegisterClassEx(&wndclassex))
	{
		MessageBox(NULL, L"RegisterClassEx() Failed!!!!", L"ERROR_1", MB_OK);
		exit(EXIT_FAILURE);
	}

	hwnd = CreateWindow(szClassName, L"Bitmap window",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
		WS_THICKFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		CW_USEDEFAULT,CW_USEDEFAULT,
		CW_USEDEFAULT,CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	if (!(hwnd))
	{
		MessageBox(NULL, L"CreateWindow() Failed!!!1", L"ERROR_2", MB_OK);
		exit(EXIT_FAILURE);
	}

	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hwnd);


	while (GetMessage((&msg), NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP hBitmap;
	void BitmapAndFont(HWND ,static HBITMAP);
	HINSTANCE hInstance;
	switch (iMsg)
	{
	case WM_CREATE:
		hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(MYBITMAP_0));
		InvalidateRect(hwnd, NULL, false);
		break;
	case WM_PAINT:
		BitmapAndFont(hwnd,hBitmap);	
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
			case VK_SPACE:
				hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
				DialogBox(hInstance, TEXT("PCMBPROJECT"), hwnd, DlgProc);
				break;
			case VK_ESCAPE:
				DestroyWindow(hwnd);
				break;
		}
		break;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HMODULE hModule = NULL;
	static int number = 0;
	TCHAR tchar_str[100];
	typedef double(*RefractiveIndexptr)(double, double, double, double);
	RefractiveIndexptr pfn = NULL;
	double danswer;
	int imyans;
	double temp1, temp2;
	switch (iMsg)
	{
		case WM_INITDIALOG:
			SetFocus(GetDlgItem(hDlg, ID_ET_RI1));
			SendDlgItemMessage(hDlg, ID_RB_PHYSICS ,BM_SETCHECK, 1, 0);
			EnableWindow(GetDlgItem(hDlg, ID_ET_FN2), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_ET_SN2), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_ET_FN3), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_ET_SN3), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_ET_FN4), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_ET_SN4), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_ET_ANS2), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_ET_ANS3), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_ET_ANS4), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_PB_CHEMISTRY_SUBMIT), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_PB_MATHS_SUBMIT), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_PB_BIOLOGY_SUBMIT), FALSE);
			return(TRUE);
			break;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
/* PHYSICS ____START____*/
				case ID_RB_PHYSICS:
						SendDlgItemMessage(hDlg, ID_RB_MATHS, BM_SETCHECK, 0, 1);
						SendDlgItemMessage(hDlg, ID_RB_CHEMISTRY, BM_SETCHECK, 0, 1);
						SendDlgItemMessage(hDlg, ID_RB_BIOLOGY, BM_SETCHECK, 0, 1);
					
						SetWindowText(GetDlgItem(hDlg, ID_ET_RI1), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_RI2), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_AI), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_AR), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_ANS1), TEXT(""));

						EnableWindow(GetDlgItem(hDlg, ID_ET_FN2), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_SN2), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_ANS2), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_FN3), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_SN3), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_ANS3), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_FN4), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_SN4), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_ANS4), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_PB_MATHS_SUBMIT), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_PB_CHEMISTRY_SUBMIT), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_PB_BIOLOGY_SUBMIT), FALSE);
					break;
				case ID_ET_RI1:
					GetDlgItemText(hDlg,ID_ET_RI1,in1.Str1,40);
					inn1.RefractiveIndex1 = _wtof(in1.Str1);
					//swprintf_s(in1.Str1, TEXT("%f"), inn1.RefractiveIndex1);
					//SetDlgItemText(hDlg, ID_ET_ANS1, in1.Str1);
					break;
				case ID_ET_RI2:
					GetDlgItemText(hDlg, ID_ET_RI2, in1.Str2, 40);
					inn1.RefractiveIndex2 = _wtof(in1.Str2);
					break;
				case ID_ET_AI:
					GetDlgItemText(hDlg, ID_ET_AI, in1.Str3, 40);
					inn1.theta1 = _wtof(in1.Str3);
					break;
				case ID_ET_AR:
					GetDlgItemText(hDlg, ID_ET_AR, in1.Str4, 40);
					inn1.theta2 = _wtof(in1.Str4);
					break;
				case ID_PB_PHYSICS_SUBMIT:
					hModule = LoadLibrary(L"FirstDynamicLinkLibrary.dll");
					if (hModule == NULL)
					{
						MessageBox(NULL, L"Error in LoadLibrary()", L"ERROR", MB_OK);
						exit(EXIT_FAILURE);
					}

					pfn = (RefractiveIndexptr)GetProcAddress(hModule, "RefractiveIndex");
					if (inn1.RefractiveIndex1 == 0) {
						danswer = pfn(inn1.RefractiveIndex1, inn1.RefractiveIndex2, inn1.theta1, inn1.theta2);
						swprintf(tchar_str, 100, L"%f", danswer);
					}
					else if (inn1.RefractiveIndex2 == 0)
					{
						danswer = pfn(inn1.RefractiveIndex1, inn1.RefractiveIndex2,inn1.theta1, inn1.theta2);
						swprintf(tchar_str, 100, L"%f", danswer);
					}
					SetDlgItemText(hDlg, ID_ET_ANS1, tchar_str);
					FreeLibrary(hModule);
					break;
/* PHYSICS ____END____*/
/* MATHEMATICS ____START____*/
				case ID_RB_MATHS:
						SendDlgItemMessage(hDlg, ID_RB_PHYSICS, BM_SETCHECK, 0, 1);
						SendDlgItemMessage(hDlg, ID_RB_CHEMISTRY, BM_SETCHECK, 0, 1);
						SendDlgItemMessage(hDlg, ID_RB_BIOLOGY, BM_SETCHECK, 0, 1);
						SendDlgItemMessage(hDlg, ID_RB_MATHS, BM_SETCHECK, 1, 0);
						
						SetWindowText(GetDlgItem(hDlg, ID_ET_RI1), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_RI2), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_AI), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_AR), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_ANS1), TEXT(""));
					break;
				case ID_ET_FN2:
					break;
				case ID_ET_SN2:
					break;
				case ID_ET_ANS2:
					break;
				case ID_PB_MATHS_SUBMIT:
					break;
/* MATHEMATICS ____END____*/
/* CHEMISTRY ____START____*/
				case ID_RB_CHEMISTRY:
						SendDlgItemMessage(hDlg, ID_RB_PHYSICS, BM_SETCHECK, 0, 1);
						SendDlgItemMessage(hDlg, ID_RB_BIOLOGY, BM_SETCHECK, 0, 1);
						SendDlgItemMessage(hDlg, ID_RB_MATHS, BM_SETCHECK, 0, 0);
						SendDlgItemMessage(hDlg, ID_RB_CHEMISTRY, BM_SETCHECK, 1, 1);
					break;
				case ID_GB_CHEMISTRY:
					break;
				case ID_ET_FN3:
					break;
				case ID_ET_SN3:
					break;
				case ID_ET_ANS3:
					break;
				case ID_PB_CHEMISTRY_SUBMIT:
					break;
/* CHEMISTRY ____END____*/
/* BIOLOGY ____START____*/
				case ID_RB_BIOLOGY:
						SendDlgItemMessage(hDlg, ID_RB_PHYSICS, BM_SETCHECK, 0, 1);
						SendDlgItemMessage(hDlg, ID_RB_MATHS, BM_SETCHECK, 0, 0);
						SendDlgItemMessage(hDlg, ID_RB_CHEMISTRY, BM_SETCHECK, 0, 1);
						SendDlgItemMessage(hDlg, ID_RB_BIOLOGY, BM_SETCHECK, 1, 1);
					break;
				case ID_ET_FN4:
					break;
				case ID_ET_SN4:
					break;
				case ID_ET_ANS4:
					break;
				case ID_PB_BIOLOGY_SUBMIT:
					break;
/* BIOLOGY ____END____*/
				case ID_PB_BACK://COMMON
					EndDialog(hDlg, 0);
					break;
			}
			return (TRUE);
			break;
	}
	return(FALSE);
}

void BitmapAndFont(HWND hwnd,static HBITMAP hBitmap)
{
	HDC myhdc_0, myhdc_1;
	PAINTSTRUCT ps;
	RECT rect;
	BITMAP bitmap;
	HFONT hFont;
	
	myhdc_0 = BeginPaint(hwnd, &ps);
		myhdc_1 = CreateCompatibleDC(myhdc_0);
			SelectObject(myhdc_1, hBitmap);
			GetClientRect(hwnd, &rect);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			StretchBlt(myhdc_0, 0, 0, rect.right - rect.left,
						rect.bottom - rect.top, 
						myhdc_1, 0, 0, bitmap.bmWidth,
						bitmap.bmHeight, NOTSRCCOPY);

			hFont = CreateFont(75, 40, 0, 0, FW_EXTRABOLD, FALSE, FALSE, FALSE,
				ANSI_CHARSET, OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
				FF_MODERN, TEXT("Times New Roman"));
			SetBkMode(myhdc_0, TRANSPARENT);

			SetTextColor(myhdc_0, RGB(24, 24, 24));
			SelectObject(myhdc_0, hFont);
			TextOut(myhdc_0,rect.left,rect.top, L"     Press Space Bar to Continue", 
					wcslen(L"     Press Space Bar to Continue"));
		DeleteObject(hFont);
		DeleteDC(myhdc_1);
	EndPaint(hwnd, &ps);
}

