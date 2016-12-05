#pragma once
#include "Tag.h"
class TagDAO
{
public:
	Tag* saveOrGetIfExist(Tag* tag);
	int count();
	Tag* findByName(string name);
	vector<Tag*>* findAll();

	static TagDAO* getInstance();
	
	~TagDAO();
private:
	static TagDAO* _instance;
	TagDAO();
};

