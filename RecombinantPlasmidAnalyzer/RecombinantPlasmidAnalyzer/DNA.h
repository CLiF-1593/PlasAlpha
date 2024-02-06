#pragma once
#include <vector>
#include <string>

enum Nucleotide { A, G, C, T, X };

#define INDEX_SIZE 5
#define INDEX_PARITY_SIZE 1
#define INDEX_NUMBER_SIZE 4

#define DATA_SIZE 12
#define DATA_PARITY_SIZE 8

#define DATA_COUNT 3
#define DATA_OVERLAP 0

#define CANDIDATE_RATIO 0.3
#define MAXIMUM_CALCULATING_TIME 30000

class DNA : public std::vector<Nucleotide> {
public:
	DNA slice(int begin, int end);
	void ins(int index, Nucleotide nucleotide);
	Nucleotide del(int index);

	std::string to_binary();
	unsigned int to_int();
	void from_binary(std::string binary);
	void from_int(int integer, int size);

	std::string str();
	void from_str(std::string str);
};

int GetEditDistanceResult(DNA& dna1, DNA& dna2, int limit = -1);