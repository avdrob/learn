#include <ostream>
#include <utility>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

#include <stdexcept>
#include <iostream>
#include <cassert>

#include "database.h"

using namespace std;

void Database::Add(const Date &date, const string &event)
{
	auto res = date2set_[date].insert(event);
	if (res.second)
		date2vector_[date].push_back(event);

	assert(date2set_.at(date).size() == date2vector_.at(date).size());
}

void Database::Print(ostream &os) const
{
	for (const auto &p : date2vector_) {
		Date d = p.first;
		for (const auto &ev : p.second)
			os << d << " " << ev << endl;
	}
}

int Database::RemoveIf(Predicate pred)
{
	int cnt = 0;
	vector<Date> date2del = {};

	for (auto &item : date2set_) {
		Date date = item.first;
		set<string> &events = item.second;
		vector<string> ev2del = {};

		for (const string &event : events)
			if (pred(date, event))
				ev2del.push_back(event);
		cnt += ev2del.size();

		if (ev2del.size() == 0)
			continue;

		vector<string> &tmp_vec = date2vector_.at(date);
		for (const string &event : ev2del) {
			events.erase(event);
			tmp_vec.erase(remove(tmp_vec.begin(), tmp_vec.end(), event),
								tmp_vec.end());
		}

		if (date2set_.at(date).size() == 0)
			date2del.push_back(date);

		assert(date2set_.at(date).size() == date2vector_.at(date).size());
	}

	if (date2del.size() > 0)
		for (const Date &date : date2del) {
			date2set_.erase(date);
			date2vector_.erase(date);
		}

	assert(date2set_.size() == date2vector_.size());

	return cnt;
}

vector<pair<Date, string>> Database::FindIf(Predicate pred) const
{
	vector<pair<Date, string>> entries = {};

	for (const auto &item : date2vector_) {
		Date date = item.first;
		const vector<string> &events = item.second;
		for (const auto &event : events)
			if (pred(date, event))
				entries.push_back(make_pair(date, event));
	}

	return entries;
}

pair<Date, string> Database::Last(const Date &d) const
{
	auto it = date2vector_.upper_bound(d);

	if (it == date2vector_.begin())
		throw string("No entries");

	it--;
	return make_pair(it->first, it->second.back());
}

ostream &operator<<(ostream &os, pair<Date, string> p)
{
	os << p.first << " " << p.second;
	return os;
}
