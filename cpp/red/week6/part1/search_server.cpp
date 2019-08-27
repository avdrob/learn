#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <functional>

vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

vector<string> SplitIntoWords(string&& line) {
  istringstream words_input(move(line));
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::FirstUpdate(istream& document_input) {
  InvertedIndex new_index;
  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }
  sync_index.GetAccess().ref_to_value = move(new_index);
  sync_index.GetAccess().ref_to_value.CastIndex();
}

void SearchServer::UpdateDocumentBaseWorker(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }

  sync_index.GetAccess().ref_to_value = move(new_index);
  sync_index.GetAccess().ref_to_value.CastIndex();
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
    if (!init_flag) {
        // lock_guard<mutex> guard(serv_mutex);
        FirstUpdate(document_input);
        init_flag = true;
        return;
    }
    futures.push_back(async(&SearchServer::UpdateDocumentBaseWorker,
                            this, ref(document_input)));
  	// this_thread::sleep_for(chrono::microseconds(1000));
}

void SearchServer::AddQueriesStreamWorker(istream& query_input,
                                          ostream& search_results_output)
{
  while (!init_flag) {
      continue;
  }

  vector<pair<size_t, size_t>> docid_count;
  for (string current_query; getline(query_input, current_query); ) {
    docid_count.resize(sync_index.GetAccess().ref_to_value.GetDocsNum());

    for (size_t i = 0; i < docid_count.size(); ++i) {
        docid_count[i].first = i;
        docid_count[i].second = 0;
    }

    for (auto& word : SplitIntoWords(current_query)) {
      for (auto it : sync_index.GetAccess().ref_to_value.Lookup(word)) {
        docid_count[it.first].second += it.second;
      }
    }

    vector<pair<size_t, size_t>> search_results(docid_count.begin(),
                                                docid_count.end());
	auto mid = search_results.begin() +
				min(static_cast<size_t>(5), search_results.size());
    partial_sort(search_results.begin(), mid, search_results.end(),
                 [] (const pair<size_t, size_t>& lhs,
				     const pair<size_t, size_t>& rhs) {
				       return lhs.second != rhs.second ?
				         lhs.second > rhs.second :
				      	 lhs.first < rhs.first;
				     }
                );

    search_results_output << current_query << ':';
    for (auto [docid, hitcount] : Head(search_results, 5)) {
      if (hitcount == 0) {
          break;
      }
      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;
  }
}

void SearchServer::AddQueriesStream(istream& query_input,
                                    ostream& search_results_output)
{
    futures.push_back(async(&SearchServer::AddQueriesStreamWorker, this,
                            ref(query_input), ref(search_results_output)));
  	// this_thread::sleep_for(chrono::microseconds(1000));
}

void InvertedIndex::Add(string document) {
  const size_t docid = docs.size();
  for (auto& word : SplitIntoWords(document)) {
    orig_index[move(word)][docid] += 1;
  }
  docs.push_back(move(document));
}

const vector<pair<size_t, size_t>>& InvertedIndex::Lookup(const string& word) const {
  static const vector<pair<size_t, size_t>> empty_vector = {};

  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return empty_vector;
  }
}

void InvertedIndex::CastIndex()
{
    for (auto it : orig_index) {
        index[move(it.first)].assign(it.second.begin(), it.second.end());
    }
}
