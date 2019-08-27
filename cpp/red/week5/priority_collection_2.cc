#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
    using Id = int; /* тип, используемый для идентификаторов */

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object)
    {
        Id id = obj_prio.size();
        prio_id.insert({0, id});
        obj_prio.push_back({move(object), 0});
        return id;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin)
    {
        for (; range_begin != range_end; ++range_begin) {
            *ids_begin = Add(move(*range_begin));
            ++ids_begin;
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const
    {
        return id < obj_prio.size() && obj_prio[id].second >= 0;
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const { return obj_prio[id].first; }

    // Увеличить приоритет объекта на 1
    void Promote(Id id)
    {
        prio_id.erase({obj_prio[id].second, id});
        prio_id.insert({++obj_prio[id].second, id});
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const
    {
        auto it = prev(prio_id.end());
        return {obj_prio[it->second].first, it->first};
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax()
    {
        auto it = prev(prio_id.end());
        auto res = pair<T, int>(move(obj_prio[it->second].first), it->first);
        obj_prio[it->second].second = -1;
        prio_id.erase(it);
        return res;
    }

private:
    // Приватные поля и методы
    set<pair<int, Id>> prio_id;
    vector<pair<T, int>> obj_prio;
};

// class StringNonCopyable : public string {
// public:
//   using string::string;  // Позволяет использовать конструкторы строки
//   StringNonCopyable(const StringNonCopyable&) = delete;
//   StringNonCopyable(StringNonCopyable&&) = default;
//   StringNonCopyable& operator=(const StringNonCopyable&) = delete;
//   StringNonCopyable& operator=(StringNonCopyable&&) = default;
// };
// 
// void TestNoCopy() {
//   PriorityCollection<StringNonCopyable> strings;
//   const auto white_id = strings.Add("white");
//   const auto yellow_id = strings.Add("yellow");
//   const auto red_id = strings.Add("red");
// 
//   strings.Promote(yellow_id);
//   for (int i = 0; i < 2; ++i) {
//     strings.Promote(red_id);
//   }
//   strings.Promote(yellow_id);
//   {
//     const auto item = strings.PopMax();
//     ASSERT_EQUAL(item.first, "red");
//     ASSERT_EQUAL(item.second, 2);
//   }
//   {
//     const auto item = strings.PopMax();
//     ASSERT_EQUAL(item.first, "yellow");
//     ASSERT_EQUAL(item.second, 2);
//   }
//   {
//     const auto item = strings.PopMax();
//     ASSERT_EQUAL(item.first, "white");
//     ASSERT_EQUAL(item.second, 0);
//   }
// }
// 
// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestNoCopy);
//   return 0;
// }
