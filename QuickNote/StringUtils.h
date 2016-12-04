#pragma once
#include <string>
#include <vector>
using namespace std;

class StringUtils
{
public:
	static vector<string> delimitedStringToVector(string str, char delimited);

	StringUtils();
	~StringUtils();
};

