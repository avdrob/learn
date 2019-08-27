#include "test_runner.h"

#include <cstdint>
#include <vector>

using namespace std;

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
  vector<typename RandomIt::value_type> pool;
  vector<bool> alive(last - first, true);
  size_t cur_pos = 0;
  size_t alive_cnt = last - first;

  move(first, last, back_inserter(pool));
  // for (auto it = first; it != last; it++) {
  //     pool.push_back(move(*it));
  // }

  for (auto it = first; it != last; it++) {
    *(first++) = move(pool[cur_pos]);
    alive[cur_pos] = false;
    alive_cnt--;

    if (alive_cnt == 0) {
        break;
    }

    for (uint32_t i = 0; i < step_size;) {
        cur_pos++;
        if (cur_pos == pool.size()) {
            cur_pos = 0;
        }
        if (alive[cur_pos]) {
            i++;
        }
    }
  }
}
