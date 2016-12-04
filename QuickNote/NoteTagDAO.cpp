#include "stdafx.h"
#include "NoteTagDAO.h"
#include <fstream>
#include "DatabaseConfig.h"
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
