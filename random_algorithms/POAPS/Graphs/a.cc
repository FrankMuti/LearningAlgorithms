/**
 *    author:     stein
 *    created:    2020.10.31 21:24:05
**/
#include <bits/stdc++.h>

using namespace std;

#define M 100000

namespace basic {
  vector<int> adj[M];
  vector<int> dist(M, -1);
  vector<bool> visited(M, false); 
  
  class Graph {
    public:
      Graph() {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
          int a, b, w;
          cin >> a >> b >> w;
          a++, b++;
          adj[a].push_back(b);
          adj[b].push_back(a);
        }
      }
      void dfs(int n) {
        visited[n] = true;
        for (auto e : adj[n]) {
          if (!visited[e]) {
            cout << n << ' ' << e << '\n';
            dfs(e);
          }
        }
      }
      void bfs(int n) {
        queue<int> q;
        dist[n] = 0;
        q.push(n);
        while (!q.empty()) {
          int v = q.back();
          q.pop();
          for (auto e : adj[v]) {
            if (dist[e] == -1) {
              dist[e] = dist[v]+1;
              q.push(e);
              cout << v << ' ' << e << ' ' << dist[e] << '\n';
            }
          }
        }
      }
  };
};

// 8 Puzzle
// In the 8-Puzzle, 8 tiles are arranged in a 3x3 grid, with
// one square left empty. The goal is to perform some moves 
// to reach the target config. The target config has the empty square in
// the bottom right corner, with the numbers in order,  1, 2, 3, ...8

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  puzzle_8::solve();
  return 0;
}

