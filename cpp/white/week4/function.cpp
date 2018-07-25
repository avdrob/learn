#include <vector>
#include <algorithm>
using namespace std;

class FunctionPart {
public:
	FunctionPart(char new_op, double new_val)
	{
		operation = new_op;
		value = new_val;
	}
	double Apply(double src_val) const
	{
		if (operation == '+')
			return src_val + value;
		else if (operation == '-')
			return src_val - value;
		else if (operation == '*')
			return src_val * value;
		else
			return src_val / value;
	}
	void Invert()
	{
		if (operation == '+')
			operation = '-';
		else if (operation == '-')
			operation = '+';
		else if (operation == '*')
			operation = '/';
		else
			operation = '*';
	}

private:
	char operation;
	double value;
};

class Function {
public:
	void AddPart(char operation, double value)
	{
		parts.push_back({operation, value});
	}
	double Apply(double value) const 
	{
		for (const FunctionPart& part : parts)
			value = part.Apply(value);
		return value;
	}
	void Invert()
	{
		for (FunctionPart& part : parts)
			part.Invert();
		reverse(begin(parts), end(parts));
	}

private:
	vector<FunctionPart> parts;
};
