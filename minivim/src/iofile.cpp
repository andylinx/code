#include "virable.h"
void init_file(string name)
{
	File.open(name);
	string ss;
	while (getline(File, ss)) {
		if (*(ss.end() - 1) == '\r' || *(ss.end() - 1) == '\n') ss.erase(ss.end() - 1);
		text.push_back(ss);
	}
}
