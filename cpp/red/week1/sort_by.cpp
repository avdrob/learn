#include <algorithm>
#include <vector>
#include <iostream>

#include "airline_ticket.h"

using namespace std;

bool operator<(const Date &lhs, const Date &rhs)
{
    return vector<int>({lhs.year, lhs.month, lhs.day}) <
           vector<int>({rhs.year, rhs.month, rhs.day});
}

bool operator==(const Date &lhs, const Date &rhs)
{
    return vector<int>({lhs.year, lhs.month, lhs.day}) ==
           vector<int>({rhs.year, rhs.month, rhs.day});
}

bool operator<(const Time &lhs, const Time &rhs)
{
    return vector<int>({lhs.hours, lhs.minutes}) <
           vector<int>({rhs.hours, rhs.minutes});
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

#define SORT_BY(field)                                          \
    [](const AirlineTicket &lhs, const AirlineTicket &rhs) {    \
        return lhs.field < rhs.field;                           \
    }