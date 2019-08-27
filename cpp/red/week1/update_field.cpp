#include <iostream>
#include <sstream>
#include <map>
#include <vector>

#include "airline_ticket.h"

using namespace std;

istream &operator>>(istream &is, Date &d)
{
    char c;
    is >> d.year >> c >> d.month >> c >> d.day;
    return is;
}

istream &operator>>(istream &is, Time &t)
{
    char c;
    is >> t.hours >> c >> t.minutes;
    return is;
}

bool operator==(const Date &lhs, const Date &rhs)
{
    return vector<int>({lhs.year, lhs.month, lhs.day}) ==
           vector<int>({rhs.year, rhs.month, rhs.day});
}

bool operator==(const Time &lhs, const Time &rhs)
{
    return vector<int>({lhs.hours, lhs.minutes}) ==
           vector<int>({rhs.hours, rhs.minutes});
}

ostream &operator<<(ostream &os, const Date &d)
{
    os << d.month << "/" << d.day << "/" << d.year;
    return os;
}

ostream &operator<<(ostream &os, const Time &t)
{
    os << t.hours << ":" << t.minutes;
    return os;
}

#define UPDATE_FIELD(ticket, field, values) {           \
    if (values.find(#field) != values.end()) {          \
        istringstream iss(values.at(#field));           \
        iss >> ticket.field;                            \
    }                                                   \
}