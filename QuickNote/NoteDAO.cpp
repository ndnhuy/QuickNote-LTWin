#include "stdafx.h"
#include "NoteDAO.h"
#include <fstream>
#include "DatabaseConfig.h"

NoteDAO* NoteDAO::_instance;

NoteDAO* NoteDAO::getInstance() {
	if (!_instance) {
		_instance = new NoteDAO();
	}

	return _instance;
}

int NoteDAO::save(Note* note) {
	int count = 0;
	ifstream is(DatabaseConfig::FILE_NAME_NOTE);
	if (is.is_open()) {
		string line;
		while (getline(is, line)) {
			if (line == "") {
				count++;
			}
		}
	}
	is.close();

	int nextId = count + 1;
	ofstream os(DatabaseConfig::FILE_NAME_NOTE, ios::app);
	if (os.is_open()) {
		os << nextId << endl;
		os << note->getContent() << endl;
		os << endl;
	}
	os.close();

	return nextId;
}

vector<Note*>* NoteDAO::findAll()
{
	vector<Note*>* notes = new vector<Note*>();
	ifstream is(DatabaseConfig::FILE_NAME_NOTE);
	if (is.is_open()) {
		int id = 0;
		string content = "";

		string line;
		while (getline(is, line)) {
			if (line == "") {
				Note* note = new Note();
				note->setId(id);
				note->setContent(content);

				notes->push_back(note);

				id = 0;
				content = "";

				continue;
			}

			if (id == 0) {
				id = stoi(line);
				continue;
			}

			if (content == "") {
				content = line;
				continue;
			}
		}
	}
	is.close();

	return notes;
}

vector<Note*>* NoteDAO::findByTagName(string tagName)
{

}

NoteDAO::NoteDAO()
{
}


NoteDAO::~NoteDAO()
{
}
