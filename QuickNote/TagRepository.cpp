#include "stdafx.h"
#include "TagRepository.h"

TagRepository*	TagRepository::_instance;

vector<Tag*>* TagRepository::findAll() {
	// call DAO to get all tag
	return NULL;
}


TagRepository* TagRepository::getInstance() {
	if (!_instance) {
		_instance = new TagRepository();
	}

	return _instance;
}

TagRepository::TagRepository()
{
}


TagRepository::~TagRepository()
{
}
