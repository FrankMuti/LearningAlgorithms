/**
 *   author:  stein
 *   created: 2020.09.11 00:55:00
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<pair<int, int>> adj [n+1];
  int x, y, z;
  while (cin >> x >> y >> z) {
    adj[x].push_back({y, z});
  }
  vector<bool> processed (n+1);
  vector<int> distance(n+1, INT32_MAX);
  priority_queue<pair<int, int>> q;
  distance[1] = 0;
  q.push({0, 1});
  while (!q.empty()) {
    int a = q.top().second; q.pop();
    if (processed[a]) continue;
    processed[a] = true;
    for (auto u : adj[a]) {
      int b = u.first, w = u.second;
      if (distance[a]+w < distance[b]) {
        distance[b] = distance[a]+w;
        q.push({-distance[b], b});
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << i << " " << distance[i] << endl;
  }
  return 0;
}
