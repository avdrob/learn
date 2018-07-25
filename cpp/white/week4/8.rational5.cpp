/*
Наконец, вам нужно реализовать возможность использовать объекты класса Rational в качестве элементов контейнера set и ключей в контейнере map. Пример:
set<Rational> rationals;
rationals.insert(Rational(1, 2));
rationals.insert(Rational(1, 3));

map<Rational, string> name;
name[Rational(1, 2)] = "одна вторая";
*/

#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

int Gcd(int a, int b) {
	while (a != 0 && b != 0) {
	    	if (a > b) {
			a %= b;
		} else {
			b %= a;
		}
	}
	return a + b;
}

class Rational {
public:
    Rational() {
	p = 0;
	q = 1;
    }

    Rational(int numerator, int denominator) {
	int gcd = Gcd(abs(numerator), abs(denominator));
        p = numerator / gcd;
	q = denominator / gcd;
	if (q < 0) {
		p *= -1;
		q *= -1;
	}
	if (p == 0) {
		q = 1;
	}
    }

    int Numerator() const {
        return p;
    }

    int Denominator() const {
        return q;
    }

private:
	int p;
	int q;
};

bool operator == (const Rational& lhs, const Rational rhs) {
	if (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator()) {
		return true;
	} 
	return false;
}

// Реализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а

bool operator < (const Rational& lhs, const Rational rhs) {
	int lcm = abs(lhs.Denominator()) * abs(rhs.Denominator()) / Gcd(abs(lhs.Denominator()), abs(rhs.Denominator()));
	if (lhs.Numerator() * (lcm / lhs.Denominator()) < rhs.Numerator() * (lcm / rhs.Denominator())) {
		return true;
	} 
	return false;
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}

/*Решение:

#include <iostream>

using namespace std;

// один из способов вычисления наибольшего общего делителя (НОД) — рекурсивный:
// вместо цикла функция будет вызывать себя же, но с другими аргументами
int GreatestCommonDivisor(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return GreatestCommonDivisor(b, a % b);
  }
}

class Rational {
public:
  Rational() {  // дробь по умолчанию — 0/1
    numerator = 0;
    denominator = 1;
  }
  Rational(int new_numerator, int new_denominator) {
    const int gcd = GreatestCommonDivisor(new_numerator, new_denominator);
    // сократим дробь, разделив числитель и знаменатель на их НОД
    numerator = new_numerator / gcd;
    denominator = new_denominator / gcd;
    // знаменатель должен быть положительным
    if (denominator < 0) {
      denominator = -denominator;
      numerator = -numerator;
    }
  }

  int Numerator() const {
    return numerator;
  }

  int Denominator() const {
    return denominator;
  }

private:
  int numerator;
  int denominator;
};

// поскольку дроби сокращены, достаточно сравнить числители и знаменатели
bool operator == (const Rational& lhs, const Rational& rhs) {
  return lhs.Numerator() == rhs.Numerator() &&
      lhs.Denominator() == rhs.Denominator();
}

// используем обычную формулу сложения дробей, основанную на приведении слагаемых к общему знаменателю
Rational operator + (const Rational& lhs, const Rational& rhs) {
  return {
      lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
      lhs.Denominator() * rhs.Denominator()
  };
}

// вычитание реализуем аналогично сложению
// дублирования кода можно было избежать, определив для класса Rational операцию унарного минуса: тогда разность lhs и rhs можно было бы вычислить           как lhs + (-rhs)
Rational operator - (const Rational& lhs, const Rational& rhs) {
  return {
      lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
      lhs.Denominator() * rhs.Denominator()
  };
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
  return {
      lhs.Numerator() * rhs.Numerator(),
      lhs.Denominator() * rhs.Denominator()
  };
}

// деление равносильно умножению на обратную («перевёрнутую») дробь
Rational operator / (const Rational& lhs, const Rational& rhs) {
  return lhs * Rational(rhs.Denominator(), rhs.Numerator());
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

ostream& operator << (ostream& os, const Rational& r) {
  return os << r.Numerator() << '/' << r.Denominator();
}

// чтобы сравнить lhs с rhs, сравним их разность с нулём, что равносильно сравнению с нулём числителя
bool operator < (const Rational& lhs, const Rational& rhs) {
  return (lhs - rhs).Numerator() < 0;
}

*/
