/** 
 *    author:     stein
 *    created:    2020.09.28 02:15:15
 *    
 *    Calculate submatrix sums quickly, given upper-left and lower-right 
      corners
**/
#include <bits/stdc++.h>
using namespace std;

// Usage:
// Submatrix<int> m (matrix);
// m.sum(0, 0, 2, 2); // top left 4 elements

template<class T>
struct SubMatrix {
  Node *a, *b, *c;
  vector<vector<T>> p;
  SubMatrix(vector<vector<T>>& v) {
    int R = v.size(), C = v[0].size();
    p.assign(R+1, vector<T> (C+1));
    for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c) {
        p[r+1][c+1] = v[r][c] + p[r][c+1] + p[r+1][c] - p[r][c];   
      }
    } 
  }
  T sum(int u, int l, int d, int r) {
    return p[d][r] - p[d][l] - p[u][r] + p[u][l];
  }
}; 

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  
  return 0;
}

