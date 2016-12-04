#pragma once
class NoteTagDAO
{
public:
	void save(int noteId, int tagId);

	static NoteTagDAO* getInstance();
	
	
	~NoteTagDAO();
private:
	static NoteTagDAO* _instance;
	NoteTagDAO();
};

