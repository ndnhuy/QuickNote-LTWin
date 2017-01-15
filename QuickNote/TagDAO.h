#pragma once
#include "Tag.h"
class TagDAO
{
public:
	Tag* saveOrGetIfExist(Tag* tag);
	int count();
	Tag* findById(int id);
	Tag* findByName(string name);
	vector<Tag*>* findByNameLike(string name);
	vector<Tag*>* findAll();

	static TagDAO* getInstance();
	
	~TagDAO();
private:
	static TagDAO* _instance;
	TagDAO();
};

