#include <iostream>
#include <fstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

json j;

void getInputType(char* fname, char* type) {
	string s1(fname);
	string s2(type);
	if (j[s1]["count"] == 1) {
		j[s1]["input_type"].push_back(s2);
	}
}

void getReturnType(char* fname, char* type) {
	string s1(fname);
	string s2(type);
	if (j.find(s1) != j.end()) {
		int count = j[s1]["count"];
		j[s1]["count"] = count + 1;
	} else {
		j[s1]["return_type"] = s2;
		j[s1]["count"] = 1;
	}
}

void getInt(char* fname, int input) {
	string s1(fname);
	long l = j[s1]["count"];
	string s2 = "set"+to_string(l);
	j[s1][s2]["input"].push_back(input);
	cout << j.dump(4) << endl;
}
