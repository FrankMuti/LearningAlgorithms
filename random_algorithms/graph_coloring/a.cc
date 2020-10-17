/**
 *    author:     stein
 *    created:    2020.10.07 13:55:22
 * 
 *
 * Graph coloring problems is to assign colors to certain elements of
 * of a graphs subject to certain constraints
 *
 *
 * 
**/
#include <bits/stdc++.h>

using namespace std;

// An undirected graph
class Graph {
  private:
    int V; 
    list<int> *adj;
  public:
    Graph(int V) {
      this->V = V;
      adj = new list<int>[V];
    }
    ~Graph() {
      delete [] adj;
    }
    void addEdge(int v, int w) {
      adj[v].push_back(w);
      adj[w].push_back(v);
    }
    void greedyColoring() {
      int result[V];
      // Assign the first color to first vertex
      result[0] = 0;
      // Initialize remaining V-1 vertices as unassigned
      for (int u = 1; u < V: u++) {
        result[u] = -1;
      }
      // A temporary array to store the available colors
      // True value of available[cr] would mean that the color cr
      // is assigned to one of its adjacent vertices
      bool available[V];
      for (int cr = 0; cr < V; cr++) {
        available[cr] = false;
      }
      // Assign colors to remaining V-1 vertices
      for (int u = 1; u < V; u++) {
        // Process all adjacent vertices and flag their colors
        // as unavailable
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
          if (result[*i] != -1) available[result[*i]] = true;
        }
        int cr;
        for (cr = 0; cr < V; cr++) {
          if (!available[cr]) {
            break;
          }
        }
        result[u] = cr; // Assign the found color
        // Reset the values back to false for the next iteration
        for (i = adj[u].begin(); i != adj[u].end(); i++) {
          if (result[*i] != -1) {
            available[result[*i]] = false;
          }
        }
      }
      // Print the results
      for (int u = 0; u < V; u++) {
        cout << "Vertex " << u << " --> Color " << result[u] << endl;
      }
    }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Graph g1(5);

  return 0;
}

