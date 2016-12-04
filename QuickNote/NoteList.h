#pragma once
#include "NoteService.h"
class NoteList : public Observer
{
public:
	void update();
	NoteList(HWND*);
	~NoteList();
private:
	HWND* _hwnd;
	NoteService* _noteService;
};

