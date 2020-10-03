/**
 *   author:  stein
 *   created: 2020.09.12 13:32:11
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<tuple<int, int, int>> edges, new_edges;
  set<int> used;
  int x, y, z;
  while (cin >> x >> y >> z) {
    edges.push_back({x, y, z});
  }
  sort(edges.begin(), edges.end(), [&] (const tuple<int, int, int> a, const tuple<int, int, int> b) {
    return get<2> (a) < get<2> (b);
  });
  new_edges.push_back(edges.front());
  for (int i = 1; i < (int) edges.size(); i++) {
    tie(x, y, z) = edges[i];
    if (used.count(x) && used.count(y)) continue;
    new_edges.push_back({x, y, z});
    used.insert(x); used.insert(y);
  }
  cout << "Nodes " << used.size() << " Edges " << new_edges.size() << endl; 
  for (auto it : new_edges) {
    tie(x, y, z) = it;
    cout << x << " " << y << " " << z << endl;
  }
  return 0;
}
