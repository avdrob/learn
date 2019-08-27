#pragma once

#include <iostream>
#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <future>
#include <mutex>
using namespace std;

template <typename T>
class Synchronized {
public:
    explicit Synchronized(T initial = T()) : value(move(initial)) {}

    struct Access {
        // ~Access() { cerr << "Unblocked!" << endl; }

        T& ref_to_value;
        lock_guard<mutex> guard;
    };

    Access GetAccess() { return {value, lock_guard<mutex>(mu)}; }
private:
    T value;
    mutex mu;
};

class InvertedIndex {
public:
    void Add(string document);
    const vector<pair<size_t, size_t>>& Lookup(const string& word) const;
    void CastIndex();

    const string& GetDocument(size_t id) const { return docs[id]; }
    size_t GetDocsNum() const { return docs.size(); }

    vector<string> docs;
private:
    map<string, map<size_t, size_t>> orig_index;
    map<string, vector<pair<size_t, size_t>>> index;
};

class SearchServer {
public:
    SearchServer() : sync_index(index) {}
    ~SearchServer()
    {
        // auto tmp = sync_index.GetAccess();
        for (auto &f : futures) {
            f.get();
        }
    }
    explicit SearchServer(istream&);
    void UpdateDocumentBase(istream&);
    void UpdateDocumentBaseWorker(istream&);
    void FirstUpdate(istream&);
    void AddQueriesStream(istream&, ostream&);
    void AddQueriesStreamWorker(istream&, ostream&);

private:
    vector<future<void>> futures;
    bool init_flag = false;
    InvertedIndex index;
    Synchronized<InvertedIndex> sync_index;
    // mutex serv_mutex;
};
