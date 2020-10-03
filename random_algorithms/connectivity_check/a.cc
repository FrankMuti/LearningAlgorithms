/**
 *   author:  stein
 *   created: 2020.09.10 20:17:38
**/
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
queue<int> q;

class Dfs {
private:
  vector<vector<int>> adj;
  vector<bool> visited;
public:
  int cnt = 0;
  Dfs(int n) {
    adj.resize(n+1);
    visited.resize(n+1, false);
    for (int i = 0; i < 2*n; i++) {
      int x, y;
      cin >> x >> y;
      adj[x].push_back(y);
    }
    dfs(1);
  }
  void dfs(int s) {
    if (visited[s]) return;
    visited[s] = true;
    cnt++;
    for (auto u : adj[s]) {
      dfs(u);
    } 
  }
};

class Bfs {
private:
  vector<vector<int>> adj;
  vector<bool> visited;
  queue<int> q;
public:
  int cnt = 1;
  vector<int> distance;
  Bfs(int n) {
    adj.resize(n+1);
    visited.resize(n+1);
    distance.resize(n+1);
    int x, y;
    while (cin >> x >> y) {
      adj[x].push_back(y);
    }
    visited[2] = true;
    distance[2] = 0;
    q.push(2);
    while (!q.empty()) {
      int s = q.front(); q.pop();
      for (auto u : adj[s]) {
        if (visited[u]) continue;
        visited[u] = true;
        cnt++;
        distance[u] = distance[s] + 1;
        q.push(u);
      } 
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  auto bfs = Bfs(n);
  cout << bfs.cnt << " " << (bfs.cnt < n ? "NO" : "YES") << endl;
  for (int i = 1; i <= n; i++) {
    cout << i << " " << bfs.distance[i] << endl;
  } 
  return 0;
}
