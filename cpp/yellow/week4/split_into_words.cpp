#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

vector<string> SplitIntoWords(const string& s)
{
	string::const_iterator cur_space, prev_space;
	vector<string> res = {};

	cur_space = s.begin();
	prev_space = s.begin();
	while (cur_space != s.end()) {
		cur_space = find(prev_space, s.end(), ' ');
		res.push_back({prev_space, cur_space});
		prev_space = cur_space + 1;
	}

	return res;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;

  return 0;
}
