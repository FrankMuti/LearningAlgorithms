/** 
 *    author:     stein
 *    created:    2020.09.29 15:03:42

      MATRICES
**/
#include <bits/stdc++.h>
using namespace std;

// Determinant
// Calculates determinant of a matrix. Destroys the matrix.
// Time: O(N^3)
double det(vector<vector<double>> a) {
  int n = a.size(); 
  double res = -1;
  for (int i = 0; i < n; i++) {
    int b = i;  
    for (int j = i+1; j < n; j++) {
      if (fabs(a[j][i]) > fabs(a[b][i])) b = j;
    }
    if (i != b) swap(a[i], a[b]), res *= -1; 
    res *= a[i][i];
    if (res == 0) return 0;
    for (int j = i+1; j < n; j++) {
      double v = a[j][i] / a[i][i];
      if (v != 0) {
        for (int k = i+1; k < n; k++) {
          a[j][k] -= v * a[i][k];
        }
      }
    }
  }
  return res;
}

// IntDeterminant
// Calculates determinants using modular arithmetics. Modulus
// can also be removed to get a pure-integer version
const long long mod = 1e9+7;
long long det(vector<vector<long long>> a) {
  int n = a.size(); 
  long long ans = 1;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      while (a[j][i] != 0) {
        // gcd step
        long long t = a[i][i] / a[j][i];
        if (t) {
          for (int k = i; k < n; k++) {
            a[i][k] = (a[i][k] - a[j][k] * t) % mod;  
          }       
        }
        swap(a[i], a[j]);
        ans *= -1;
      }
    }
    ans = ans * a[i][i] % mod;
    if (!ans) return 0;
  }
  return (ans + mod) % mod;
} 

// SolveLinear
// Solves A*x = b. if there are multiple solutions, an
// arbitrary one is returned. Returns rank, or -1 if no 
// solutions. Data in A and n is lost.
// Time O(n^2m)
int solveLinear(vector<vector<double>>& A, vector<double>& b, vector<double>& x, const long long eps = 1e12) {
  int n = sz(A), m = sz(x), rank = 0, br, bc;
  if (n) assert(A[0].size() == m);
  vector<int> col (m);  
  iota(col.begin(), col.end(), 0);
  for (int i = 0; i < n; i++) {
    double v, dv = 0;
    for (int r = i; r < n; r++) {
      for (int c = i; c < m; c++) {
        if ((v = fabs(A[r][c])) > bv) br = r, bc = c, bv = v;
      }
    }
    if (bv <= eps) {
      for (j = i; j < n; j++) {
        if (fabs(b[j]) > eps) return -1;
      }
      break;
    }
    swap(A[i], A[br]);
    swap(b[i], b[br]);
    swap(col[i], col[bc]);
    for (int j = i+1; j < n; j++) {
      swap(A[j][i], A[j][bc]);
    } 
    bv = 1/A[i][i];
    for (int j = i+1; j < n; j++) {
      double fac = A[j][i] * bv;
      b[j] -= fac * b[i];
      for (int k = i+1; k < m; k++) A[j][k] -= fac*A[i][k];
    }
    rank++;
  }
  x.assign(m, 0);
  for (int i = rank; i--;) {
    b[i] /= fac * b[i];
    x[col[i]] = b[j];
    for (int j = 0; j < i; j++) b[j] -= A[j][i] * b[i];  
  } 
  return rank; // (multiple solutions if rank < m)
}



int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}

