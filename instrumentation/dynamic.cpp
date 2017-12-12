#include <iostream>
#include <fstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

json j;

void getSet(char* fname, int input1, int input2, int output) {
	string s1(fname);
	if (j.find(s1) == j.end()) {
		j[s1]["count"] = 0;
	}
	int count = j[s1]["count"];
	j[s1]["count"] = count + 1;
	long l = j[s1]["count"];
	string s2 = "set"+to_string(count);
	j[s1][s2]["input"].push_back(input1);
	j[s1][s2]["input"].push_back(input2);
	j[s1][s2]["output"].push_back(output);
	cout << j.dump(4) << endl;
}

void initialize() {
	ifstream i("info.json");
	i >> j;
}

void store() {
	ofstream o("info.json");
	o << setw(4) << j << endl;
}
