#include <iostream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

json j;

void getInputType(char* fname, char* type) {
	string s1(fname);
	string s2(type);
	j[s1]["input_type"].push_back(s2);
	std::cout << j.dump(4) << std::endl;
}

void getReturnType(char* fname, char* type) {
	string s1(fname);
	string s2(type);
	j[s1]["return_type"] = s2;
	j[s1]["input_type"] = json::array();
	// j[s1]["return_type"]["info"].push_back()
}

void getInt(char* fname, int input) {
	string s1(fname);
	j[s1]["input"].push_back(input);
	std::cout << j.dump(4) << std::endl;
}
