/**
 *   author:  stein
 *   created: 2020.09.11 00:10:20
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<tuple<int, int, int>> edges;
  const int inf = 1e9;
  vector<int> distance(n+1, inf);
  int x, y, z;
  while (cin >> x >> y >> z) {
    edges.push_back({x, y, z});
  }
  distance[1] = 0;
  for (int i = 1; i <= n - 1; i++) {
    for (auto e : edges) {
      int a, b, w;
      tie(a, b, w) = e;
      distance[b] = min(distance[b], distance[a]+w);
    }
  }
  for (int i = 1; i <= n; i++) cout << i << " " << distance[i] << endl;
  return 0;
}
