#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>
#include "TextQuery.hpp"
#include "make_plural.hpp"

using std::string;
using std::ifstream;
using std::ostream;
using std::set;
using std::getline;
using std::istringstream;
using std::endl;
using std::shared_ptr;
using std::vector;

TextQuery::TextQuery(ifstream &is): file(new vector<string>)
{
	string text;
	while(getline(is, text)) {
		file->push_back(text);
		int n = file->size() - 1;
		istringstream line(text);
		string word;
		while(line >> word) {
			auto &lines = wm[word]; // lines is a shared_ptr
			if (!lines)
				lines.reset(new set<line_no>);
			lines->insert(n);
		}
	}
}

QueryResult TextQuery::query(const string &sought) const
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}

ostream &print_results(ostream &os, const QueryResult &qr)
{
	os << qr.sought << " occurs " <<qr.lines->size() << " "
		<< make_plural(qr.lines->size(), "time", "s") << endl;
	for (auto num : *qr.lines)
		os << "\t(line " << num + 1 << ") "
			<< *(qr.file->begin() + num) << endl;
	return os;
}

