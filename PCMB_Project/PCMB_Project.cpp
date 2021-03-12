#include"PCMB_Project.h"
#include"PCMBCOMOperablity.h"


struct physics0 {
	TCHAR Str1[50];
	TCHAR Str2[50];
	TCHAR Str3[50];
	TCHAR Str4[50];
	TCHAR Str5[50];
};
struct physics1 {
	double RefractiveIndex1;
	double RefractiveIndex2;
	double theta1;					
	double theta2;
	double Ans;
};

struct maths0 {
	int FirstNumber;
	int SecondNumber;
	int AnsGCD;
};

struct maths1 {
	int FirstNumber;
	int SecondNumber;
	long Ans;
};


physics0 physics0_in1;
physics1 physics1_in1;
maths0 maths0_in1;
maths1 maths1_in1;
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
	wndclassex.hIcon = LoadIcon(hInstance,TEXT("MYICON"));
	wndclassex.hIconSm = LoadIcon(hInstance,TEXT("MYICON2"));
	wndclassex.hInstance = hInstance;
	wndclassex.style = CS_HREDRAW | CS_VREDRAW;
	wndclassex.lpszMenuName = NULL;
	wndclassex.lpszClassName = szClassName;
	wndclassex.lpfnWndProc = WndProc;
	wndclassex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);


	if (!RegisterClassEx(&wndclassex))
	{
		MessageBox(NULL, TEXT("RegisterClassEx() Failed!!!!"), TEXT("ERROR_1"), MB_OK);
		exit(EXIT_FAILURE);
	}

	hwnd = CreateWindow(szClassName, TEXT("Bitmap window"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
		WS_THICKFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		CW_USEDEFAULT,CW_USEDEFAULT,
		CW_USEDEFAULT,CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	if (!(hwnd))
	{
		MessageBox(NULL, TEXT("CreateWindow() Failed!!!1"), TEXT("ERROR_2"), MB_OK);
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
	typedef int(*findgcdptr)(int,int);
	typedef long(*MultiplicationOfTwoIntegers)(int, int);
	RefractiveIndexptr RefractiveIndexPtr_pfn0 = NULL;
	findgcdptr findgcdptr_pfn0 = NULL;
	MultiplicationOfTwoIntegers multiplyintegersptr_pfn0 = NULL;
	double danswer;
	double ianswer;
	long lanswer;
	int imyans;
	double temp1, temp2;
	switch (iMsg)
	{
		case WM_INITDIALOG:
			SetFocus(GetDlgItem(hDlg, ID_ET_RI1));
			SendDlgItemMessage(hDlg, ID_RB_PHYSICS ,BM_SETCHECK, 1, 0);
			return(TRUE);
			break;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
/* PHYSICS ____START____*/
/*				case ID_RB_PHYSICS:
						SendDlgItemMessage(hDlg, ID_RB_MATHS, BM_SETCHECK, 0, 1);
						SendDlgItemMessage(hDlg, ID_RB_CHEMISTRY, BM_SETCHECK, 0, 1);
					

						SetWindowText(GetDlgItem(hDlg, ID_ET_RI1), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_RI2), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_AI), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_AR), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_ANS1), TEXT(""));

						/*
						EnableWindow(GetDlgItem(hDlg, ID_ET_FN2), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_SN2), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_ANS2), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_FN3), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_SN3), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_ANS3), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_PB_MATHS_SUBMIT), FALSE);
						EnableWindow(GetDlgItem(hDlg, ID_PB_CHEMISTRY_SUBMIT), FALSE);
						*/
/*					break;
				case ID_ET_RI1:
					GetDlgItemText(hDlg,ID_ET_RI1,physics0_in1.Str1,40);
					physics1_in1.RefractiveIndex1 = atof(physics0_in1.Str1);
					//swprintf_s(physics0_in1.Str1, TEXT("%f"), physics1_in1.RefractiveIndex1);
					//SetDlgItemText(hDlg, ID_ET_ANS1, physics0_in1.Str1);
					break;
				case ID_ET_RI2:
					GetDlgItemText(hDlg, ID_ET_RI2, physics0_in1.Str2, 40);
					physics1_in1.RefractiveIndex2 = atof(physics0_in1.Str2);
					break;
				case ID_ET_AI:
					GetDlgItemText(hDlg, ID_ET_AI, physics0_in1.Str3, 40);
					physics1_in1.theta1 = atof(physics0_in1.Str3);
					break;
				case ID_ET_AR:
					GetDlgItemText(hDlg, ID_ET_AR, physics0_in1.Str4, 40);
					physics1_in1.theta2 = atof(physics0_in1.Str4);
					break;
				case ID_PB_PHYSICS_SUBMIT:
					hModule = LoadLibrary(TEXT("ExplicitServer.dll")); 
					if (hModule == NULL)
					{
						MessageBox(NULL, TEXT("Error in LoadLibrary()"), TEXT("ERROR"), MB_OK);
						exit(EXIT_FAILURE);
					}

					RefractiveIndexPtr_pfn0 = (RefractiveIndexptr)GetProcAddress(hModule, "RefractiveIndex");
					if (physics1_in1.RefractiveIndex1 == 0) {
						danswer = RefractiveIndexPtr_pfn0(physics1_in1.RefractiveIndex1, physics1_in1.RefractiveIndex2, physics1_in1.theta1, physics1_in1.theta2);
						sprintf_s(tchar_str,TEXT("%f"), danswer);
						//wsprintf(tchar_str,TEXT("%f"), danswer);
						//swprintf(tchar_str, 100, TEXT("%f"), danswer);
					}
					else if (physics1_in1.RefractiveIndex2 == 0)
					{
						danswer = RefractiveIndexPtr_pfn0(physics1_in1.RefractiveIndex1, physics1_in1.RefractiveIndex2,physics1_in1.theta1, physics1_in1.theta2);
						sprintf_s(tchar_str,TEXT("%f"), danswer);
						//swprintf(tchar_str, 100, TEXT("%f"), danswer);
						//wsprintf(tchar_str,TEXT("%f"), danswer);
					}
					SetDlgItemText(hDlg, ID_ET_ANS1, tchar_str);
					FreeLibrary(hModule);
					EnableWindow(GetDlgItem(hDlg, ID_ET_RI1), FALSE);
					EnableWindow(GetDlgItem(hDlg, ID_ET_RI2), FALSE);
					EnableWindow(GetDlgItem(hDlg, ID_ET_AI), FALSE);
					EnableWindow(GetDlgItem(hDlg, ID_ET_AR), FALSE);					
					EnableWindow(GetDlgItem(hDlg, ID_ET_ANS1), FALSE);
					EnableWindow(GetDlgItem(hDlg, ID_PB_PHYSICS_SUBMIT), FALSE);
					break;
/* PHYSICS ____END____*/
/* MATHEMATICS ____START____*/
/*				case ID_RB_MATHS:
						SendDlgItemMessage(hDlg, ID_RB_PHYSICS, BM_SETCHECK, 0, 1);
						SendDlgItemMessage(hDlg, ID_RB_CHEMISTRY, BM_SETCHECK, 0, 1);
						SendDlgItemMessage(hDlg, ID_RB_MATHS, BM_SETCHECK, 1, 0);
						
						SetWindowText(GetDlgItem(hDlg, ID_ET_RI1), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_RI2), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_AI), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_AR), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_ANS1), TEXT(""));
					break;
				case ID_ET_FN2:
					maths0_in1.FirstNumber=GetDlgItemInt(hDlg, ID_ET_FN2, NULL,TRUE);
					//(hDlg, ID_ET_RI1, physics0_in1.Str1, 40);
					break;
				case ID_ET_SN2:
					maths0_in1.SecondNumber = GetDlgItemInt(hDlg, ID_ET_FN2, NULL, TRUE);
					break;
				case ID_PB_MATHS_SUBMIT:
					hModule = LoadLibrary(TEXT("ExplicitServer.dll"));
					if (hModule == NULL)
					{
						MessageBox(NULL, TEXT("Error in LoadLibrary()"), TEXT("ERROR"), MB_OK);
						exit(EXIT_FAILURE);
					}
					findgcdptr_pfn0 = (findgcdptr)GetProcAddress(hModule, "findgcd");
					ianswer = findgcdptr_pfn0(maths0_in1.FirstNumber, maths0_in1.SecondNumber);
					SetDlgItemInt(hDlg, ID_ET_ANS2, ianswer, TRUE);
					FreeLibrary(hModule);
					EnableWindow(GetDlgItem(hDlg, ID_ET_FN2), FALSE);
					EnableWindow(GetDlgItem(hDlg, ID_ET_SN2), FALSE);
					EnableWindow(GetDlgItem(hDlg, ID_ET_ANS2), FALSE);
					EnableWindow(GetDlgItem(hDlg, ID_PB_MATHS_SUBMIT), FALSE);
					break;
/* MATHEMATICS ____END____*/
/* CHEMISTRY ____START____*/
				case ID_RB_CHEMISTRY:
						SendDlgItemMessage(hDlg, ID_RB_PHYSICS, BM_SETCHECK, 0, 1);
						SendDlgItemMessage(hDlg, ID_RB_MATHS, BM_SETCHECK, 0, 0);
						SendDlgItemMessage(hDlg, ID_RB_CHEMISTRY, BM_SETCHECK, 1, 1);
						SetWindowText(GetDlgItem(hDlg, ID_ET_FN3), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_SN3), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_ANS3), TEXT(""));
						break;
				case ID_ET_FN3:
					maths1_in1.FirstNumber = GetDlgItemInt(hDlg, ID_ET_FN3, NULL, TRUE);					
					break;
				case ID_ET_SN3:
					maths1_in1.SecondNumber = GetDlgItemInt(hDlg, ID_ET_SN3, NULL, TRUE);
					break;
				case ID_PB_CHEMISTRY_SUBMIT:
					hModule = LoadLibrary(TEXT("PCMBCOMOperablity.dll"));
					if (hModule == NULL)
					{
						MessageBox(NULL, TEXT("Error in LoadLibrary()"), TEXT("ERROR"), MB_OK);
						exit(EXIT_FAILURE);
					}
					multiplyintegersptr_pfn0 = (MultiplicationOfTwoIntegers)GetProcAddress(hModule, "MultiplicationOfTwoIntegers");
					if (multiplyintegersptr_pfn0 == NULL) 
					{
						MessageBox(NULL, TEXT("Error in GetProcAddress()!!!"), TEXT("ERROR"), MB_OK);
						exit(EXIT_FAILURE);
					}

					lanswer = multiplyintegersptr_pfn0(maths1_in1.FirstNumber, maths1_in1.SecondNumber);
					SetDlgItemInt(hDlg, ID_ET_ANS3, lanswer, TRUE);
					FreeLibrary(hModule);
					EnableWindow(GetDlgItem(hDlg, ID_ET_FN3), FALSE);
					EnableWindow(GetDlgItem(hDlg, ID_ET_SN3), FALSE);
					EnableWindow(GetDlgItem(hDlg, ID_ET_ANS3), FALSE);
					EnableWindow(GetDlgItem(hDlg, ID_PB_CHEMISTRY_SUBMIT), FALSE);
					break;
/* CHEMISTRY ____END____*/
/*				case ID_PB_MODIFY:
						
						EnableWindow(GetDlgItem(hDlg, ID_ET_RI1), TRUE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_RI2), TRUE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_AI), TRUE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_AR), TRUE);					
						EnableWindow(GetDlgItem(hDlg, ID_ET_ANS1), TRUE);
						EnableWindow(GetDlgItem(hDlg, ID_PB_PHYSICS_SUBMIT), TRUE);
					

						SetWindowText(GetDlgItem(hDlg, ID_ET_RI1), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_RI2), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_AI), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_AR), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_ANS1), TEXT(""));

						EnableWindow(GetDlgItem(hDlg, ID_ET_FN2), TRUE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_SN2), TRUE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_ANS2), TRUE);
						EnableWindow(GetDlgItem(hDlg, ID_PB_MATHS_SUBMIT), TRUE);

						SetWindowText(GetDlgItem(hDlg, ID_ET_FN2), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_SN2), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_ANS2), TEXT(""));
						

						EnableWindow(GetDlgItem(hDlg, ID_ET_FN3), TRUE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_SN3), TRUE);
						EnableWindow(GetDlgItem(hDlg, ID_ET_ANS3), TRUE);
						EnableWindow(GetDlgItem(hDlg, ID_PB_CHEMISTRY_SUBMIT), TRUE);

						SetWindowText(GetDlgItem(hDlg, ID_ET_FN3), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_SN3), TEXT(""));
						SetWindowText(GetDlgItem(hDlg, ID_ET_ANS3), TEXT(""));
*/						
					break;
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
			TextOut(myhdc_0,rect.left,rect.top,TEXT("     Press Space Bar to Continue"),32);
		DeleteObject(hFont);
		DeleteDC(myhdc_1);
	EndPaint(hwnd, &ps);
}


void ComErrorDescriptionString(HWND hwnd,HRESULT hr)
{
	TCHAR* szErrorMessage=NULL;
	TCHAR str[255];

	if(FACILITY_WINDOWS==HRESULT_FACILITY(hr))
	{
		hr=HRESULT_CODE(hr);
	}

	if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |  FORMAT_MESSAGE_FROM_SYSTEM,NULL,hr,MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),(LPTSTR)&szErrorMessage,0,NULL)!=0)
	{
		//sprintf(str,TEXT("%s"),szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
	{
		//sprintf(str,TEXT("[Could not find a description for error # %#x.]\n"),hr);
	}
	MessageBox(hwnd,str,TEXT("COM Error"),MB_OK);
}