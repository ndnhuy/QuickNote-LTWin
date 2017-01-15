#pragma once

#include "Tag.h"
#include "TagDAO.h"
#include "NoteTagDAO.h"

class TagRepository
{
public:
	vector<Tag*>* findAll();
	vector<Tag*>* findTagByNameLikeAndSortByFrequency(string name);
	static TagRepository* getInstance();

	~TagRepository();
private:
	TagDAO* _tagDAO;
	NoteTagDAO* _noteTagDAO;

	bool compareMethod(Tag* tag1, Tag* tag2);

	static TagRepository* _instance;
	TagRepository();
};

