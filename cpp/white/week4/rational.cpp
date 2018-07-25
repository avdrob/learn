#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class Rational {
private:
	int numerator;
	int denominator;
	int sign;
	int gcd(int a, int b);
	void Reduce();
public:
	Rational(int numerator = 0, int denominator = 1);

	int Numerator() const {return numerator;};
	int Denominator() const {return denominator;};
};

int Rational::gcd(int a, int b)
{
	while (a != 0 && b != 0)
		if (a > b)
			a = a % b;
		else
			b = b % a;

	return a + b;
}

int Gcd(int a, int b)
{
	while (a != 0 && b != 0)
		if (a > b)
			a = a % b;
		else
			b = b % a;

	return a + b;
}

void Rational::Reduce()
{
	int divisor = gcd(abs(numerator), abs(denominator));
	numerator /= divisor;
	denominator /= divisor;
}

Rational::Rational(int num, int denom):
	numerator(num), denominator(denom)
{
	if (numerator == 0) {
		denominator = 1;
		return;
	}
	Reduce();
	sign = numerator * denominator < 0 ? (-1) : 1;
	numerator = abs(numerator) * sign;
	denominator = abs(denominator);
}

/*
Rational operator + (const Rational& r1, const Rational& r2)
{
	int n1 = r1.Numerator(), n2 = r2.Numerator();
	int d1 = r1.Denominator(), d2 = r2.Denominator();

	return Rational{n1 * d2 + n2 * d1, d1 * d2};
} */

Rational operator + (const Rational& lhs, const Rational& rhs) {
	int lcm = abs(lhs.Denominator()) * abs(rhs.Denominator()) / Gcd(abs(lhs.Denominator()), abs(rhs.Denominator()));
	return Rational {lhs.Numerator() * (lcm / lhs.Denominator()) + rhs.Numerator() * (lcm / rhs.Denominator()), lcm};
}

Rational operator - (const Rational& r1, const Rational &r2)
{
	int n1 = r1.Numerator(), n2 = r2.Numerator();
	int d1 = r1.Denominator(), d2 = r2.Denominator();

	return Rational{n1 * d2 - n2 * d1, d1 * d2};
}

Rational operator * (const Rational& r1, const Rational &r2)
{
	return Rational{r1.Numerator() * r2.Numerator(),
		r1.Denominator() * r2.Denominator()};
}

Rational operator / (const Rational& r1, const Rational &r2)
{
	return Rational{r1.Numerator() * r2.Denominator(),
		r1.Denominator() * r2.Numerator()};
}

bool operator == (const Rational& r1, const Rational& r2)
{
	return r1.Numerator() == r2.Numerator() &&
		r1.Denominator() == r2.Denominator();
}

bool operator < (const Rational& r1, const Rational& r2)
{
	return (r1 - r2).Numerator() < 0;
}

ostream& operator << (ostream& out, Rational r)
{
	if (out)
		out << r.Numerator() << '/' << r.Denominator();
	return out;
}

istream& operator >> (istream& is, Rational& r) {
  int n, d;
  char c;
  is >> n >> c >> d;
  if (is && c == '/') {
    r = Rational(n, d);
  }
  return is;
}
/*
istream& operator >> (istream& inp, Rational& r)
{
	int n, d;

	if (inp.rdbuf()->in_avail() > 0) {
		inp >> n;
		inp.ignore(1);
		inp >> d;
		r = Rational{n, d};
	}

	return inp;
}
*/

int main() {

	{
		ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4") {
			cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
			return 1;
		}
	}

	{
		istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal) {
			cout << "5/7 is incorrectly read as " << r << endl;
			return 2;
		}
	}

	{
		istringstream input("5/7 10/8");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
			return 3;
		}

		input >> r1;
		input >> r2;
		correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
			return 4;
		}
	}

	cout << "OK" << endl;

	return 0;
}
