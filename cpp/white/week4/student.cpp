#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Student {
	string name;
	string surname;
	long long int bday;
	long long int bmonth;
	long long int byear;
};

void prerr()
{
	cout << "bad request" << endl;
}
	
int main()
{
	long long int N, M;

	cin >> N;
	vector<Student> stlist(N);
	for (long long int i = 1; i <= N; i++) {
		cin >> stlist[i-1].name >> stlist[i-1].surname >> stlist[i-1].bday >>
			stlist[i-1].bmonth >> stlist[i-1].byear;
	}

	cin >> M;
	for (long long int i = 1; i <= M; i++) {
		string request;
		long long int K;

		cin >> request >> K;
		if (request != "date" && request != "name" ||
				K <= 0 || K > 10000)
			prerr();
		else if (request == "name") {
			K--;
			cout << stlist[K].name << ' ' <<
				stlist[K].surname << endl;
		}
		else if (request == "date") {
			K--;
			cout << stlist[K].bday << '.' << stlist[K].bmonth <<
				'.' << stlist[K].byear << endl;
		}
		else
			prerr();
	}

	return 0;
}
