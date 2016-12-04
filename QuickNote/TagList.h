#pragma once
#include "Observer.h"
#include "TagRepository.h"
class TagList : public Observer
{
public:
	void update();
	TagList(HWND*);
	~TagList();

private:
	HWND* _hwnd;
	TagRepository* _tagRepository;
};

