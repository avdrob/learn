#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <iomanip>

using namespace std;

const double pi = 3.14;

class Figure {
public:
	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;

private:
};

class Triangle : public Figure {
public:
	Triangle(double a, double b, double c) : a_(a),  b_(b), c_(c) {}
	virtual string Name() const override { return name_; }
	virtual double Perimeter() const override { return a_ + b_ + c_; }
	virtual double Area() const override
	{
		double p = Perimeter() / 2;
		return sqrt(p * (p - a_) * (p - b_) * (p - c_));
	}


private:
	const string name_ = "TRIANGLE";
	const double a_, b_, c_;
};

class Rect : public Figure {
public:
	Rect(double w, double h) : w_(w), h_(h) {}
	virtual string Name() const override { return name_; }
	virtual double Perimeter() const override { return 2 * (w_ + h_); }
	virtual double Area() const override { return w_ * h_; }

private:
	const string name_ = "RECT";
	const double w_, h_;
};

class Circle : public Figure {
public:
	Circle(double r) : r_(r) {}
	virtual string Name() const { return name_; }
	virtual double Perimeter() const override { return 2 * pi * r_; }
	virtual double Area() const override { return pi * r_ * r_; }

private:
	const string name_ = "CIRCLE";
	const double r_;
};

shared_ptr<Figure> CreateFigure(istream &is)
{
	string name;

	is >> name;
	if (name == "TRIANGLE") {
		double a, b, c;
		is >> a >> b >> c;
		return make_shared<Triangle>(a, b, c);
	}
	else if (name == "RECT") {
		double w, h;
		is >> w >> h;
		return make_shared<Rect>(w, h);
	}
	else {
		double r;
		is >> r;
		return make_shared<Circle>(r);
	}
}
