#include "stdafx.h"
#include "TagRepository.h"
#include "StringUtils.h"
#include <algorithm>
TagRepository*	TagRepository::_instance;

vector<Tag*>* TagRepository::findAll() {
	return _tagDAO->findAll();
}

bool TagRepository::compareMethod(Tag* tag1, Tag* tag2) {
	return _noteTagDAO->findNoteIDsByTagId(tag1->getId())->size() <
		_noteTagDAO->findNoteIDsByTagId(tag2->getId())->size();
}

vector<Tag*>* TagRepository::findTagByNameLikeAndSortByFrequency(string name)
{
	vector<Tag*>* tags = _tagDAO->findByNameLike(name);
	
	for (int k = 0; k < tags->size(); k++) {
		for (int i = 0; i < tags->size() - 1; i++) {
			if (compareMethod(tags->at(i), tags->at(i + 1))) {
				iter_swap(tags->begin() + i, tags->begin() + i + 1);
			}
		}
	}

	for (int i = 0; i < tags->size(); i++) {
		OutputDebugString(StringUtils::toWCHAR(tags->at(i)->getName() + "\n"));
	}

	return tags;
}


TagRepository* TagRepository::getInstance() {
	if (!_instance) {
		_instance = new TagRepository();
	}

	return _instance;
}

TagRepository::TagRepository()
{
	_tagDAO = TagDAO::getInstance();
	_noteTagDAO = NoteTagDAO::getInstance();
}


TagRepository::~TagRepository()
{
}
