#include <iostream>

using namespace std;

extern string AskTimeServer(void);

class TimeServer {
public:
	  string GetCurrentTime();

private:
	  string LastFetchedTime = "00:00:00";
};

string TimeServer::GetCurrentTime()
{
	try {
		LastFetchedTime = AskTimeServer();
	}
	catch (system_error &) {
	}
	catch (exception &e) {
		throw;
	}

	return LastFetchedTime;
}

int main() {
	TimeServer ts;
	try {
		cout << ts.GetCurrentTime() << endl;
	}
	catch (exception& e) {
		cout << "Exception got: " << e.what() << endl;
	}
	return 0;
}
