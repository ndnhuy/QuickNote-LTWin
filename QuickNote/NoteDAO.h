#pragma once
#include "Note.h"
#include <vector>

class NoteDAO
{
public:
	int save(Note* note);
	vector<Note*>* findAll();

	static NoteDAO* getInstance();

	NoteDAO();
	~NoteDAO();
private:

	static NoteDAO* _instance;
};

