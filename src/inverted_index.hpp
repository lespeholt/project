#include <string>
#include <set>
#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <functional>

#include "boost/algorithm/string.hpp"

using namespace std;

// TODO(lespeholt): Split into IndexBuilder (unsorted) and Index (sorted).

class InvertedIndex {
 public:
  vector<string> query(const string& query) {
    if (query.empty()) {
      return {};
    }

    vector<string> tokens = tokenize(query);

    stack<set<IndexPos>> lookups;

    for (auto token : tokens) {
      lookups.push(lookup_[token]);
    }

    while (lookups.size() >= 2) {
      auto last = lookups.top(); lookups.pop();
      auto first = lookups.top(); lookups.pop();

      set<IndexPos> new_positions;

      consecutive(first.begin(), first.end(), last.begin(), last.end(),
                  inserter(new_positions, new_positions.end()));

      lookups.push(new_positions);
    }

    vector<string> result;

    transform(lookups.top().begin(), lookups.top().end(), back_inserter(result), [](IndexPos pos) {
      return pos.first;
    });

    auto new_end = unique(result.begin(), result.end());

    result.resize(distance(result.begin(), new_end));

    return result;
  }

  void index(const string& key, const string& content) {
    vector<string> tokens = tokenize(content);

    for (unsigned i = 0; i < tokens.size(); ++i) {
      auto token = tokens[i];
      lookup_[token].insert({ key, i });
    }
  }

 private:
  typedef pair<string, uint32_t> IndexPos;

  template <class InputIterator1, class InputIterator2, class OutputIterator>
  void consecutive(InputIterator1 first1, InputIterator1 last1,
                   InputIterator2 first2, InputIterator2 last2,
                   OutputIterator result) {
    while (true) {
      if (first1==last1) break;
      if (first2==last2) break;

      if (first1->first == first2->first
          && first1->second + 1 == first2->second) {
        *result++ = *first1;
      }

      if (*first1 < *first2) {
        *first1++;
      } else {
        *first2++;
      }
    }
  }

  vector<string> tokenize(const string& content) {
    vector<string> result;
    boost::split(result, content, boost::is_any_of(" \n"), boost::token_compress_on);
    return result;
  }

  unordered_map<string, set<IndexPos>> lookup_;
};
