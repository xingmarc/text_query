#include <iostream>
#include <string>
#include <fstream>

#include "TextQuery.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::string;

void runQueries(ifstream &infile)
{
	TextQuery tq(infile);
	while(true) {
		cout << "Enter word to look for, or q to quit: ";
		string s;
		if (!(cin >> s) || s == "q") break;
		print_results(cout, tq.query(s)) << endl;
	}
}

int main() {
	ifstream infile("midnight_summer_dream_act_1_secene_1.txt");
	runQueries(infile);
	return 0;
}
