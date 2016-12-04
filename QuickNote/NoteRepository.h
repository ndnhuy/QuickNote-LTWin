#pragma once

#include "Note.h"
#include "NoteDAO.h"
#include "TagDAO.h"
#include "NoteTagDAO.h"

class NoteRepository
{
public:
	void save(Note* note);
	static NoteRepository* getInstance();


	~NoteRepository();

private:
	NoteDAO* _noteDAO;
	TagDAO* _tagDAO;
	NoteTagDAO* _noteTagDAO;
	

	static NoteRepository* _instance;
	NoteRepository();
};

