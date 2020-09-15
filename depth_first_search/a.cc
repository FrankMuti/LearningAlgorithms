/**
 *   author:  stein
 *   created: 2020.09.10 18:30:02
**/
#include <bits/stdc++.h>
using namespace std;

#define MX 100

vector<vector<int>> adj;
vector<bool> visited;

int n;

int main() {
  cin >> n;
  adj = vector<vector<int>> (n+1);
  visited.resize(n+1, false);
  int x, y;
  while (cin >> x >> y) {
    adj[x].push_back(y);
  }
  function<void(int)> dfs = [&] (int s) {
    if (visited[s]) return;
    visited[s] = true;
    for (auto u : adj[s]) {
      cout << s << " " << u << endl;
      dfs(u);
    }
  };

  dfs(1);

}