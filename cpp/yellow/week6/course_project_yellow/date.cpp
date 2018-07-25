#include <string>
#include <ostream>
#include <sstream>
#include <iomanip>
#include <exception>
#include <tuple>

#include "date.h"

using namespace std;

Date::Date(unsigned year, unsigned month, unsigned day)
	: year_(year), month_(month), day_(day),
	date_(to_string(year) + "-" + to_string(month) + "-" + to_string(day))
{
}

string Date::GetDate() const
{
	return date_;
}

unsigned Date::GetYear() const
{
	return year_;
}

unsigned Date::GetMonth() const
{
	return month_;
}

unsigned Date::GetDay() const
{
	return day_;
}

bool operator<(const Date &lhs, const Date &rhs)
{
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
		make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator<=(const Date &lhs, const Date &rhs)
{
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <=
		make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator>(const Date &lhs, const Date &rhs)
{
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >
		make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator>=(const Date &lhs, const Date &rhs)
{
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >=
		make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator==(const Date &lhs, const Date &rhs)
{
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) ==
		make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator!=(const Date &lhs, const Date &rhs)
{
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) !=
		make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

ostream &operator<<(ostream &os, const Date &d)
{
	static char old_fill = os.fill();

	os << setfill('0');
	os << setw(4) << d.GetYear();
	os << "-" << setw(2) << d.GetMonth();
	os << "-" << setw(2) << d.GetDay();
	os << setfill(old_fill);

	return os;
}

Date ParseDate(istream &iss)
{
	string s;
	iss >> s;
	istringstream tmpis(s);

	string year_str, month_str, day_str;
	unsigned year, month, day;

	tmpis >> ws;
	year = month = day = 0;
	try {
		getline(tmpis, year_str, '-');
		year = stoul(year_str);
		getline(tmpis, month_str, '-');
		month = stoul(month_str);
		getline(tmpis, day_str);
		day = stoul(day_str);
	}
	catch (exception &e) {
		throw runtime_error("Wrong date format: " + s);
	}

	if (year > 9999)
		throw runtime_error("Wrong year value: " + year);

	if (month < 1 || month > 12)
		throw runtime_error("Wrong month value: " + month);

	if (day < 1 || day > 31)
		throw runtime_error("Wrong day value: " + day);

	return Date(year, month, day);
}
