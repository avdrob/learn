#include <string>
#include <ostream>

#include "event.h"

using namespace std;

Event::Event(string name) : name_(name) {}

string Event::GetName() const
{
	return name_;
}

bool operator<(const Event &lhs, const Event &rhs)
{
	return lhs.GetName() < rhs.GetName();
}

bool operator==(const Event &lhs, const Event &rhs)
{
	return lhs.GetName() == rhs.GetName();
}

bool operator==(const Event &lhs, const string &rhs)
{
	return lhs.GetName() == rhs;
}

bool operator==(const string &lhs, const Event &rhs)
{
	return lhs == rhs.GetName();
}

bool operator!=(const Event &lhs, const Event &rhs)
{
	return lhs.GetName() == rhs.GetName();
}

bool operator!=(const Event &lhs, const string &rhs)
{
	return lhs.GetName() != rhs;
}

bool operator!=(const string &lhs, const Event &rhs)
{
	return lhs != rhs.GetName();
}

ostream &operator<<(ostream &os, const Event &ev)
{
	os << ev.GetName();
	return os;
}
