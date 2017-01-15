#pragma once
#include "Note.h"
#include <vector>

class NoteDAO
{
public:
	int save(Note* note);
	vector<Note*>* findAll();
	Note* findById(int id);

	static NoteDAO* getInstance();

	NoteDAO();
	~NoteDAO();
private:

	static NoteDAO* _instance;
};

