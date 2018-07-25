#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class SortedStrings {
	public:
		void AddString(const string& s)
		{
			strvec.push_back(s);
			sort(strvec.begin(), strvec.end());
		}
		vector<string> GetSortedStrings()
		{
			return strvec;
		}

	private:
		vector<string> strvec;
};
