#pragma once
#include <string>
#include "Note.h"
#include "NoteRepository.h"
using namespace std;
class NoteService
{
public:
	void createNote(string content, string commaDelimitedTagNames);

	static class NoteService* getInstance();
	~NoteService();
private:
	NoteRepository* _noteRepository;

	static NoteService* _instance;
	NoteService();
};

