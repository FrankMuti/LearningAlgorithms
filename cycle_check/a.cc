/**
 *   author:  stein
 *   created: 2020.09.10 21:11:46
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> graph[n];
  vector<bool> visited (n);
  vector<bool> resStack (n);
  int x, y;
  while (cin >> x >> y) {
    graph[x].push_back(y);
    cout << x << " " << y << endl;
  }
  function<bool(int)> helper = [&](int u) {
    visited[u] = true;
    resStack[u] = true;
    for (auto it : graph[u]) {
      if (resStack[it]) return true;
      else if (it == u) return true;
      else if (!visited[it]) {
        if (helper(it)) return true;
      }
    } 
    resStack[u] = false;
    return false;
  };
  function<bool()> isCyclic = [&]() {
    for (int u = 0; u < n; u++) {
      if (!visited[u]) {
        if (helper(u)) return true;
      }
    }
    return false;
  };
  bool res = isCyclic();
  cout << (res ? "YES" : "NO") << endl;
  visited.clear();
  visited.resize(n);
  return 0;
}
