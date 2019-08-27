#include <string>
#include <list>
#include <utility>

#include "test_runner.h"
using namespace std;

class Editor {
public:
    Editor() : cursor(data.begin()) {}

    void Left()
    {
        if (cursor != data.begin()) {
            cursor--;
        }
    }

    void Right()
    {
        if (cursor != data.end()) {
            cursor++;
        }
    }

    void Insert(char token) { data.insert(cursor, token); }

    void Cut(size_t tokens = 1)
    {
        list<char>::iterator first, last;
        tie(first, last) = copy_(tokens);
        cursor = last;
        data.erase(first, last);
    }

    void Copy(size_t tokens = 1) { copy_(tokens); }

    void Paste()
    {
        list<char> buf_copy(buffer);
        data.splice(cursor, buf_copy);
    }

    string GetText() const
    {
        return string(data.begin(), data.end());
    }

private:
    list<char> data;
    list<char> buffer;
    list<char>::iterator cursor;

    pair<list<char>::iterator, list<char>::iterator>
    copy_(size_t tokens)
    {
        auto first = cursor;
        auto last = cursor;
        for (int i = 0; i < tokens; i++) {
            if (last != data.end()) {
                last++;
            }
        }

        buffer = list<char>(first, last);
        return {first, last};
    }
};