int Factorial(int n)
{
	if (n <= 0)
		return 1;

	int res = 1;
	for (int i = 1; i <= n; i++)
		res *= i;

	return res;
}
