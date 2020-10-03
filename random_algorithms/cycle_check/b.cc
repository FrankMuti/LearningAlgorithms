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
  vector<bool> visited (n); // array to track vertices already visited
  vector<bool> resStack (n); // array to track vertices in recursion stack of the traversal
  int x, y;
  while (cin >> x >> y) {
    graph[x].push_back(y);
    cout << x << " " << y << endl;
  }
  function<bool(int)> helper = [&] (int u) {
    visited[u] = true;
    resStack[u] = true;
    for (auto it : graph[u]) {
      // if vertice v is found in recursion stack of this dfs
      if (resStack[it]) return true;
      // if there's an edge from the vertex to itself
      if (it == u) return true;
      if (!visited[it]) {
        if (helper(it)) return true;
      }
    }
    resStack[u] = false;
    return false;
  };
  // The wrappper function calls helper function on each vertices which
  // have not been visited. Helper function returns true is it detects
  // a back edge in the subgraph (tree) or false
  function<bool()> isCyclic = [&] () {
    for (int u = 0; u < n; u++) {
      if (!visited[u]) {
        if (helper(u)) return true; // checks if the DFS tree from the vertex contains a cycle
      }
    }
    return false;
  };
  bool res = isCyclic();
  cout << (res ? "YES" : "NO") << endl;
  return 0;
}
