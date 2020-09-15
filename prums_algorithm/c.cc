/**
 *   author:  stein
 *   created: 2020.09.15 16:28:46
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<pair<int, int>> adj[n+1];
  int x, y, z;
  while (cin >> x >> y >> z) {
    adj[x].push_back({y, z});
    adj[y].push_back({x, z});
  }
  vector<tuple<int, int, int>> new_edges;
  set<int> used;
  used.insert(1);
  for (int i = 1; i <= n; i++) {
    pair<int, int> mn = {-1, INT32_MAX};
    int mn_s = -1;
    for (auto s : used) {
      for (auto u : adj[s]) {
        if (used.count(u.first)) continue;
        if (u.second < mn.second) {
          mn = u;
          mn_s = s;
        }
      }
    }
    if (mn_s == -1) continue;
    used.insert(mn.first);
    new_edges.push_back({mn_s, mn.first, mn.second});
  }
  int cost = 0;
  for (auto it : new_edges) {
    tie(x, y, z) = it;
    cost += z;
    cout << x << " " << y << " " << z << endl;
  }
  cout << "Cost " << cost << endl;
  cout << "Nodes " << used.size() << endl;
  cout << "Edges " << new_edges.size() << endl;
  return 0;
}
