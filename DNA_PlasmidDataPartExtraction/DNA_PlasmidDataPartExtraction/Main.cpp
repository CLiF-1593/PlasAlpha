#include <iostream>
#include <vector>
#include <FileIO.h>
#include "DNA.h"
#include <assert.h>
#include "Plasmid.h"
using namespace std;

#define PLASMID_NUM 2
#define PRINT_NUM 120

#define CHECKING_DELTA 32
#define MARGIN 0

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

int NotNegative(int x) {
	if (x < 0) return 0;
	return x;
}

int GetOffset(DNA& plasmid, DNA& origin) {
	int max_offset = 0;
	int max = 0;
	int min = plasmid.size();
	DNA min_plasmid_part;
	DNA min_origin_part;

	for (int offset = 0; offset < plasmid.size() - origin.size() + 1; offset += CHECKING_DELTA) {
		/*int cnt = 0;
		for (int j = 0; j < origin.size(); j++) {
			if (origin[j] == plasmid[j + offset]) cnt++;
		}
		if (cnt > max) {
			max = cnt;
			max_offset = offset;
		}*/
		DNA plasmid_part = plasmid.slice(offset - MARGIN, offset + origin.size() + MARGIN);
		DNA sub_origin = origin;
		int cost = GetEditDistanceResult(plasmid_part, sub_origin);
		if (cost < min && cost != -1) {
			min = cost;
			min_plasmid_part = plasmid_part;
			min_origin_part = sub_origin;
			max_offset = offset;
		}
	}

	for (int offset = MAX(0, max_offset - CHECKING_DELTA); offset < MIN(max_offset + CHECKING_DELTA, plasmid.size() - origin.size() + 1); offset++) {
		DNA plasmid_part = plasmid.slice(offset - MARGIN, offset + origin.size() + MARGIN);
		DNA sub_origin = origin;
		int cost = GetEditDistanceResult(plasmid_part, sub_origin);
		if (cost < min && cost != -1) {
			min = cost;
			min_plasmid_part = plasmid_part;
			min_origin_part = sub_origin;
			max_offset = offset;
		}
	}

	plasmid = min_plasmid_part;
	origin = min_origin_part;
	return max_offset;
}

void MergeDNA(DNA& fwd, DNA& rev) {
	for (int index = 0; index < fwd.size() || index < rev.size(); index++) {
		bool fwdx = false;
		bool revx = false;
		if (index < fwd.size() && fwd[index] == X) {
			fwdx = true;
		}
		else if (index < rev.size() && rev[index] == X) {
			revx = true;
		}
		if (fwdx && !revx) {
			rev.insert(rev.begin() + index, X);
		}
		else if (!fwdx && revx) {
			fwd.insert(fwd.begin() + index, X);
		}
	}

	assert(fwd == rev);
}

void InsertBlank(vector<int> blank, vector<int> offset_blank, int& offset, DNA& seq, DNA& std) {
	DNA new_seq;
	for (int i = 0, index = 0; i < std.size(); i++) {
		while (blank[index + offset]) {
			new_seq.push_back(X);
			blank[index + offset]--;
		}
		if (std[i] != X) index++;
		new_seq.push_back(seq[i]);
	}
	int ofs = offset;
	for (int i = 0; i < ofs; i++) {
		offset += offset_blank[i];
	}
	seq = new_seq;
}

void OriginInsertBlank(vector<int> blank, DNA& seq) {
	DNA new_seq;
	for (int i = 0; i < seq.size(); i++) {
		while (blank[i]) {
			new_seq.push_back(X);
			blank[i]--;
		}
		new_seq.push_back(seq[i]);
	}
	while (blank.back()) {
		new_seq.push_back(X);
		blank.back();
	}
	seq = new_seq;
}

double betaPDF(double x, double alpha, double beta) {
	if (x < 0 || x > 1 || alpha <= 0 || beta <= 0) {
		return 0.0;
	}

	double numerator = pow(x, alpha - 1) * pow(1 - x, beta - 1);
	double denominator = tgamma(alpha) * tgamma(beta) / tgamma(alpha + beta);

	return numerator / denominator;
}

