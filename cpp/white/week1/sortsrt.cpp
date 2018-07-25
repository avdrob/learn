#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	string s1, s2, s3, mins;


	cin >> s1 >> s2 >> s3;
	if (s1 < s2) {
		if (s1 < s3)
			mins = s1;
		else
			mins = s3;
	} else
		if (s2 < s3)
			mins = s2;
		else
			mins = s3;

	cout << mins << endl;

	return 0;
}
