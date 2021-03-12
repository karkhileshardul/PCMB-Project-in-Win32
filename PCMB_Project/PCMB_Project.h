#include<stdio.h>
#include<Windows.h>

#define MYBITMAP_0	501
#define WIN_WIDTH	800
#define WIN_HEIGHT	600

//dialog box related 

#define ID_RB_PHYSICS			101
#define ID_GB_PHYSICS			102
#define ID_ET_RI1				103
#define ID_ET_RI2				104
#define ID_ET_AI				105
#define ID_ET_AR				106
#define	ID_ET_ANS1				107
#define ID_PB_PHYSICS_SUBMIT	108

#define	ID_RB_MATHS				111
#define ID_GB_MATHS				112
#define ID_ET_FN2				113
#define ID_ET_SN2				114
#define ID_ET_ANS2				115
#define ID_PB_MATHS_SUBMIT		116

#define	ID_RB_CHEMISTRY			121
#define ID_GB_CHEMISTRY			122
#define ID_ET_FN3				123
#define ID_ET_SN3				124
#define ID_ET_ANS3				125
#define ID_PB_CHEMISTRY_SUBMIT	126

#define	ID_RB_BIOLOGY			131
#define ID_GB_BIOLOGY			132
#define ID_ET_FN4				133
#define ID_ET_SN4				134
#define ID_ET_ANS4				135
#define ID_PB_BIOLOGY_SUBMIT	136

#define ID_PB_MODIFY	160
#define ID_PB_BACK		150

// callback function declaration
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);






