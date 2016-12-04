#include "stdafx.h"
#include "TagRepository.h"

TagRepository*	TagRepository::_instance;

vector<Tag*>* TagRepository::findAll() {
	return _tagDAO->findAll();
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
}


TagRepository::~TagRepository()
{
}
