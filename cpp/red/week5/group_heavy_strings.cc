// #include "test_runner.h"
// 
// #include <algorithm>
// #include <string>

#include <vector>
#include <set>
#include <map>
#include <utility>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

// template <typename String>
// inline bool char_in_set(const Char<String> &c, const set<Char<String>> &s)
// {
//     return s.find(c) != s.end();
// }

// template <typename String>
// void make_set_from_word(const String &word, set<Char<String>> &s)
// {
//     s.clear();
//     for (const Char<String> &c : word) {
//         // The only place to copy Char<String>
//         s.insert(c);
//     }
// }
// 
// template <typename Char>
// bool word_in_set(const set<Char> &word, const set<Char> &s)
// {
//     if (word.size() != s.size()) {
//         return false;
//     }
// 
//     for (const Char &c : word) {
//         if (s.find(c) == s.end()) {
//             return false;
//         }
//     }
//     return true;
// }

//// This solution is a bad one: we use linear lookup of charsets instead of
//// logarithmic one (as we store charsets in vector instead of map).
// template <typename String>
// vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
//   // Напишите реализацию функции,
//   // использовав не более 1 копирования каждого символа
// 
//     vector<Group<String>> groups;
//     vector<set<Char<String>>> charsets;
// 
//     for (String &word : strings) {
//         bool found = false;
// 
//         set<Char<String>> ws;
//         make_set_from_word(word, ws);
// 
//         for (int i = 0; i < charsets.size(); i++) {
//             if (word_in_set(ws, charsets[i])) {
//                 found = true;
//                 groups[i].push_back(move(word));
//             }
//         }
// 
//         if (!found) {
//             charsets.push_back(move(ws));
//             groups.push_back(Group<String>());
//             groups.back().push_back(move(word));
//         }
//     }
// 
//     return groups;
// }

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
    vector<Group<String>> res;
    map<set<Char<String>>, Group<String>> data;

    for (String &word : strings) {
        set<Char<String>> charset;
        for (Char<String> &c : word) {
            charset.insert(c);
        }
        data[move(charset)].push_back(move(word));
    }

    for (auto &it : data) {
        res.push_back(move(it.second));
    }

    return res;
}
