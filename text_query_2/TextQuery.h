#ifndef TEXTQUERY_HPP
#define TEXTQUERY_HPP

#include <vector>
#include <map>
#include <set>
#include <string>
#include <memory>
#include <fstream>

class QueryResult;

class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&) const;
private:
	std::shared_ptr<std::vector<std::string>> file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult {
friend std::ostream& print(std::ostream&, const QueryResult&);

public:
	typedef std::vector<std::string>::size_type line_no;
	typedef std::set<line_no>::const_iterator line_it;

	QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p,
			std::shared_ptr<std::vector<std::string>> f):
		sought(s), lines(p), file(f) {}

	std::set<line_no>::size_type size() const { return lines -> size(); }
	line_it begin() const { return lines -> cbegin(); }
	line_it end() const { return lines -> cend(); }

	std::shared_ptr<std::vector<std::string>> get_file() { return file; }

private:
	std::string sought;
	std::shared_ptr<std::set<TextQuery::line_no>> lines;
	std::shared_ptr<std::vector<std::string>> file;
};
std::ostream &print(std::ostream&, const QueryResult&);

#endif

