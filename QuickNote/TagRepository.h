#pragma once

#include "Tag.h"

class TagRepository
{
public:
	vector<Tag*>* findAll();

	static TagRepository* getInstance();

	TagRepository();
	~TagRepository();
private:
	static TagRepository* _instance;
};

