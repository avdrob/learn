#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    int elem_num = range_end - range_begin;

    if (range_end - range_begin < 2) {
        return;
    }

    vector<typename RandomIt::value_type> vec(make_move_iterator(range_begin),
                                              make_move_iterator(range_end));
    MergeSort(vec.begin(), vec.begin() + elem_num / 3);
    MergeSort(vec.begin() + elem_num / 3, vec.begin() + 2 * elem_num / 3);
    MergeSort(vec.begin() + 2 * elem_num / 3, vec.begin() + elem_num);

    vector<typename RandomIt::value_type> temp;
    merge(make_move_iterator(vec.begin()),
          make_move_iterator(vec.begin() + elem_num / 3),
          make_move_iterator(vec.begin() + elem_num / 3),
          make_move_iterator(vec.begin() + 2 * elem_num / 3),
          back_inserter(temp)
    );
    merge(make_move_iterator(temp.begin()),
          make_move_iterator(temp.end()),
          make_move_iterator(vec.begin() + 2 * elem_num / 3),
          make_move_iterator(vec.end()),
          range_begin
    );
}

// void TestIntVector() {
//   vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
//   MergeSort(begin(numbers), end(numbers));
//   ASSERT(is_sorted(begin(numbers), end(numbers)));
// }
// 
// template <typename InputIt>
// void output(InputIt first, InputIt last)
// {
//     for (; first != last; ++first) {
//         cout << *first << " ";
//     }
//     cout << endl;
// }
// 
// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestIntVector);
// 
//   vector<int> numbers = {9, 6, 4, 7, 6, 4, 4, 0, 1, 5,};
//   output(begin(numbers), end(numbers));
//   MergeSort(begin(numbers), end(numbers));
//   output(begin(numbers), end(numbers));
// 
//   return 0;
// }
