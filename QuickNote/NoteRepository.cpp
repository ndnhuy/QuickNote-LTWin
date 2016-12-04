#include "stdafx.h"
#include "NoteRepository.h"

NoteRepository*	NoteRepository::_instance;

void NoteRepository::save(Note* note) {
	int noteId = _noteDAO->save(note);

	vector<Tag*> *tags = note->getTags();
	for (int i = 0; i < tags->size(); i++) {
		Tag* retrievedTag = _tagDAO->saveOrGetIfExist( tags->at(i) );
		_noteTagDAO->save(noteId, retrievedTag->getId());
	}
}

vector<Note*>* NoteRepository::findAll()
{
	return _noteDAO->findAll();
}

NoteRepository* NoteRepository::getInstance() {
	if (!_instance) {
		_instance = new NoteRepository();
	}

	return _instance;
}

NoteRepository::NoteRepository()
{
	_noteDAO = NoteDAO::getInstance();
	_tagDAO = TagDAO::getInstance();
	_noteTagDAO = NoteTagDAO::getInstance();
}


NoteRepository::~NoteRepository()
{
}
