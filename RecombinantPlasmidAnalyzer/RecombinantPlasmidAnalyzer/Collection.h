#pragma once
#include "DNA.h"
#include <string>

using namespace std;

class Collection {
private:
	string vector_name;
	DNA vector_seq;

public:
	Collection();
	~Collection();

	Collection* SetVectorName(string vector_name) { this->vector_name = vector_name; return this; }
	Collection* SetVectorSeq(DNA vector_seq) { this->vector_seq = vector_seq; return this; }
};

