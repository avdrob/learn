#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <sstream>
#include <iterator>
#include <utility>
#include <algorithm>
#include <future>

using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other)
  {
      for (auto& it : other.word_frequences) {
          word_frequences[it.first] += it.second;
      }
  }
};

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    // Реализуйте эту функцию
    string s;
    vector<string> all_words;
    while (input >> s) {
        all_words.push_back(move(s));
    }

    vector<future<Stats>> futures;
    size_t thr_num = min(all_words.size(), static_cast<size_t>(4));
    size_t lines = all_words.size() / thr_num;
    auto first = all_words.begin();
    auto last = first + lines + all_words.size() % thr_num;

    for (size_t i = 0; i < thr_num; ++i) {
        futures.push_back(async([first, last, &key_words] () {
                            Stats res;
                            for (auto it = first; it != last; ++it) {
                                if (key_words.find(*it) != key_words.end()) {
                                    res.word_frequences[move(*it)] += 1;
                                }
                            }
                            return res;
                        }));
        first = last;
        last += lines;
    }

    Stats res;
    for (auto& f : futures) {
        res += f.get();
    }
    return res;
}

// void TestBasic() {
//   const set<string> key_words = {"yangle", "rocks", "sucks", "all"};
// 
//   stringstream ss;
//   ss << "this new yangle service really rocks\n";
//   ss << "It sucks when yangle isn't available\n";
//   ss << "10 reasons why yangle is the best IT company\n";
//   ss << "yangle rocks others suck\n";
//   ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
// 
//   Stats stats;
//   LOG_DURATION("ExploreKeyWords") {
//    stats = ExploreKeyWords(key_words, ss);
//   }
//   // const auto stats = ExploreKeyWords(key_words, ss);
//   const map<string, int> expected = {
//     {"yangle", 6},
//     {"rocks", 2},
//     {"sucks", 1}
//   };
//   ASSERT_EQUAL(stats.word_frequences, expected);
// }
// 
// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestBasic);
// }
