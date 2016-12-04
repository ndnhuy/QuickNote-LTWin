#include "stdafx.h"
#include "Note.h"


Note::Note()
{
}


Note::~Note()
{
	for (int i = 0; i < _tags->size(); i++) {
		delete _tags->at(i);
	}
	_tags->clear();
}

int Note::getId() {
	return _id;
}

void Note::setId(int id) {
	_id = id;
}

string Note::getContent() {
	return _content;
}

void Note::setContent(string content) {
	_content = content;
}

vector<Tag*>* Note::getTags() {
	return _tags;
}

void Note::setTags(vector<Tag*> *tags) {
	_tags = tags;
}
