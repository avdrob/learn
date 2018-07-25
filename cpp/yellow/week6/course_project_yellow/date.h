#pragma once

#include <string>
#include <ostream>
#include <sstream>

class Date {
public:
	Date(unsigned year, unsigned month, unsigned day);
	std::string GetDate() const;
	unsigned GetYear() const;
	unsigned GetMonth() const;
	unsigned GetDay() const;

private:
	const unsigned year_, month_, day_;
	const std::string date_;
};

bool operator<(const Date &lhs, const Date &rhs);
bool operator<=(const Date &lhs, const Date &rhs);
bool operator>(const Date &lhs, const Date &rhs);
bool operator>=(const Date &lhs, const Date &rhs);
bool operator==(const Date &lhs, const Date &rhs);
bool operator!=(const Date &lhs, const Date &rhs);

std::ostream &operator<<(std::ostream &os, const Date &d);

Date ParseDate(std::istream &iss);
