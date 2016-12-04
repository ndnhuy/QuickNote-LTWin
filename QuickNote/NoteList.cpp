#include "stdafx.h"
#include "NoteList.h"
#include <commctrl.h>
#include <windowsX.h>
#include <winuser.h>
#include "StringUtils.h"

void NoteList::update()
{
	vector<Note*>* notes = _noteService->findAll();
	for (int i = 0; i < notes->size(); i++)  {
		LV_ITEM lv;
		lv.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
		lv.iItem = 0;
		lv.iSubItem = 0;
		lv.pszText = StringUtils::toWCHAR(notes->at(i)->getContent());
		ListView_InsertItem(*_hwnd, &lv);
	}

	if (!notes) {
		for (int i = 0; i < notes->size(); i++) {
			delete notes->at(i);
		}
		notes->clear();
	}
}

NoteList::NoteList(HWND* hwnd)
{
	_hwnd = hwnd;
	_noteService = NoteService::getInstance();
}


NoteList::~NoteList()
{
}
