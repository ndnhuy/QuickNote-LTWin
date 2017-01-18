#include "stdafx.h"
#include "NoteService.h"
#include "StringUtils.h"
#include "NoteRepository.h"
#include "TagRepository.h"

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

vector<Note*>* NoteService::findByTagName(string tagName)
{
	if (tagName == "") {
		return findAll();
	}
	return _noteRepository->findByTagName(tagName);
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

	// update cached
	_cachedSumNotes = _noteTagDAO->count();
}

void NoteService::registerObservable(Observable * o)
{
	_observables->push_back(o);
}

int NoteService::getSumOfNotesForEachTag()
{
	return _cachedSumNotes;
}

NoteService::NoteService()
{
	_noteRepository = NoteRepository::getInstance();
	_observables = new vector<Observable*>();
	_noteTagDAO = NoteTagDAO::getInstance();
	_cachedSumNotes = _noteTagDAO->count();
}


NoteService::~NoteService()
{
	for (int i = 0; i < _observables->size(); i++) {
		delete _observables->at(i);
	}
	_observables->clear();
}
