#include "Print.h"
#include <iostream>
#include <windows.h>
using namespace std;

/*
[Info]
> Original DNA : 1.txt.dna
> Plasmid Info : pCES208 Seq.txt
> Restriction Enzyme Info : [1st]PstI (CTGCAG) / [2nd]BamHI (GGATCC)
> Plasmid DNA (fwd) : Sequencing Result/HST04_Lab1_1_C2_pCES208_Sanger_F.txt
> Plasmid DNA (rev) : Sequencing Result/HST04_Lab1_1_C2_pCES208_Sanger_R.txt

[Result]
> Original Nucleotide Number : 263
> Same Nucleotide Number : 241
> Correctness : 91.634981%
> Beta PDF Correctness : 95.667793%
> Availability : Enable

> Sequence
Label           :                                                                                          <PstI><------------------------
Origin Plasmid  : GCGCAATTAACCCTCACTAAAGGGAACAAAAGCTGGGTACCGGGCCCCCCCTCGAGGTCGACGGTATCGATAAGCTTGATATCGAATTCCTGCAGGTGCCAACTGAGTAAATAAATTAGC
Forward Plasmid : ACCCAAGTCATACTCACTAA_GGGA_CAAA_GCTGGGTACCGGGCCCCCCCTCGAGGTCGACGGTATCGATAAGCTTGATATCGAATTCCTGCAGGTGCCAACTGAGTAAATAAATTAGC
Reverse Plasmid : GCGCAATTAACCCTCACTAAAGGGAACAAAAGCTGGGTACCGGGCCCCCCCTCGAGGTCGACGGTATCGATAAGCTTGATATCGAATTCCTGCAGGTGCCAACTGAGTAAATAAATTAGC
Matching Result : ^ ^   ^ ^ ^^        ^    ^    ^

Specific Result : \X\XXX\X\X\\XXXXXXXX\XXXX\XXXX\XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Label           : ------Data-------------------------------><BamHI>

Origin Plasmid  : GTCCAGTATCACGCGTCTGACTGGTCAACTGTTCGATCGTTAGGATCCACTAGTTCTAGAGCGGCCGCCACCGCGGTGGAGCTCCAATTCGCCCTATAGTGAGTCGTATTACGCGCGGTG
Forward Plasmid : GTCCAGTATCACGCGTCTGACTGGTCAACTGTTCGATCGTTAGGATCCACTAGTTCTAGAGCGGCCGCCACCGCGGTGGAGCTCCAATTCGCCCTATAGTGAGTCGTATTACGCGCGGTG
Reverse Plasmid : GTCCAGTATCACGCGTCTGACTGGTCAACTGTTCGATCGTTAGGATCCACTAGTTCTAGAGCGGCCGCCACCGCGGTGGAGCTCCAATTCGCCCTATAGTGAGTCGTAT_ACGCGCG_T_
Matching Result :
	   ^       ^ ^
Specific Result : XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX/XXXXXXX/X/

Label           :
Origin Plasmid  : ACCACCATTTGCCCCATATCACC
Forward Plasmid : ACCACCATTTGCCCCATATCACC
Reverse Plasmid : ACCAGCAT__GCTCCG_A_CGGG
Matching Result :     ^   ^^  ^  ^^ ^ ^^^
Specific Result : XXXX/XXX//XX/XX//X/X///



===================================================
*/

void PrintRaw(std::string output) {
	cout << output;
}

void Print(std::string output) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int attr = 15;
	string keyword = "";
	for (int i = 0; i < output.size(); i++) {
		char c = output[i];
		if (c == ' ') {
			cout << " ";
			continue;
		}
		if ((c == '>' && (i == 0 || output[i-1] == '\n')) || c == '/') {
			SetConsoleTextAttribute(hConsole, 7);
			cout << c;
			SetConsoleTextAttribute(hConsole, attr);
			continue;
		}
		if (attr == -1) {
			if (output[i] == 'E') SetConsoleTextAttribute(hConsole, 10);
			else SetConsoleTextAttribute(hConsole, 12);
			while(output[i] != '\n') cout << output[i++];
			attr = 15;
			keyword.clear();
			cout << endl;
			SetConsoleTextAttribute(hConsole, attr);
			continue;
		}
		if (attr == -2) {
			while (output[i] != '\n') {
				if (output[i] == 'A') SetConsoleTextAttribute(hConsole, 12);
				else if (output[i] == 'G') SetConsoleTextAttribute(hConsole, 10);
				else if (output[i] == 'C') SetConsoleTextAttribute(hConsole, 14);
				else if (output[i] == 'T') SetConsoleTextAttribute(hConsole, 11);
				else SetConsoleTextAttribute(hConsole, 15);
				cout << output[i++];
			}
			attr = 15;
			keyword.clear();
			cout << endl;
			SetConsoleTextAttribute(hConsole, attr);
			continue;
		}
		
		SetConsoleTextAttribute(hConsole, attr);
		cout << c;
		
		if (c == ':') {
			if (keyword == "OriginalDNA") attr = 14;
			else if (keyword == "PlasmidInfo") attr = 14;
			else if (keyword == "RestrictionEnzymeInfo") attr = 10;
			else if (keyword == "PlasmidDNA(fwd)") attr = 14;
			else if (keyword == "PlasmidDNA(rev)") attr = 14;
			else if (keyword == "OriginalNucleotideNumber") attr = 14;
			else if (keyword == "SameNucleotideNumber") attr = 14;
			else if (keyword == "Correctness") attr = 11;
			else if (keyword == "BetaPDFCorrectness") attr = 9;
			else if (keyword == "Availability") attr = -1;
			else if (keyword == "Label") attr = 13;
			else if (keyword == "OriginPlasmid") attr = -2;
			else if (keyword == "ForwardPlasmid") attr = -2;
			else if (keyword == "ReversePlasmid") attr = -2;
			else if (keyword == "MatchingResult") attr = 15;
			else if (keyword == "SpecificResult") attr = 15;
			else attr = 15;
		}
		if (c == '\n') attr = 15, keyword.clear();
		else keyword.push_back(c);
	}
}