using namespace std;
int main() {
	cout << "[ DNA Plasmid Data Part Extraction System ]" << endl << endl;
	cout << "> Plasmid Data Part Extraction System" << endl;
	cout << "  ¤¤Random Access of DNA Digital Data Storage System Using Restriction Modification System" << endl << endl;
	cout << "> 2023 KSA R&E" << endl << endl << endl;
	system("Pause");

	srand((unsigned)time(NULL));
	cout << endl;

	cout << "> Select the Plasmid Files" << endl;
	vector<string> plasmid_path_set = FileIO::GetFileNames();
	if (plasmid_path_set.empty()) return 0;

	cout << "> Select the Original DNA Files" << endl;
	vector<string> origin_path_set = FileIO::GetFileNames();
	if (origin_path_set.empty()) return 0;
	
	string plasmid_name_fwd;
	string plasmid_name_rev;
	string origin_name;

	if (origin_path_set.size() * PLASMID_NUM != plasmid_path_set.size()) {
		cout << "> Error: The number of plasmid files is not correct." << endl;
		return 0;
	}

	string plasmid_path_fwd;
	string plasmid_path_rev;
	string origin_path;


	string output = "";
	cout << endl;

	for (int i = 0; i < plasmid_path_set.size(); i+= 2) {
		if (i % PLASMID_NUM == 0) {
			origin_name.clear();
			origin_path = origin_path_set[i / PLASMID_NUM];
			while (origin_path.back() != '\\') {
				origin_name += origin_path.back();
				origin_path.pop_back();
			}
			reverse(origin_name.begin(), origin_name.end());
			origin_path = origin_path_set[i / PLASMID_NUM];
		}

		plasmid_path_fwd = plasmid_path_set[i];
		plasmid_name_fwd.clear();
		while (plasmid_path_fwd.back() != '\\') {
			plasmid_name_fwd += plasmid_path_fwd.back();
			plasmid_path_fwd.pop_back();
		}
		reverse(plasmid_name_fwd.begin(), plasmid_name_fwd.end());
		plasmid_path_fwd = plasmid_path_set[i];

		plasmid_path_rev = plasmid_path_set[i + 1];
		plasmid_name_rev.clear();
		while (plasmid_path_rev.back() != '\\') {
			plasmid_name_rev += plasmid_path_rev.back();
			plasmid_path_rev.pop_back();
		}
		reverse(plasmid_name_rev.begin(), plasmid_name_rev.end());
		plasmid_path_rev = plasmid_path_set[i + 1];

		cout << "> Original DNA : " << origin_name << endl;
		cout << "> Plasmid DNA (fwd) : " << plasmid_name_fwd << endl;
		cout << "> Plasmid DNA (rev) : " << plasmid_name_rev << endl;

		output += "> Original DNA : " + origin_name + "\n";
		output += "> Plasmid DNA (fwd) : " + plasmid_name_fwd + "\n";
		output += "> Plasmid DNA (rev) : " + plasmid_name_rev + "\n";

		DNA origin, plasmid_fwd, plasmid_rev;

		string str = FileIO::ReadFileData(origin_path);
		for (int j = 0; j < str.size(); j++) {
			if (str[j] == 'A') origin.push_back(A);
			else if (str[j] == 'T') origin.push_back(T);
			else if (str[j] == 'G') origin.push_back(G);
			else if (str[j] == 'C') origin.push_back(C);
		}

		str = FileIO::ReadFileData(plasmid_path_fwd);
		for (int j = 0; j < str.size(); j++) {
			if (str[j] == 'A') plasmid_fwd.push_back(A);
			else if (str[j] == 'T') plasmid_fwd.push_back(T);
			else if (str[j] == 'G') plasmid_fwd.push_back(G);
			else if (str[j] == 'C') plasmid_fwd.push_back(C);
		}

		str = FileIO::ReadFileData(plasmid_path_rev);
		for (int j = 0; j < str.size(); j++) {
			if (str[j] == 'A') plasmid_rev.push_back(T);
			else if (str[j] == 'T') plasmid_rev.push_back(A);
			else if (str[j] == 'G') plasmid_rev.push_back(C);
			else if (str[j] == 'C') plasmid_rev.push_back(G);
		}
		reverse(plasmid_rev.begin(), plasmid_rev.end());

		string data = origin.str();

		DNA front_plasmid, back_plasmid;
		front_plasmid.from_str(plasmid_front_seq);
		back_plasmid.from_str(plasmid_back_seq);
		origin.insert(origin.begin(), front_plasmid.begin(), front_plasmid.end());
		origin.insert(origin.end(), back_plasmid.begin(), back_plasmid.end());

		DNA fwd_cmp_origin = origin;
		DNA fwd_cmp_plasmid = plasmid_fwd;
		int fwd_offset = GetOffset(fwd_cmp_origin, fwd_cmp_plasmid);
		DNA rev_cmp_origin = origin;
		DNA rev_cmp_plasmid = plasmid_rev;
		int rev_offset = GetOffset(rev_cmp_origin, rev_cmp_plasmid);

		vector<int> fwd_blank(origin.size() + 1, 0);
		vector<int> rev_blank(origin.size() + 1, 0);
		vector<int> whole_blank(origin.size() + 1, 0);

		for (int index = fwd_offset, j = 0; j < fwd_cmp_origin.size(); j++) {
			if (fwd_cmp_origin[j] == X) fwd_blank[index]++;
			else index++;
		}
		for (int index = rev_offset, j = 0; j < rev_cmp_origin.size(); j++) {
			if (rev_cmp_origin[j] == X) rev_blank[index]++;
			else index++;
		}
		for (int j = 0; j < whole_blank.size(); j++) {
			whole_blank[j] = max(fwd_blank[j], rev_blank[j]);
		}

		plasmid_fwd = fwd_cmp_plasmid;
		plasmid_rev = rev_cmp_plasmid;
		InsertBlank(rev_blank, whole_blank, fwd_offset, plasmid_fwd, fwd_cmp_origin);
		InsertBlank(fwd_blank, whole_blank, rev_offset, plasmid_rev, rev_cmp_origin);
		OriginInsertBlank(whole_blank, origin);

		int fwd_begin = fwd_offset;
		int fwd_end = fwd_offset + plasmid_fwd.size();
		int rev_begin = rev_offset;
		int rev_end = rev_offset + plasmid_rev.size();

		DNA entire_plasmid_fwd = plasmid_fwd;
		DNA entire_plasmid_rev = plasmid_rev;
		DNA entire_origin = origin;

		entire_plasmid_fwd.insert(entire_plasmid_fwd.begin(), fwd_offset, X);
		entire_plasmid_rev.insert(entire_plasmid_rev.begin(), rev_offset, X);
		entire_plasmid_fwd.insert(entire_plasmid_fwd.end(), origin.size() - plasmid_fwd.size(), X);
		entire_plasmid_rev.insert(entire_plasmid_rev.end(), origin.size() - plasmid_rev.size(), X);

		int begin = max(fwd_begin, rev_begin);
		int end = min(fwd_end, rev_end);

		DNA core_plasmid_fwd = entire_plasmid_fwd.slice(begin, end);
		DNA core_plasmid_rev = entire_plasmid_rev.slice(begin, end);
		DNA core_origin = origin.slice(begin, end);

		int previous_nucleotide_num = core_origin.size();
		int same_nucleotide_num = 0;
		double pdf_correctness = 0;
		string result = "";
		string specific_result = "";

		string label = "";

		for (int index = 0, j = 0; j < entire_origin.size(); j++) {
			int prev_size = label.size();
			if (entire_origin[j] != X) {
				int begin, end;
				begin = plasmid_front_seq.size() - PstI_seq.size();
				end = plasmid_front_seq.size() - 1;
				if (index == begin) label += "<";
				if (index == end) {
					int cnt = 0;
					while (label.back() != '<') cnt++, label.pop_back();
					label.insert(label.end(), floor(((double)cnt - (double)string("PstI").size()) / 2.0), '-');
					label += "PstI";
					label.insert(label.end(), round(((double)cnt - (double)string("PstI").size()) / 2.0), '-');
					label += ">";
				}
				begin = plasmid_front_seq.size();
				end = plasmid_front_seq.size() + data.size() - 1;
				if (index == begin) label += "<";
				if (index == end) {
					int cnt = 0;
					while (label.back() != '<') cnt++, label.pop_back();
					label.insert(label.end(), floor(((double)cnt - (double)string("Data").size()) / 2.0), '-');
					label += "Data";
					label.insert(label.end(), round(((double)cnt - (double)string("Data").size()) / 2.0), '-');
					label += ">";
				}
				begin = plasmid_front_seq.size() + data.size();
				end = plasmid_front_seq.size() + data.size() + BamHI_seq.size() - 1;
				if (index == begin) label += "<";
				if (index == end) {
					int cnt = 0;
					while (label.back() != '<') cnt++, label.pop_back();
					label.insert(label.end(), NotNegative(floor(((double)cnt - (double)(string("BamHI").size())) / 2.0)), '-');
					label += "BamHI";
					label.insert(label.end(), NotNegative(round(((double)cnt - (double)(string("BamHI").size())) / 2.0)), '-');
					label += ">";
				}
				index++;
			}
			if(label.size() == prev_size) label += " ";
		}

		label = label.substr(begin, end - begin);

		for (int j = 0; j < core_origin.size(); j++) {
			if (core_origin[j] == core_plasmid_fwd[j] && core_origin[j] == core_plasmid_rev[j]) {
				same_nucleotide_num++;
				result.push_back(' ');
				specific_result.push_back('X');
				pdf_correctness += betaPDF((double)(j) / (double)(core_origin.size() - 1), 1.5, 1.5) / (double)previous_nucleotide_num;
			}
			else if (core_origin[j] == core_plasmid_fwd[j]) specific_result.push_back('/'), result.push_back('^');
			else if (core_origin[j] == core_plasmid_rev[j]) specific_result.push_back('\\'), result.push_back('^');
			else specific_result.push_back(' '), result.push_back('^');

		}

		cout << "> Nucleotide Matching : " << same_nucleotide_num << " / " << previous_nucleotide_num << endl;
		cout << "> Correctness : " << (double)same_nucleotide_num / (double)previous_nucleotide_num * 100 << "%" << endl;
		cout << "> Beta PDF Correctness : " << pdf_correctness * 100.0 << "%" << endl << endl;

		output += "> Original Nucleotide Number : " + to_string(previous_nucleotide_num) + "\n";
		output += "> Same Nucleotide Number : " + to_string(same_nucleotide_num) + "\n";
		output += "> Correctness : " + to_string((double)same_nucleotide_num / (double)previous_nucleotide_num * 100) + "%\n";
		output += "> Beta PDF Correctness : " + to_string(pdf_correctness * 100.0) + "%\n\n";

		cout << "> Result" << endl;

		output += "> Result\n";

		string plasmid_fwd_str = core_plasmid_fwd.str();
		string plasmid_rev_str = core_plasmid_rev.str();
		string origin_str = core_origin.str();

		int index = 0;
		while (index < plasmid_fwd_str.size()) {
			int begin = index;
			int end = index + PRINT_NUM;
			if(end > plasmid_fwd_str.size()) end = plasmid_fwd_str.size();
			string str_ = label.substr(begin, end - begin);
			string str0 = origin_str.substr(begin, end - begin);
			string str1 = plasmid_fwd_str.substr(begin, end - begin);
			string str2 = plasmid_rev_str.substr(begin, end - begin);
			string str3 = result.substr(begin, end - begin);
			string str4 = specific_result.substr(begin, end - begin);
			//string str3 = origin_str.substr(begin, end - begin);
			cout << "Label           : " << str_ << endl;
			cout << "Origin Plasmid  : " << str0 << endl;
			cout << "Forward Plasmid : " << str1 << endl;
			cout << "Reverse Plasmid : " << str2 << endl;
			cout << "Matching Result : " << str3 << endl;
			cout << "Specific Result : " << str4 << endl << endl;

			output += "Label           : " + str_ + "\n";
			output += "Origin Plasmid  : " + str0 + "\n";
			output += "Forward Plasmid : " + str1 + "\n";
			output += "Reverse Plasmid : " + str2 + "\n";
			output += "Matching Result : " + str3 + "\n";
			output += "Specific Result : " + str4 + "\n\n";
			index = end;
		}

		cout << endl << endl;
		cout << "===================================================";
		cout << endl << endl;

		output += "\n\n";
		output += "===================================================\n\n";
		output += "\n\n";

		if ((i + 2) % PLASMID_NUM == 0) {
			origin_path += "_plasmid_result.txt";
			FileIO::SaveFileData(origin_path, output);
			output.clear();
			cout << "Saved : " << origin_path << endl;

			cout << endl << endl;
			cout << "===================================================";
			cout << endl << endl;
		}
	}
}