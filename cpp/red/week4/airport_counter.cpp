#include <cstdint>
#include <array>
#include <utility>

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

#include "test_runner.h"
#include "profile.h"

using namespace std;

template <typename Ap>
class AirportCounter {
private:
    static constexpr uint32_t N = static_cast<uint32_t>(Ap::Last_);

public:
    // конструктор по умолчанию: список элементов пока пуст
    AirportCounter() { airports_cnt.fill(0); }

    // конструктор от диапазона элементов типа TAirport
    template <typename It>
    AirportCounter(It begin, It end)
        : AirportCounter()
    {
        for (It it = begin; it != end; ++it) {
            airports_cnt[static_cast<size_t>(*it)]++;
        }
    }

    // получить количество элементов, равных данному
    int Get(Ap ap) const { return airports_cnt[static_cast<size_t>(ap)]; }

    // добавить данный элемент
    void Insert(Ap ap) { airports_cnt[static_cast<size_t>(ap)]++; }

    // удалить одно вхождение данного элемента
    void EraseOne(Ap ap) { airports_cnt[static_cast<size_t>(ap)]--; }

    // удалить все вхождения данного элемента
    void EraseAll(Ap ap) { airports_cnt[static_cast<size_t>(ap)] = 0; }

    using Item = pair<Ap, size_t>;

    // получить некоторый объект, по которому можно проитерироваться,
    // получив набор объектов типа Item - пар (аэропорт, количество),
    // упорядоченных по аэропорту
    const array<Item, N> GetItems() const
    {
        array<Item, N> airports_pair;
        for (size_t i = 0; i < N; i++) {
            airports_pair[i] = {static_cast<Ap>(i), airports_cnt[i]};
        }
        return airports_pair;
    }

private:
    array<size_t, N> airports_cnt;
};