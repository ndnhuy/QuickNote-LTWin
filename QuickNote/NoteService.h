#pragma once
#include <string>
#include <vector>
#include "Note.h"
#include "NoteRepository.h"
#include "Observable.h"

using namespace std;
class NoteService
{
public:
	vector<Note*>* findAll();
	void createNote(string content, string commaDelimitedTagNames);
	void registerObservable(Observable* o);

	static class NoteService* getInstance();
	~NoteService();
private:
	NoteRepository* _noteRepository;
	vector<Observable*> *_observables;

	static NoteService* _instance;
	NoteService();
};

