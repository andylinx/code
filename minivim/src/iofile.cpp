#include "virable.h"
using std::endl;
void init_file(string name)
{
	File.open(name);
	string ss;
	while (getline(File, ss)) {
		if (*(ss.end() - 1) == '\r' || *(ss.end() - 1) == '\n') ss.erase(ss.end() - 1);
		text.push_back(ss);
	}
}
void out_file(string name)
{
	OFile.open(name);
	for (int j = 0; j < text.size(); j++) {
		for (int i = 0; i < text[j].length(); i++) OFile.put(text[j][i]);
		if (j != text.size() - 1) OFile.put('\n');
	}
	OFile.close();
}
