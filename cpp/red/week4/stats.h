#ifndef STATS_H_
#define STATS_H_

#include <string_view>
#include <map>
#include <memory>

#include "http_request.h"

using namespace std;

class Stats {
public:
    Stats();
    Stats(const Stats&);
    ~Stats();
    void AddMethod(string_view method);
    void AddUri(string_view uri);
    const map<string_view, int> &GetMethodStats() const;
    const map<string_view, int> &GetUriStats() const;

private:
    struct StatsImpl;
    unique_ptr<StatsImpl> pimpl;
};

HttpRequest ParseRequest(string_view line);

#endif  // STATS_H_