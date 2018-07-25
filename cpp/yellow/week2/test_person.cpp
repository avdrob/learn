#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

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

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name)
	{
		try {
		func();
		cerr << test_name << " OK" << endl;
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
};

void TestIncognito()
{
	Person p;
	AssertEqual(p.GetFullName(2018), "Incognito", "No changes");
	p.ChangeFirstName(2015, "Michael");
	p.ChangeLastName(2014, "Trump");
	AssertEqual(p.GetFullName(2013), "Incognito", "Late changes");
}

void TestUnknown()
{
	Person p;

	p.ChangeFirstName(2015, "Michael");
	p.ChangeFirstName(2014, "David");
	AssertEqual(p.GetFullName(2014), "David with unknown last name",
						"Unknown last");

	p.ChangeLastName(2010, "Jonson");
	p.ChangeLastName(2009, "Kim");
	AssertEqual(p.GetFullName(2009), "Kim with unknown first name",
						"Unknown first");
}

void TestFull()
{
	Person p;
	AssertEqual(p.GetFullName(2018), "Incognito", "He's just born");
	p.ChangeLastName(1995, "Zakaryan");
	p.ChangeFirstName(1995, "Michael");
	AssertEqual(p.GetFullName(1996), "Michael Zakaryan", "Already got name");
	p.ChangeFirstName(1996, "Andrey");
	AssertEqual(p.GetFullName(1997), "Andrey Zakaryan", "Changed first name");
	p.ChangeLastName(1997, "Drobyshev");
	AssertEqual(p.GetFullName(2000), "Andrey Drobyshev", "Changed last name too");
}

void TestAll()
{
	TestRunner tr;
	tr.RunTest(TestIncognito, "TestIncognito");
	tr.RunTest(TestUnknown, "TestUnknown");
	tr.RunTest(TestFull, "TestFull");
}

int main()
{
	TestAll();
	return 0;
}
