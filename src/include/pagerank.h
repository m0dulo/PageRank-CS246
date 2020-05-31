#ifndef PAGERANK_PAGERANK_H
#define PAGERANK_PAGERANK_H

#include "utilis.h"
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#define MAX 30000
#define dtype double

const dtype eps = 1e-7;
const dtype beta = 0.8;

using namespace std;

class PageRank {
private:
  vector<int> edge[MAX];
  int k[MAX];
  int v[MAX];
  dtype r[MAX];
  dtype temp[MAX];
  set<int> cnt;

  vector<pair<dtype, int>> ans;

  unordered_map<int, dtype> answer;

  void covert2Edge(vector<vector<string>> &vec) {
    for (auto &vect : vec) {
      int a = atoi(vect[0].c_str());
      int b = atoi(vect[1].c_str());
      // cout << a << " " << b << endl;;
      edge[a].emplace_back(b);
      v[b]++;
      k[a]++;
      cnt.insert(b);
      cnt.insert(a);
    }
  }

  static dtype myFabs(dtype a) { return a > 0 ? a : -a; }

  static bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
    return a.second < b.second;
  }

public:
  void compute(vector<vector<string>> &data) {
    covert2Edge(data);
    int size = cnt.size();
    cout << size << endl;
    for (int i = 1; i <= size; ++i) {
      r[i] = 1 / size;
    }
    dtype e = 1.0;
    while (e > eps) {
      for (int i = 1; i <= size; ++i) {
        temp[i] = r[i];
      }
      for (int i = 1; i <= size; ++i) {
        r[i] = 0.0;
      }
      dtype sum = 0.0;
      for (int i = 1; i <= size; ++i) {
        int t = i;
        for (auto e : edge[t]) {
          r[e] += beta * temp[t] / k[t];
        }
      }

      for (int i = 1; i <= size; ++i) {
        sum += r[i];
      }

      for (int i = 1; i <= size; ++i) {
        r[i] += (1 - sum) / size;
      }
      e = 0;
      for (int i = 1; i <= size; ++i) {
        e += myFabs(r[i] - temp[i]);
      }
    }

    for (int i = 1; i <= size; ++i) {
      ans.emplace_back(make_pair(r[i], i));
    }
    sort(ans.begin(), ans.end());

    for (int i = ans.size() - 1; i >= ans.size() - 5; --i) {
      LyxUtilis::log(ans[i].first, " ", ans[i].second);
    }
  }
};

#endif // PAGERANK_PAGERANK_H