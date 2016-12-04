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

NoteDAO::NoteDAO()
{
}


NoteDAO::~NoteDAO()
{
}
