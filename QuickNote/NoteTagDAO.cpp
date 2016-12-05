#include "stdafx.h"
#include "NoteTagDAO.h"
#include <fstream>
#include "DatabaseConfig.h"
#include "StringUtils.h"
using namespace std;

NoteTagDAO*	NoteTagDAO::_instance;

void NoteTagDAO::save(int noteId, int tagId) {
	ofstream os(DatabaseConfig::FILE_NAME_NOTETAG, ios::app);
	if (os.is_open()) {
		os << noteId << " " << tagId << endl;
		os << endl;
	}
	os.close();
}

vector<int>* NoteTagDAO::findNoteIDsByTagId(int tagId)
{
	vector<int>* IDs = new vector<int>();

	ifstream is(DatabaseConfig::FILE_NAME_NOTETAG);
	string line;
	if (is.is_open()) {
		while (getline(is, line)) {
			vector<string> noteIdAndTagId = StringUtils::delimitedStringToVector(line, ' ');
			if ( tagId == stoi(noteIdAndTagId.at(1)) ) {
				IDs->push_back( stoi(noteIdAndTagId.at(0)) );
			}
		}
	}
}

NoteTagDAO* NoteTagDAO::getInstance() {
	if (!_instance) {
		_instance = new NoteTagDAO();
	}

	return _instance;
}

NoteTagDAO::NoteTagDAO()
{
}


NoteTagDAO::~NoteTagDAO()
{
}
