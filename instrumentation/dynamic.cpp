#include <iostream>
#include <fstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

json j;

void getSet(char* fname, int input1, int input2, int output) {
	cout << "Saving inputs: " << input1 << " " << input2 << endl;
	string s1(fname);
	if (j.find(s1) == j.end()) {
		j[s1]["count"] = 0;
	}
	int count = j[s1]["count"];
	count++;
	j[s1]["count"] = count;
	string s2 = "set"+to_string(count);
	j[s1][s2]["input"].push_back(input1);
	j[s1][s2]["input"].push_back(input2);
	j[s1][s2]["output"] = output;
	//cout << j.dump(4) << endl;
}

void initialize() {	
	ifstream i("info.json");
	if (i) {
		i >> j;
	}
}

void store() {
	ofstream o("info.json");
	o << setw(4) << j << endl;
}

int compareSet(char* fname, int input1, int input2) {
	string s1(fname);
	if (j.find(s1) != j.end()) {
		int count = j[s1]["count"];
		for (int i = 0; i < count; i++) {
			string s2 = "set"+to_string(i+1);
			int i1 = j[s1][s2]["input"][0];
			int i2 = j[s1][s2]["input"][1];
			if (input1 == i1 && input2 == i2) {
				cout << "Match of inputs " << input1 << " " << input2 << " found!" << endl;
				int o = j[s1][s2]["output"];
				return o;
			}
		}
	}
	return -1;
}
