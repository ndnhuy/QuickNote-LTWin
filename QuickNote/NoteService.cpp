#include "stdafx.h"
#include "NoteService.h"
#include "StringUtils.h"
#include "NoteRepository.h"

NoteService*	NoteService::_instance;
NoteService* NoteService::getInstance() {
	if (!_instance) {
		_instance = new NoteService();
	}

	return _instance;
}

vector<Note*>* NoteService::findAll()
{
	return _noteRepository->findAll();
}

void NoteService::createNote(string content, string commaDelimitedTagNames) {
	Note* note = new Note();
	note->setContent(content);

	vector<Tag*> *tags = new vector<Tag*>();
	vector<string> tagNameStrings = StringUtils::delimitedStringToVector(commaDelimitedTagNames, ',');
	for (int i = 0; i < tagNameStrings.size(); i++) {
		tags->push_back(new Tag(tagNameStrings[i]));
	}

	note->setTags(tags);

	_noteRepository->save(note);

	// notify all registered observables
	if (_observables != NULL) {
		for (int i = 0; i < _observables->size(); i++) {
			_observables->at(i)->notify();
		}
	}
}

void NoteService::registerObservable(Observable * o)
{
	_observables->push_back(o);
}


NoteService::NoteService()
{
	_noteRepository = NoteRepository::getInstance();
	_observables = new vector<Observable*>();
}


NoteService::~NoteService()
{
	for (int i = 0; i < _observables->size(); i++) {
		delete _observables->at(i);
	}
	_observables->clear();
}
