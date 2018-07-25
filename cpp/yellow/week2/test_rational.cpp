#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

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

void TestConstruct()
{
	Rational r;
	AssertEqual(r.Numerator(), 0, "Default numerator");
	AssertEqual(r.Denominator(), 1, "Default denominator");

	Rational r1(4, 16);
	AssertEqual(r1.Numerator(), 1, "Reduced numerator");
	AssertEqual(r1.Denominator(), 4, "Reduced denominator");

	Rational r2(-10, 100);
	AssertEqual(r2.Numerator(), -1, "Reduced numerator");
	AssertEqual(r2.Denominator(), 10, "Reduced denominator");

	Rational r3(10, -2);
	AssertEqual(r3.Numerator(), -5, "Reduced numerator");
	AssertEqual(r3.Denominator(), 1, "Reduced denominator");

	Rational r4(-2, -3);
	AssertEqual(r4.Numerator(), 2, "Negative numerator");
	AssertEqual(r4.Denominator(), 3, "Negative denominator");

	Rational r5(0, -200);
	AssertEqual(r5.Numerator(), 0, "Zero numerator");
	AssertEqual(r5.Denominator(), 1, "Zero numerator");
}

int main()
{
	TestRunner tr;
	tr.RunTest(TestConstruct,  "TestConstruct");

	return 0;
}
