#include "test_runner.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>

using namespace std;

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    // Реализуйте эту функцию
    size_t thr_num = min(matrix.size(), static_cast<size_t>(4));
    int rows = matrix.size() / thr_num;
    auto first = matrix.begin();
    auto last = first + rows + matrix.size() % thr_num;
    vector<future<int64_t>> futures;

    for (size_t i = 0; i < thr_num; ++i) {
        // auto last = rows <= matrix.end() - first ? first + rows : matrix.end();
        futures.push_back(async([first, last] () {
                            int64_t res = 0;
                            for (auto it = first; it != last; ++it) {
                                res += accumulate(it->begin(), it->end(), 0);
                            }
                            return res;
                          }));
        first = last;
        last += rows;
    }

    int64_t res = 0;
    for (auto& f : futures) {
        res += f.get();
    }
    return res;
}

// void TestCalculateMatrixSum() {
//   const vector<vector<int>> matrix = {
//     {1, 2, 3, 4},
//     {5, 6, 7, 8},
//     {9, 10, 11, 12},
//     {13, 14, 15, 16},
//     {1, 2, 3, 4}
//   };
//   ASSERT_EQUAL(CalculateMatrixSum(matrix), 146);
// }
// 
// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestCalculateMatrixSum);
// }
