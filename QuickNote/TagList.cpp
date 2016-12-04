#include "stdafx.h"
#include "TagList.h"
#include <commctrl.h>
#include <windowsX.h>
#include <winuser.h>
#include "StringUtils.h"
void TagList::update() {

	vector<Tag*> *tags = _tagRepository->findAll();
	TreeView_DeleteAllItems(*_hwnd);

	for (int i = 0; i < tags->size(); i++) {
		TV_INSERTSTRUCT tv;
		tv.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
		tv.hParent = NULL;
		tv.item.iImage = NULL;
		tv.item.iSelectedImage = NULL;
		tv.item.pszText = StringUtils::toWCHAR(tags->at(i)->getName());
		TreeView_InsertItem(*_hwnd, &tv);
	}
}

TagList::TagList(HWND *hwnd)
{
	_hwnd = hwnd;
	_tagRepository = TagRepository::getInstance();
}



TagList::~TagList()
{
}
