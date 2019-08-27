#include <numeric>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>

using namespace std;

template <typename It>
class Paginator {
public:
    Paginator(It begin, It end, size_t page_size)
    {
        if (begin == end) {
            return;
        }

        size_t cnt = 0;
        It prev = begin;
        for (It it = next(begin); it != end; ++it) {
            cnt++;
            if (cnt == page_size) {
                pages.push_back(Page{prev, it, cnt});
                cnt = 0;
                prev = it;
            }
        }
        cnt++;
        pages.push_back(Page{prev, end, cnt});
    }

    auto begin() const { return pages.begin(); }
    auto end() const { return pages.end(); }
    size_t size() const { return pages.size(); }

private:
    class Page {
    public:
        Page(It first_, It last_, size_t size_)
            : first(first_), last(last_), page_size(size_)
        {}

        It begin() const { return first; }
        It end() const { return last; }
        size_t size() const  { return page_size; }
    private:
        It first, last;
        size_t page_size;
    };

private:
    vector<Page> pages;
    size_t page_size;
};

template <typename C>
auto Paginate(C &c, size_t page_size)
{
    return Paginator{c.begin(), c.end(), page_size};
}