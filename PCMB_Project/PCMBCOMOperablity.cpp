#define UNICODE
#include"PCMBCOMOperablity.h"

#import "Math.tlb" no_namespace, raw_interfaces_only
#include"math.tlh"
#include<windows.h>
#include<stdio.h>

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"kernel32.lib")
#pragma comment(lib,"ole32.lib")
#pragma comment(lib,"oleaut32.lib")
#pragma comment(lib,"advapi32.lib")

HRESULT hr;
int WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		hr = CoInitialize(NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("ComError"), TEXT("Error"), MB_OKCANCEL);
			exit(EXIT_FAILURE);
		}
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_DETACH:
		CoUninitialize();
		break;

	}
	//MessageBox(NULL, TEXT("MSGS"), TEXT("MSGBOX"), MB_OK);
	return (TRUE);
}
extern "C" long MultiplicationOfTwoIntegers(int num1,int num2)
{
	long IMultiply = 0;
	TCHAR str[100];
	CLSID clsidMath;

	IMath *app;
	
	hr = CLSIDFromProgID(L"ManagedSeverForInterop.Math", &clsidMath);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Error in COM -.Net1"), TEXT("Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	hr = CoCreateInstance(clsidMath, NULL, CLSCTX_INPROC_SERVER, __uuidof(IMath), (void**)&app);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Error in COM -.Net2"), TEXT("Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	hr = app->MultiplicationOfTwoIntegers(num1, num2, &IMultiply);
	if (FAILED(hr))
	{
		exit(EXIT_FAILURE);
	}
	app->Release();
	return IMultiply;
}

