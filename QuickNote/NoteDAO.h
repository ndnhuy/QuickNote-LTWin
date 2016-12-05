#pragma once
#include "Note.h"
#include <vector>

class NoteDAO
{
public:
	int save(Note* note);
	vector<Note*>* findAll();
	vector<Note*>* findByTagName(string tagName);

	static NoteDAO* getInstance();

	NoteDAO();
	~NoteDAO();
private:

	static NoteDAO* _instance;
};

