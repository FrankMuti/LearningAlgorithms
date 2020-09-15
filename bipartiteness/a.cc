/**
 *   author:  stein
 *   created: 2020.09.10 23:28:40
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> adj[n+1];
  vector<bool> visited(n+1);
  vector<vector<int>> colors (n+1, vector<int> (n+1));
  int x, y;
  while (cin >> x >> y) {
    adj[x].push_back(y);
  }
  function<void(int)> Dfs = [&] (int s) {
    if (visited[s]) return;
    visited[s] = true;
    for (auto u : adj[s]) {
      cout << s << " " << u << endl;
      Dfs(u);
    }
  };
  Dfs(1);
  return 0;
}
