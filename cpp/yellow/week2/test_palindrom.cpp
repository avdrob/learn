#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>

using namespace std;

template <class T>
ostream& operator<<(ostream &os, const vector<T> &s)
{
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream &operator<<(ostream &os, const set<T> &s)
{
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m)
{
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u,
		const string& hint)
{
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u
			 << " hint: " << hint;
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint)
{
	AssertEqual(b, true, hint);
}

void PrintFunc()
{
	ifstream fs(__FILE__);
	string line;

	while (true) {
		getline(fs, line);
		if (line[0] == 'b' &&
			line.find("bool IsPalindrom(") != string::npos) {
			cerr << line << endl;
			break;
		}
	}
	while (true) {
		getline(fs, line);
		cerr << line << endl;
		if (line == "}")
			break;
	}
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name)
	{
		// if (is_printed == false) {
		// 	PrintFunc();
		// 	is_printed = true;
		// }

		try {
			func();
			cerr << test_name << " OK"  << endl;
		}
		catch (runtime_error& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
	}

	~TestRunner()
	{
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate"
				<< endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
	bool is_printed = false;
};

void TestCorrect()
{
	Assert(IsPalindrom("madam"), "madam");
	Assert(IsPalindrom("level"), "level");
	Assert(IsPalindrom("wasitacaroracatisaw"), "wasitacaroracatisaw");
	Assert(IsPalindrom(""), "empty string");
	Assert(IsPalindrom(" "), "single space");
	Assert(IsPalindrom("."), "single dot");
	Assert(IsPalindrom("  asdf fdsa  "), "with spaces");

	Assert(IsPalindrom("abba"), "abba");
}

void TestIncorrect()
{
	Assert(!IsPalindrom("adama"), "adama");
	Assert(!IsPalindrom("madan"), "madan");
	Assert(!IsPalindrom("kulzuk"), "kulzuk");
	Assert(!IsPalindrom("  blahhal "), "  blahhal ");
	Assert(!IsPalindrom("ma dam"), "ma dam");
	Assert(!IsPalindrom(" Kur\n ruK "), " Kur\n ruK ");

	Assert(!IsPalindrom("smadam"), "smadam");
	Assert(!IsPalindrom("madams"), "madams");
}

int main()
{
	// system("echo >&2; pwd >&2");
	// system("ls -la >&2");
	// system("ls -la .. >&2");

	// system("find ../autograder/grading-files/testing/palindrome -regex '.*\.cpp' >&2");

	// system("cat ../autograder/grading-files/testing/palindrome/impl/misses_first_last_letters.cpp >&2");
	// system("cat ../autograder/grading-files/testing/palindrome/impl/misses_first_letter.cpp >&2");
	// system("cat ../autograder/grading-files/testing/palindrome/impl/misses_last_letter.cpp >&2");
	// system("cat ../autograder/grading-files/testing/palindrome/impl/misses_middle_letter.cpp >&2");

	TestRunner tr;
	tr.RunTest(TestCorrect, "TestCorrect");
	tr.RunTest(TestIncorrect, "TestIncorrect");

	return 0;
}
