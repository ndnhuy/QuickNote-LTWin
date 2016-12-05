// QuickNote.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "QuickNote.h"
#include <commctrl.h>
#include <windowsX.h>
#include <winuser.h>
#include <float.h>
#include <stdio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
#define MAX_LOADSTRING 100

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hwnd);
void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm);

#include "NoteService.h"
#include "StringUtils.h"

WCHAR* getEnteredTextAsBuffer(HWND textboxHwnd, WCHAR* textboxName, bool emptyCheck);
WCHAR* concat(WCHAR* source, WCHAR* dest);
void init();

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_QUICKNOTE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_QUICKNOTE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QUICKNOTE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BTNFACE + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_QUICKNOTE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
      CW_USEDEFAULT, 0, 800, 500, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_NOTIFY, OnNotify);

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



#include "CreatingNoteObservable.h"
#include "TagList.h"
#include "NoteList.h"

HWND txtNote;
HWND txtTag;
HWND lstNote;
HWND lstTag;

CreatingNoteObservable* observable = new CreatingNoteObservable();
TagList* tagList = new TagList(&lstTag);
NoteList* noteList = new NoteList(&lstNote);

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	// Lấy font hệ thống
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	// Note
	HWND hwnd = CreateWindowEx(0, L"STATIC", L"Note", WS_CHILD | WS_VISIBLE | SS_LEFT, 220, 10, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	txtNote = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE, 250, 10, 300, 20, hWnd, NULL, hInst, NULL);
	SendMessage(txtNote, WM_SETFONT, WPARAM(hFont), TRUE);

	SendMessage(txtNote, EM_LIMITTEXT, (WPARAM)0, 0);
	
	// Tag
	hwnd = CreateWindowEx(0, L"STATIC", L"Tags", WS_CHILD | WS_VISIBLE | SS_LEFT, 220, 40, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	txtTag = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE, 250, 40, 300, 20, hWnd, NULL, hInst, NULL);
	SendMessage(txtTag, WM_SETFONT, WPARAM(hFont), TRUE);

	SendMessage(txtTag, EM_LIMITTEXT, 0, 0);

	// List of tags
	lstTag = CreateWindowEx(0, WC_TREEVIEW, _T("Tree View"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_SIZEBOX | WS_VSCROLL | WS_TABSTOP | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
		10, 10, 200, 300,
		hWnd,
		(HMENU)IDC_LIST_TAG, hInst, NULL);

	// Init
	TV_INSERTSTRUCT tvDrive;
	tvDrive.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvDrive.hParent = NULL;
	tvDrive.item.iImage = NULL;
	tvDrive.item.iSelectedImage = NULL;
	tvDrive.item.pszText = L"HAHAHA";
	HTREEITEM hDrive = TreeView_InsertItem(lstTag, &tvDrive);

	tvDrive.item.pszText = L"HEHEHE";
	TreeView_InsertItem(lstTag, &tvDrive);

	// List of note
	lstNote = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, _T("List View"),
		WS_CHILD | LVS_REPORT | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP | LVS_ICON | LVS_EDITLABELS | LVS_SHOWSELALWAYS,
		220, 70, 200, 100,
		hWnd, (HMENU)IDC_LIST_NOTE, hInst, NULL);
	SendMessage(lstNote, WM_SETFONT, WPARAM(hFont), TRUE);

	// Init columns
	LVCOLUMN lvCol;

	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt = LVCFMT_LEFT;

	lvCol.cx = 200;
	lvCol.pszText = _T("Notes");
	ListView_InsertColumn(lstNote, 0, &lvCol);

	LV_ITEM lv;
	lv.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	lv.iItem = 0;
	lv.iSubItem = 0;
	lv.pszText = L"HAHA";
	ListView_InsertItem(lstNote, &lv);

	// save button
	hwnd = CreateWindowEx(0, L"BUTTON", L"Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 220, 200, 60, 40, hWnd, (HMENU)IDC_BUTTON_SAVE, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);


	init();

	return true;
}

void init() {
	observable->attach(tagList);
	observable->attach(noteList);
	NoteService::getInstance()->registerObservable(observable);

	tagList->update();
	noteList->update();
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	WCHAR* bufferNote = NULL;
	WCHAR* bufferTag = NULL;
	switch (id) {
		case IDC_BUTTON_SAVE: {
		
			bufferNote = getEnteredTextAsBuffer(txtNote, L"note", true);
			if (bufferNote == NULL) {
				return;
			}

			bufferTag = getEnteredTextAsBuffer(txtTag, L"tag", false);
			if (bufferTag == NULL) {
				return;
			}

			NoteService::getInstance()->createNote(StringUtils::toString(bufferNote), 
												   StringUtils::toString(bufferTag));

			break;
		}
	}

	if (!bufferNote) {
		delete[] bufferNote;
	}

	if (!bufferTag) {
		delete[] bufferTag;
	}
}

WCHAR* getEnteredTextAsBuffer(HWND textboxHwnd, WCHAR* textboxName, bool emptyCheck) {
	int textLength = GetWindowTextLength(textboxHwnd);
	if (emptyCheck && textLength == 0) {
		MessageBox(textboxHwnd, concat(L"Please enter ", textboxName), L"Error", MB_OK);
		return NULL;
	}
	WCHAR* buffer = new WCHAR[textLength + 1];
	GetWindowText(textboxHwnd, buffer, textLength + 1);

	return buffer;
}

WCHAR* concat(WCHAR* source, WCHAR* dest) {
	int bufferSize = wcsnlen_s(source, INT_MAX) + wcsnlen_s(dest, INT_MAX) + 1;
	WCHAR* result = new WCHAR[bufferSize];
	wcscpy_s(result, bufferSize, source);
	wcscat_s(result, bufferSize, dest);

	return result;
}

LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm)
{
	switch (pnm->code) {
		case TVN_SELCHANGED:
			
			break;
	}

	return 0;
}

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code here...
	EndPaint(hWnd, &ps);
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}