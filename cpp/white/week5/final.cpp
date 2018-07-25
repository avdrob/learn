#include <iostream>
#include <iomanip>
#include <exception>
#include <map>
#include <set>
#include <string>
#include <sstream>

using namespace std;

class Date {
public:
	Date(string datestr = "1-1-1");
	friend bool operator<(const Date &lhs, const Date &rhs);

	int year;
	int month;
	int day;

private:
	string date;
};

Date::Date(string datestr)
{
	istringstream iss(datestr);

	iss >> year;
	if (iss.peek() != '-')
		throw invalid_argument("Wrong date format: " + datestr);
	iss.get();

	iss >> month;
	if (!iss || iss.peek() != '-')
		throw invalid_argument("Wrong date format: " + datestr);
	iss.get();

	iss >> day;
	if (!iss || !iss.eof())
		throw invalid_argument("Wrong date format: " + datestr);

	if (month < 1 || month > 12)
		throw invalid_argument("Month value is invalid: " +
					to_string(month));
	if (day < 1 || day > 31)
		throw invalid_argument("Day value is invalid: " +
					to_string(day));

	date = datestr;
}

bool operator<(const Date& lhs, const Date& rhs)
{
	return lhs.date < rhs.date;
}

class Cmd {
public:
	Cmd(string str = "");
	string cmd;

private:
	static const set<string> valid_cmds;
};

/* Initialize static const set to be used by all instances of Cmd class */
static const string tmp[] = {"Add", "Del", "Find", "Print"};
const set<string> Cmd::valid_cmds = set<string>(tmp, tmp +
						sizeof(tmp)/sizeof(tmp[0]));

Cmd::Cmd(string str)
{
	if (str != "" && valid_cmds.count(str) == 0)
		throw invalid_argument("Unknown command: " + str);
	cmd = str;
}

class Database {
public:
	void AddEvent(const Date& date, const string& event);
	void DeleteEvent(const Date& date, const string& event);
	void  DeleteDate(const Date& date);

	void Find(const Date& date) const;
	void Print() const;

private:
	map<Date, set<string>> data;
};

void Database::AddEvent(const Date &date, const string &event)
{
	data[date].insert(event);
}

void Database::DeleteEvent(const Date &date, const string &event)
{
	if (data[date].count(event)) {
		data[date].erase(event);
		cout << "Deleted successfully" << endl;
	}
	else
		cout << "Event not found" << endl;
}

void Database::DeleteDate(const Date &date)
{
	int n = data[date].size();

	if (n > 0)
		data.erase(date);
	cout << "Deleted " << n << " events" << endl;
}

void Database::Find(const Date &date) const
{
	if (data.find(date) != data.end())
		for (const string &ev : data.at(date))
			cout << ev << endl;
}

void Database::Print() const
{
	for (auto const &rec : data) {
		Date date = rec.first;
		set<string> ev_set = rec.second;
		for (auto const &ev : ev_set) {
			cout << setfill('0');
			cout << setw(4) << date.year << '-'
				<< setw(2) << date.month << '-'
				<< setw(2) << date.day;
			cout << ' ' << ev << endl;
		}
	}
}

int main() {
	Database db;
	string line;

	while (cin >> ws && getline(cin, line)) {
		string cmdstr, datestr, event;
		Cmd cmd;
		Date date;
		istringstream iss(line);

		iss >> cmdstr >> datestr >> event;
		try {
			cmd = Cmd(cmdstr);
			if (cmdstr != "Print")
				date = Date(datestr);
		}
		catch (invalid_argument &e) {
			cout << e.what() << endl;
			return 0;
		}

		if (cmdstr == "Add")
			db.AddEvent(date, event);
		else if (cmdstr == "Del")
			if (event != "")
				db.DeleteEvent(date, event);
			else
				db.DeleteDate(date);
		else if (cmdstr == "Find")
			db.Find(date);
		else
			db.Print();
	}

  return 0;
}
