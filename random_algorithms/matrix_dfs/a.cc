/**
 *    author:     stein
 *    created:    2020.11.11 14:45:19
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> grid (n, vector<int> (m));
  for (auto& r : grid) {
    for (auto& it : r) {
      cin >> it;
    }
  }
  vector<vector<bool>> visited (n, vector<bool> (m));
  function<int(int, int)> Safe = [&] (int x, int y) {
    return (x >= 0) && (x < n) && (y >= 0) && (y < m) 
      && (grid[x][y] && !visited[x][y]);
  };
  function<void(int, int)> Dfs = [&] (int x, int y) {
    static int rowNbr [] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static int colNbr [] = {-1, 0, 1, -1, 1, -1, 0, 1};
    visited[x][y] = true;
    for (int k = 0; k < 8; ++k) {
      if (Safe(x+rowNbr[k], y+colNbr[k])) {
        Dfs(x+rowNbr[k], y+colNbr[k]);
      }
    }
  };
  int res = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] && !visited[i][j]) {
        Dfs(i, j);
        ++res;
      }
    }
  }
  cout << res << endl;
  return 0;
}

