#pragma once

#include "Tag.h"
#include "TagDAO.h"

class TagRepository
{
public:
	vector<Tag*>* findAll();

	static TagRepository* getInstance();

	TagRepository();
	~TagRepository();
private:
	TagDAO *_tagDAO;

	static TagRepository* _instance;
};

