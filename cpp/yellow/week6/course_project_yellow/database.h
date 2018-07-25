#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>
#include <utility>
#include <ostream>

#include "date.h"
#include "node.h"

using Predicate = std::function<bool(const Date &, const std::string &)>;

class Database {
public:
	void Add(const Date &date, const std::string &event);
	void Print(std::ostream &os) const;
	int RemoveIf(Predicate pred);
	std::vector<std::pair<Date, std::string>> FindIf(Predicate pred) const;
	std::pair<Date, std::string> Last(const Date &d) const;

private:
	std::map<Date, std::set<std::string>> date2set_;
	std::map<Date, std::vector<std::string>> date2vector_;

};

std::ostream &operator<<(std::ostream &os, std::pair<Date, std::string> p);
