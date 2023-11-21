#include "RestrictionEnzyme.h"
#include "FileIO.h"
#include "DNA.h"
using namespace std;

string table;

std::string GetRestrictionEnzymeSequence(std::string name) {
	if (table.empty()) {
		table = FileIO::ReadFileData("RestrictionEnzymeTable");
	}
	DNA ret;
	int pos = table.find(name);
	if (pos == string::npos) {
		cout << "Restriction enzyme " << name << " not found." << endl;
		cout << "Input Restriction Enzyme Recognition Site : ";
		string site;
		cin >> site;
		table += site + "\t" + name + "\n";
		ret.from_str(site);
	}
	else {
		while (pos != -1 && table[pos] != '\n') pos--;
		pos++;
		for (int j = pos; table[j] != '\t'; j++) {
			if (table[j] == 'A') ret.push_back(A);
			else if (table[j] == 'T') ret.push_back(T);
			else if (table[j] == 'G') ret.push_back(G);
			else if (table[j] == 'C') ret.push_back(C);
		}
	}
	FileIO::SaveFileData("RestrictionEnzymeTable", table);
	return ret.str();
}
