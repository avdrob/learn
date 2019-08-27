#include <vector>
#include <map>
#include <string_view>

#include "stats.h"

using namespace std;

const vector<string> known_methods = {"GET", "POST", "PUT",
                                        "DELETE", "UNKNOWN"};
const vector<string> known_uris = {"/", "/order", "/product",
                                    "/basket", "/help", "unknown"};

struct Stats::StatsImpl {
    StatsImpl()
    {
        for (const string &method : known_methods) {
            method_stats[method] = 0;
        }
        for (const string &uri : known_uris) {
            uri_stats[uri] = 0;
        }
    }

    map<string_view, int> method_stats;
    map<string_view, int> uri_stats;
};

Stats::Stats() : pimpl(new StatsImpl) {}
Stats::Stats(const Stats &other) : pimpl(new StatsImpl(*other.pimpl)) {}
Stats::~Stats() = default;

const map<string_view, int> &Stats::GetMethodStats() const
{
    return pimpl->method_stats;
}

const map<string_view, int> &Stats::GetUriStats() const
{
    return pimpl->uri_stats;
}

void Stats::AddMethod(string_view method)
{
    if (pimpl->method_stats.find(method) != pimpl->method_stats.end()) {
        pimpl->method_stats[method]++;
    }
    else {
        pimpl->method_stats[known_methods.back()]++;
    }
}

void Stats::AddUri(string_view uri)
{
    if (pimpl->uri_stats.find(uri) != pimpl->uri_stats.end()) {
        pimpl->uri_stats[uri]++;
    }
    else {
        pimpl->uri_stats[known_uris.back()]++;
    }
}

string_view next_word(string_view &str)
{
    string_view res;
    size_t space;

    space = str.find_first_not_of(' ');
    str.remove_prefix(min(space, str.size()));

    space = str.find(' ');
    res = str.substr(0, space);
    str.remove_prefix(space != str.npos ? space + 1 : str.size());

    return res;
}

HttpRequest ParseRequest(string_view line)
{
    string_view method, uri, proto;
    string_view str = line;

    method = next_word(str);
    uri = next_word(str);
    proto = next_word(str);

    return {method, uri, proto};
}