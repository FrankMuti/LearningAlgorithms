/**
 *    author:     stein
 *    created:    2020.10.31 20:16:20
**/
#include <bits/stdc++.h>

using namespace std;

#define MAXN 10000000

// Adjancency List
// Unweighted
class AdjList {
  public:
    int n, m;
    vector<int> adj[MAXN];
    AdjList() {
      cin >> n; // number of nodes
      cin >> m; // number of edges
      for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--; // zero-indexed
        adj[a].push_back(b);
        adj[b].push_back(a); // omit this line if the graph is directed
      }
    }
};

// if we're dealing with a weighted graph
namespace simple {
  struct Edge {
    int to, weight;
    Edge(int dest, int w) : to (dest), weight(w) {}
  };
};
// Adjacency Matrix
// Primarily used in the Floyd-Warshall algorithm
class AdjMatrix {
  public:
    int n, m;
    vector<vector<int>> adj;
    AdjMatrix() {
      adj.resize(MAXN, vector<int> (MAXN));
      cin >> n >> m;
      for (int i = 0; i < m; i++) {
        int a;
        int b;
        cin >> a >> b;
        a--, b--; 
        adj[a][b] = 1; // or set to w if graph is weighted
        adj[b][a] = 1; // or w
      }
    }
};

// EdgeList
// Used in weighted undirected graphs, when we
// want to sort the edges by weight for DSU
namespace adv {
  struct Edge {
    int a, b, w;
    Edge(int start, int end, int weight) : a (start), b (end), w (weight) {}
    bool operator<(const Edge& e) {
      // sort order is ascending, by weight to sort
      // in ascending order, just negate the value
      // of the compare.
      return w < e.w;
    }
    friend ostream& operator<<(ostream& os, const Edge& e) {
      return os << e.a << ' ' << e.b << " : " << e.w;
    }
  };
  class Build {
    public:
      int n, m;
      vector<Edge> edges;
      Build() {
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
          int a, b, w;
          cin >> a >> b >> w;
          edges.push_back(Edge(a, b, w));
        }
        cout << "Printing.." << '\n';
        for (auto it : edges) {
          cout << it << '\n';
        }
      }
  };
};

namespace gt {
  vector<bool> visited (MAXN, false);
  vector<int> adj[MAXN];
  vector<int> dist(MAXN, -1);
  class Graph {
    public:
      Graph() {
        build();
      }
      void build() {
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
      void dfs(int node) {
        visited[node] = true;
        for (auto it : adj[node]) {
          if (!visited[it]) {
            cout << node << ' ' << it << '\n';
            dfs(it);
          }
        }
      }
      void bfs(int start) {
        queue<int> q;
        dist[start] = 0;
        q.push(start);
        while (!q.empty()) {
          int v = q.back();
          q.pop();
          for (auto e : adj[v]) {
            if (dist[e] == -1) {
              dist[e] = dist[v]+1;
              q.push(e);
              cout << v << ' ' << e << ':' << dist[e] << '\n';
            }
          }
        }
      }
  };
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  gt::Graph graph;
  graph.bfs(1);
  return 0;
}

