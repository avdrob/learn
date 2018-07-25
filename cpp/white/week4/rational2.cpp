#include <cmath>
#include <iostream>
#include <exception>

using namespace std;

class Rational {
private:
	int numerator;
	int denominator;
	int sign;
	int Gcd(int a, int b);
public:
	Rational(int numerator = 0, int denominator = 1);

	int Numerator() const {return numerator;};
	int Denominator() const {return denominator;};
};

int Rational::Gcd(int a, int b)
{
        while (a != 0 && b != 0)
                if (a > b)
                        a = a % b;
                else
                        b = b % a;

        return a + b;
}

Rational::Rational(int num, int denom):
        numerator(num), denominator(denom)
{
	if (denominator == 0)
		throw invalid_argument("Invalid argument");

	int divisor = Gcd(abs(numerator), abs(denominator));
	numerator /= divisor;
	denominator /= divisor;

        sign = numerator * denominator < 0 ? (-1) : 1;
        numerator = abs(numerator) * sign;
        denominator = abs(denominator);
}

Rational operator+(const Rational &lhs, const Rational &rhs)
{
	return Rational{lhs.Numerator() * rhs.Denominator() +
			rhs.Numerator() * lhs.Denominator(),
			lhs.Denominator() * rhs.Denominator()};
}

Rational operator-(const Rational &lhs, const Rational &rhs)
{
	return Rational{lhs.Numerator() * rhs.Denominator() -
			rhs.Numerator() * lhs.Denominator(),
			lhs.Denominator() * rhs.Denominator()};
}

Rational operator*(const Rational &lhs, const Rational &rhs)
{
	return Rational{lhs.Numerator() * rhs.Numerator(),
			lhs.Denominator() * rhs.Denominator()};
}

Rational operator/(const Rational &lhs, const Rational &rhs)
{
	if (rhs.Numerator() == 0)
		throw domain_error("Division by zero");

	return Rational(lhs.Numerator() * rhs.Denominator(),
			lhs.Denominator() * rhs.Numerator());
}

istream &operator>>(istream &is, Rational &r)
{
	int n, d;
	char c;

	is >> n >> c >> d;
	if (is && c == '/')
		r = Rational(n, d);

	return is;
}

ostream &operator<<(ostream &os, const Rational &r)
{
	if (os)
		os << r.Numerator() << '/' << r.Denominator();

	return os;
}

int main(int argc, char *argv[])
{
	Rational r1, r2;
	char op;

	try {
		cin >> r1 >> ws >> op >> ws >> r2;
	} catch (invalid_argument &inv) {
		cout << inv.what() << endl;
		return 1;
	}


	switch (op) {
	case '+':
		cout << r1 + r2 << endl;
		break;
	case '-':
		cout << r1 - r2 << endl;
		break;
	case '*':
		cout << r1 * r2 << endl;
		break;
	case '/':
		try {
			cout << r1 / r2 << endl;
			break;
		} catch (domain_error &dom) {
			cout << dom.what() << endl;
			return 2;
		}
	}

	return 0;
}

