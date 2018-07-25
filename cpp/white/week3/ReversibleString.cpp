#include <string>
#include <utility>
using namespace std;

class ReversibleString {
	public:
		ReversibleString() {};
		ReversibleString(const string& s) {rstr = s;};
		void Reverse() {
			for (int i = 0; i < rstr.size()/2; i++)
				swap(rstr[i], rstr[rstr.size()-i-1]);
		}
		string ToString() const {return rstr;};

	private:
		string rstr;
};
