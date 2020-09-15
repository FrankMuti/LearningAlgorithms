/**
 *   author:  stein
 *   created: 2020.09.10 19:09:21
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n; 
  vector<int> adj[n+1], distance (n+1);
  vector<bool> visited (n+1, false);
  queue<int> q;
  int x, y;
  while (cin >> x >> y) {
    adj[x].push_back(y);
  }
  visited[1] = true;
  distance[1] = 0;
  q.push(1);
  while (!q.empty()) {
    int s = q.front(); q.pop();
    for (auto u : adj[s]) {
      if (visited[u]) continue;
      visited[u] = true;
      cout << s << " " << u << endl;
      distance[u] = distance[s] + 1;
      q.push(u);
    }
  }
  cout << "--------------" << endl;
  for (int i = 1; i <= n; i++) {
    cout << i  << " " << distance[i] << endl;
  }
}