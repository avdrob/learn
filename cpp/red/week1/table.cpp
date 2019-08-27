#include <utility>
#include <vector>

using namespace std;

template <typename T>
class Table {
public:
    Table(size_t rows, size_t columns)
        : num_rows(rows), num_columns(columns), table(rows)
    {
        for (vector<T> &row : table) {
            row = vector<T>(columns);
        }
    }

    void Resize(size_t rows, size_t columns)
    {
        table.resize(rows);
        for (vector<T> &row : table) {
            row.resize(columns);
        }
        num_rows = rows;
        num_columns = columns;
    }

    pair<size_t, size_t> Size() const
    {
        return make_pair(num_rows, num_columns);
    }

    vector<T> &operator[](size_t i) { return table[i]; }
    const vector<T> &operator[](size_t i) const { return table[i]; }

private:
    size_t num_rows, num_columns;
    vector<vector<T>> table;
};