#pragma once
#include <string>
#include <vector>
#include "Note.h"
#include "NoteRepository.h"
#include "Observable.h"
#include "NoteTagDAO.h"

using namespace std;
class NoteService
{
public:
	vector<Note*>* findAll();
	vector<Note*>* findByTagName(string tagName);
	void createNote(string content, string commaDelimitedTagNames);
	void registerObservable(Observable* o);
	int getSumOfNotesForEachTag();

	static class NoteService* getInstance();
	~NoteService();
private:
	NoteRepository* _noteRepository;
	vector<Observable*> *_observables;
	NoteTagDAO* _noteTagDAO;

	int _cachedSumNotes;

	static NoteService* _instance;
	NoteService();
};

