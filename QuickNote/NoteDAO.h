#pragma once
#include "Note.h"

class NoteDAO
{
public:
	int save(Note* note);

	static NoteDAO* getInstance();

	NoteDAO();
	~NoteDAO();
private:

	static NoteDAO* _instance;
};

