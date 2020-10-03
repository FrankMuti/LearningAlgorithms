/**
 *   author:  stein
 *   created: 2020.09.15 16:28:46
**/
#include <bits/stdc++.h>
using namespace std;

#define MAX INT32_MAX

class Graph {
public:
  vector<vector<int>> LinkCost;
  int NNodes;
  Graph(vector<vector<int>> mat) {
    NNodes = mat.size();
    LinkCost = vector<vector<int>> (mat);
    for (int i = 0; i < NNodes; i++) {
      for (int j = 0; j < NNodes; j++) {
        if (LinkCost[i][j] == 0) LinkCost[i][j] = MAX;
      }
    }
    for (int i = 0; i < NNodes; i++) {
      for (int j = 0; j < NNodes; j++) {
        if (LinkCost[i][j] < MAX) cout << " " << LinkCost[i][j] << " ";
        else cout << " * "; 
      }
      cout << endl;
    }
  }
  int unReached(vector<bool> r) {
    bool done = true;
    for (int i = 0; i < (int) r.size(); i++) {
      if (!r[i]) return i;
    }
    return -1;
  }
  void prim() {
    vector<bool> Reached (NNodes);
    vector<int> predNodes (NNodes);
    Reached[0] = true;
    predNodes[0] = 0;
    cout << "Reachset : ";
    for (int i = 0; i < (int) Reached.size(); i++) {
      if (Reached[i]) cout << i << " ";
    }
    cout << endl;
    for (int k = 0; k < NNodes; k++) {
      int x = 0, y = 0;
      for (int i = 0; i < NNodes; i++) {
        for (int j = 0; j < NNodes; j++) {
          if (Reached[i] && !Reached[j] && LinkCost[i][j] < LinkCost[x][y]) {
            x = i, y = j;
          }
        }
      }
      cout << "Min cost edge: (" << x << ", " << y << ") cost = " << LinkCost[x][y] << endl; 
      predNodes[y] = x;
      Reached[y] = true;
      cout << "Reachset : ";
      for (int i = 0; i < (int) Reached.size(); i++) {
        if (Reached[i]) cout << i << " ";
      }
      cout << endl;
    }
    vector<int> a (predNodes);
    for (int i = 0; i < NNodes; i++) {
      cout << a[i] << " --> " << i << endl; 
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<vector<int>> conn {
    {0,3,0,2,0,0,0,0,4},
    {3,0,0,0,0,0,0,4,0},
    {0,0,0,6,0,1,0,2,0},
    {2,0,6,0,1,0,0,0,0},
    {0,0,0,1,0,0,0,0,8},
    {0,0,1,0,0,0,8,0,0},
    {0,0,0,0,0,8,0,0,0},
    {0,4,2,0,0,0,0,0,0},
    {4,0,0,0,8,0,0,0,0}
  };
  Graph G (conn);
  G.prim();
  return 0;
}
