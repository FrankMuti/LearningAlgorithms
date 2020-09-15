/**
 *   author:  stein
 *   created: 2020.09.11 01:32:12
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> adj[n+1];
  int x, y;
  while (cin >> x >> y) {
    adj[x].push_back(y);
  }
  function<void(int, int)> Dfs = [&] (int s, int e) {
    for (auto u : adj[s]) {
      cout << s << " " << u << endl; 
      if (u != e) Dfs(u, s);
    } 
  };
  vector<int> count(n+1);
  function<void(int, int)> CtNodes = [&] (int s, int e) {
    count[s] = 1;
    for (auto u : adj[s]) {
      if (u == e) continue;
      CtNodes(u, s);
      count[s] += count[u];
    }
  };
  Dfs(1, 0);
  CtNodes(1, 0);
  cout << " -- " << endl;
  for (int i = 1; i <= n; i++) cout << i << " " << count[i] << endl;
  return 0;
}
