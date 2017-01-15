#pragma once
#include "NoteService.h"
class NoteListController : public Observer
{
public:
	void update();
	void setSelectedTagName(string name);
	NoteListController(HWND*);
	~NoteListController();
private:
	HWND* _hwnd;
	NoteService* _noteService;
	string _selectedTagName;
};

