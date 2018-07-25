#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <csignal>

using namespace std;

string ParseEvent(istream &is)
{
	string s;

	is >> ws;
	getline(is, s);
	return s;
}

void TestAll();

int main() {
  TestAll();

  Database db;

  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      }
      catch (string &s) {
          cout << s << endl;
      }
      catch (runtime_error &e) {
	      cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}

void TestParseEvent()
{
	{
		istringstream is("event");
		AssertEqual(ParseEvent(is), "event",
					"Parse event without leading spaces");
	}
	{
		istringstream is("   sport event ");
		AssertEqual(ParseEvent(is), "sport event ",
					"Parse event with leading spaces");
	}
	{
		istringstream is("  first event  \n  second event");
		vector<string> events;
		events.push_back(ParseEvent(is));
		events.push_back(ParseEvent(is));
		AssertEqual(events, vector<string>{"first event  ",
				"second event"}, "Parse multiple events");
	}
}

void TestParseDate()
{
	{
		istringstream is("2017-07-08 ");
		Date d = ParseDate(is);
		AssertEqual(d, Date(2017, 7, 8), "2017-07-08 ");
	}

	{
		istringstream is("2017-7-8 ");
		Date d = ParseDate(is);
		AssertEqual(d, Date(2017, 7, 8), "2017-7-8 ");
	}

	{
		istringstream is("      0-2-31 ");
		Date d = ParseDate(is);
		AssertEqual(d, Date(0, 2, 31), "        0-2-31 ");
	}

	{
		istringstream is(" 01-03-08     ");
		Date d = ParseDate(is);
		AssertEqual(d, Date(1, 3, 8), " 01-03-08        ");
	}
}

void TestParseCondition() {
  {
    istringstream is("date != 2017-11-18");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 1");
    Assert(!root->Evaluate({2017, 11, 18}, ""), "Parse condition 2");
  }
  {
    istringstream is(R"(event == "sport event")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 3");
    Assert(!root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 4");
  }
  {
    istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 5");
    Assert(root->Evaluate({2017, 3, 1}, ""), "Parse condition 6");
    Assert(root->Evaluate({2017, 6, 30}, ""), "Parse condition 7");
    Assert(!root->Evaluate({2017, 7, 1}, ""), "Parse condition 8");
    Assert(!root->Evaluate({2016, 12, 31}, ""), "Parse condition 9");
  }
  {
    istringstream is(R"(event != "sport event" AND event != "Wednesday")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 10");
    Assert(!root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 11");
    Assert(!root->Evaluate({2017, 1, 1}, "Wednesday"), "Parse condition 12");
  }
  {
    istringstream is(R"(event == "holiday AND date == 2017-11-18")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(!root->Evaluate({2017, 11, 18}, "holiday"), "Parse condition 13");
    Assert(!root->Evaluate({2017, 11, 18}, "work day"), "Parse condition 14");
    Assert(root->Evaluate({1, 1, 1}, "holiday AND date == 2017-11-18"), "Parse condition 15");
  }
  {
    istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 16");
    Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 17");
  }
  {
    istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(!root->Evaluate({2016, 1, 1}, "holiday"), "Parse condition 18");
    Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 19");
    Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 20");
    Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 21");
  }
  {
    istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2016, 1, 1}, "event"), "Parse condition 22");
    Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 23");
    Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 24");
    Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 25");
  }
  {
    istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 26");
    Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 27");
  }
  {
    istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({1, 1, 1}, "2017-01-01"), "Parse condition 28");
    Assert(!root->Evaluate({2016, 1, 1}, "event"), "Parse condition 29");
    Assert(root->Evaluate({2016, 1, 2}, "event"), "Parse condition 30");
  }
}

void TestAll()
{
	TestRunner tr;
	tr.RunTest(TestParseEvent, "TestParseEvent");
	tr.RunTest(TestParseCondition, "TestParseCondition");
	tr.RunTest(TestParseDate, "TestParseDate");
}
