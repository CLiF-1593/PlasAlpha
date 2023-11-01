#include "DNA.h"
#include <assert.h>
#include <algorithm>
using namespace std;

int GCD(int a, int b) {
	if (a < b) {
		int tmp = a;
		a = b;
		b = tmp;
	}
	while (b) {
		int tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}

// =============================================
// ==================== DNA ====================
// =============================================

DNA DNA::slice(int begin, int end) {
	DNA new_dna;
	if (begin < 0) begin = 0;
	if (end >= (int)this->size()) end = this->size() - 1;
	if(this->empty()) return new_dna;
	for (int i = begin; i < end; i++) {
		int index = i;
		while (index < 0) index += this->size();
		while (index >= (int)this->size()) {
			index -= this->size();
		}
		new_dna.push_back((*this)[index]);
	}
	return new_dna;
}

void DNA::ins(int index, Nucleotide nucleotide) {
	if(0 <= index && index <= this->size()) {
		this->push_back(X);
		for(int i = this->size() - 1; i > index; i--) {
			(*this)[i] = (*this)[i - 1];
		}
		(*this)[index] = nucleotide;
	}
}

Nucleotide DNA::del(int index) {
	if(0 <= index && index < this->size()) {
		Nucleotide nucleotide = (*this)[index];
		for(int i = index; i < this->size() - 1; i++) {
			(*this)[i] = (*this)[i + 1];
		}
		this->pop_back();
		return nucleotide;
	}
	return X;
}

std::string DNA::to_binary() {
	std::string ret;
	while (this->size() & 3) {
		this->push_back(A);
	}
	for (int i = 0; i < this->size(); i += 4) {
		char c = 0;
		for (int j = 0; j < 4; j++) {
			c <<= 2;
			c += (*this)[i + j];
		}
		ret += c;
	}
	return ret;
}

unsigned int DNA::to_int() {
	unsigned int ret = 0;
	for (int i = 0; i < this->size(); i++) {
		ret <<= 2;
		ret += (*this)[i];
	}
	return ret;
}

void DNA::from_binary(std::string binary) {
	DNA ret;
	for (int i = 0; i < binary.size(); i++) {
		DNA section;
		char c = binary[i];
		for (int k = 0; k < 4; k++) {
			section.push_back(static_cast<Nucleotide>(c & 3));
			c >>= 2;
		}
		reverse(section.begin(), section.end());
		ret.insert(ret.end(), section.begin(), section.end());
	}
	(*this) = ret;
	return;
}

void DNA::from_int(int integer, int size) {
	DNA ret;
	for (int i = 0; i < size; i++) {
		ret.push_back(static_cast<Nucleotide>(integer & 3));
		integer >>= 2;
	}
	reverse(ret.begin(), ret.end());
	(*this) = ret;
	return;
}

std::string DNA::str() {
	string ret;
	for (int i = 0; i < this->size(); i++) {
		switch ((*this)[i]) {
			case A: ret += 'A'; break;
			case G: ret += 'G'; break;
			case C: ret += 'C'; break;
			case T: ret += 'T'; break;
			case X: ret += '_'; break;
		}
	}
	return ret;
}

// ===================================================
// ================== Edit Distance ==================
// ===================================================

class ReturnType {
public:
	int distance = -1;
	int prev_dna1_pos = -1;
	int prev_dna2_pos = -1;

	bool operator<(ReturnType& other) const {
		return this->distance < other.distance;
	}
};

// Bottom-up DP
ReturnType EditDistance(DNA &dna1, DNA &dna2, int limit) {
	int size1 = dna1.size();
	int size2 = dna2.size();

	std::vector<ReturnType> cache((size2 + 1) * (size1 + 1));
	std::vector<ReturnType> container(3);
	for (register int i = 0; i <= size1; ++i) {
		for (register int j = 0; j <= size2; ++j) {
			ReturnType ret;
			if (i + j == 0) {
				ret.distance = 0;
			}
			else if (i == 0) {
				ret.distance = j;
				ret.prev_dna1_pos = i;
				ret.prev_dna2_pos = j - 1;
			}
			else if (j == 0) {
				ret.distance = i;
				ret.prev_dna1_pos = i - 1;
				ret.prev_dna2_pos = j;
			}
			else {
				container[0] = (cache[(size2 + 1) * (i - 1) + j - 1]);
				container[1] = (cache[(size2 + 1) * i + j - 1]);
				container[2] = (cache[(size2 + 1) * (i - 1) + j]);

				container[0].distance += (dna1[i - 1] != dna2[j - 1]);
				container[0].prev_dna1_pos = i - 1;
				container[0].prev_dna2_pos = j - 1;

				container[1].distance++;
				container[1].prev_dna1_pos = i;
				container[1].prev_dna2_pos = j - 1;

				container[2].distance++;
				container[2].prev_dna1_pos = i - 1;
				container[2].prev_dna2_pos = j;

				if(container[0].distance < container[1].distance && container[0].distance < container[2].distance)
					ret = container[0];
				else if(container[1].distance < container[0].distance && container[1].distance < container[2].distance)
					ret = container[1];
				else
					ret = container[2];
			}
			if (limit != -1 && ret.distance > limit) goto ENDLOOP;
			cache[(size2 + 1) * i + j] = ret;
		}
	}

	ENDLOOP:
	DNA dna_result_1, dna_result_2;
	ReturnType back = cache.back();
	int cur_dna1_pos = size1;
	int cur_dna2_pos = size2;
	
	while (back.prev_dna1_pos != -1 || back.prev_dna2_pos != -1) {
		if (cur_dna1_pos == back.prev_dna1_pos) {
			dna_result_1.push_back(X);
		}
		else {
			dna_result_1.push_back(dna1.back());
			dna1.pop_back();
		}
		if (cur_dna2_pos == back.prev_dna2_pos) {
			dna_result_2.push_back(X);
		}
		else {
			dna_result_2.push_back(dna2.back());
			dna2.pop_back();
		}
		cur_dna1_pos = back.prev_dna1_pos;
		cur_dna2_pos = back.prev_dna2_pos;
		back = cache[(size2 + 1) * back.prev_dna1_pos + back.prev_dna2_pos];
	}
	reverse(dna_result_1.begin(), dna_result_1.end());
	reverse(dna_result_2.begin(), dna_result_2.end());
	dna1 = dna_result_1;
	dna2 = dna_result_2;
	return cache[(size2 + 1) * size1 + size2];
}

// ==================================================
// ================== DNA_Analyzer ==================
// ==================================================


int GetEditDistanceResult(DNA& dna1, DNA& dna2, int limit) {
	//return GetDelta(dna1, dna2, limit);
	auto result = EditDistance(dna1, dna2, limit);
	return result.distance;
}

void DNA::from_str(std::string str) {
	for (int i = 0; i < str.size(); i++) {
		if(str[i] == 'A')
			this->push_back(A);
		else if(str[i] == 'G')
			this->push_back(G);
		else if(str[i] == 'C')
			this->push_back(C);
		else if(str[i] == 'T')
			this->push_back(T);
		else if(str[i] == '_')
			this->push_back(X);
	}
}
