#pragma once
#include <vector>
using namespace std;	
class NoteTagDAO
{
public:
	void save(int noteId, int tagId);
	vector<int>* findNoteIDsByTagId(int tagId);
	int count();
	static NoteTagDAO* getInstance();
	
	
	~NoteTagDAO();
private:
	static NoteTagDAO* _instance;
	NoteTagDAO();
};

