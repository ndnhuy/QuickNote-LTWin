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
}


NoteService::NoteService()
{
	_noteRepository = NoteRepository::getInstance();
}


NoteService::~NoteService()
{
}
