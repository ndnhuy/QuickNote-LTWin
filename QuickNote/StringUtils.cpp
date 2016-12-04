#include "stdafx.h"
#include "StringUtils.h"
#include <sstream>
vector<string> StringUtils::delimitedStringToVector(string str, char delimited) {
	vector<string> strings;

	string each;
	for (string::const_iterator it = str.begin(); it != str.end(); it++) {
		if (*it == delimited) {
			if (!each.empty()) {
				strings.push_back(each);
				each.clear();
			}

			continue;
		}

		each += *it;
	}

	if (!each.empty()) {
		strings.push_back(each);
	}

	return strings;
}

StringUtils::StringUtils()
{
}


StringUtils::~StringUtils()
{
}
