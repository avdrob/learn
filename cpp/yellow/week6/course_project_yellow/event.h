#pragma once

#include <string>
#include <ostream>

class Event {
public:
	Event(std::string name);
	std::string GetName() const;

private:
	const std::string name_;
};

bool operator<(const Event &lhs, const Event &rhs);
bool operator==(const Event &lhs, const Event &rhs);
bool operator==(const Event &lhs, const std::string &rhs);
bool operator==(const std::string &lhs, const Event &rhs);
bool operator!=(const Event &lhs, const Event &rhs);
bool operator!=(const Event &lhs, const std::string &rhs);
bool operator!=(const std::string &lhs, const Event &rhs);

std::ostream &operator<<(std::ostream &os, const Event &ev);
