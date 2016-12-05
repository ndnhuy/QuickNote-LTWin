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

vector<Note*>* NoteRepository::findByTagName(string tagName)
{
	Tag* tag = _tagDAO->findByName(tagName);
	vector<int>* noteIDs = _noteTagDAO->findNoteIDsByTagId(tag->getId());
	vector<Note*>* notes = new vector<Note*>();
	for (int i = 0; i < noteIDs->size(); i++) {
		notes->push_back( _noteDAO->findById(noteIDs->at(i)) );
	}
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
