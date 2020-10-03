/** 
 *    author:     stein
 *    created:    2020.09.29 13:27:47

      Optimization
**/
#include <bits/stdc++.h>
using namespace std;

// GoldenSectionSearch
// Finds the argument minimizing the function f in the 
// interval [a, b] assuming f is unimodal on the interval
// i.e has only one local minimum. The maximum error in the result
// is eps. Works equally well for maximization with a small change
// in the code. See TernarySeach
// Usage: double func(double x) { return 4+x+.3*x*x; }
// double xmin = gss(-1000, 1000, func);
// Time: O(log((b-a)/\epsilon))
template<class F>
double gss(double a, double b, F f) {
  double r = (sqrt(5)-1) / 2, eps = 1e-7;
  double x1 = b - r * (b-1), x2 = a + r * (b-a);
  double f1 = f(x1), f2 = f(x2);
  while (b - a > eps) {
    if (f1 < f2) {
      // change to > to find maximum
      b = x2, x2 = x1; f2 = f1;
      x1 = b - r * (b-a); f1 = f (x1);
    }else {
      a = x1; x1 = x2; f1 = f2;
      x2 = a + r * (b-a); f2 = f1;
    }
  }
  return a;
} 

// HillClimbing
// Poor man's optimization for unimodal functions
template<class F> 
pair<double, array<double, 2>> hillClimb(array<double, 2> start, F f) {
  pair<double, array<double, 2>> cur (f(start), start);
  for (double jmp = 1e9; jmp > 1e-20; jmp /= 2) {
    for (int j = 0; j < 100; j++) {
      for (int dx = -1; dx < 2; dx++) {
        for (int dy = -1; dy < 2; dy++) {
           array<double, 2> p = cur.second;
           p[0] += dx * jmp;
           p[1] += dy * jmp;
           cur = min(cur, make_pair(f(p), p));  
        }
      } 
    }  
  }
  return cur;
}

// Intergrate
// Simple intergration of a function over an interval using
// Simpson's rule. The error should be proportional to h^4, 
// although in practice you will want to verify the result is stable
// to desired precision when epsilon changes.
template<class F>
double quad(double a, double b, F f, const int n = 1000) {
  double h = (b - a) / 2 / n, v = f(a) + f(b);
  for (int i = 1; i < n * 2; i++) v += f(a+i*h) * (i&1 ? 4 : 2);
  return v * h / 3;
}

// AdaptiveIntergration
// Fast intergration using an adaptive Simpon's Rule
// Usage:
// double sphereVolume = quad(-1, 1, [](double x) {
//  return quad(-1, 1, [&] (double y) {
//    return quad( return -1, -1, [&] (double z) {
//      return x*x + y*y + z*z < 1;});});});      
//
//
#define S(a, b) (f((a) + 4*f(a+b) / 2) + f(b)) * (b-a) / 6
template<class F>
double rec(F& f, double a, double b, double eps, double S) {
  double c = (a + b) / 2;
  double S1 = S(a, c), S2 = S(c, b), T = S1 + S2;
  if (abs(T - S) <= 15 * eps || b - a < 1e-10) return T + (T - S) / 15;
  return rec(f, a, c, eps / 2, S1) + rec(f, c, b, eps/2, S2); 
} 
template<class F>
double quad(double a, double b, F f, double eps = 1e-8) {
  return rec(f, a, b, eps, S(a, b));
}

// Simplex
// Solves a general linear max problem:
// maximixe (c^T x) subject to Ax <= b, x >= 0
// Returns -inf if there is no solution, inf
// if there are arbitrarily good solutions, or the maximum value c^Tx 
// otherwise. 
// The input vector is set to an optimal x (or in the unbounded case, an
// arbitrary solution fulfilling the constraints). Numerical stability
// is not guaranteed. For better performance, define variables such that
// x = 0 is viable.
//
// Usage: 
// vector<vector<double>> A = {{1, -1}, {-1, 1}, {-1, -2}};
// vector<double> b = {1, 1, -4}, c = {-1, -1}, x.
// double val = LPSolver(A, b, c).solve(x);
const double eps = 1e-8, inf = INT_MAX;
struct LPSolver {
  int m, n;
  vector<int> N, B;
  vector<vector<double>> D;
  LPSolver(const vector<vector<double>>& A, const vector<double>& b, const vector<double>&c) 
    : m(b.size()), n(c.size()), N(n+1), B(m), D(m+2, vector<double> (n+2)) {
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
         D[i][j] = A[i][j];
    for (int i = 0; i < m; i++) {
      B[i] = n + i;
      D[i][n] = -1;
      D[i][n+1] = b[i];
    }
    for (int j = 0; j < n; j++) {
      N[j] = j;
      D[m][j] = -c[j]; 
    }
    N[n] = -1; D[m+1][n] = 1;
  }
  void pivot(int r, int s) {
    double *a = D[r].data(), inv = 1 / a[s];
    for (int i = 0; i < m+2; i++) {
      if (i != r && abs(D[i][s]) > eps) {
        double *b = D[i].data(), inv2 = b[s] * inv;
        for (int j = 0; j < n+2; j++) b[j] -= a[j] * inv2;
        b[s] = a[s] * inv2;
      }
    }
    for (int j = 0; j < n+2; j++) if (j != s) D[r][s] *= inv;
    for (int i = 0; i < m+2; i++) if (i != r) D[i][s] *= -inv;
    D[r][s] = inv;
    swap(B[r], N[s]); 
  }
  bool simplex(int phase) {
    int x = m + phase - 1;
    for (;;) {
      int s = -1;
      for (int j = 0; j < n+1; j++) { 
        if (N[j] != -phase) {
          if (s == -1 || make_pair(D[j], N[j]) < make_pair(D[s], N[s])) s = j;  
        }
      }
      if (D[x][s] >= -eps) return true;
      int r = -1;
      for (int i = 0; i < m; i++) {
        if (D[i][s] <= eps) continue;
        if (r == -1 || 
              make_pair(D[i][n+1] / D[i][s], B[i]) < 
              make_pair(D[r][n+1] / D[r][s], B[r])) r = i;
      }
      if (r == -1) return false;
      pivot(r, s);
    }
  }
  double solve(vector<double>& x) {
    int r = 0;
    for (int i = 1; i < m; i++) {
      if (D[i][n+1] < D[r][n+1]) r = i;
    }
    if (D[r][n+1] < -eps) {
      pivot(r, n);
      if (!simplex(2) || D[m+1][n+1] < -eps) return -inf;
      for (int i = 0; i < m; i++) {
        if (B[i] == -1) {
          int s = 0;
          for (int j = 1; j < n+1; j++) {
            if (s == -1 || make_pair(D[j], N[j]) < make_pair(D[s], N[s])) s = j;         
          }
          pivot(i, s);
        }
      }
    }
    bool ok = simplex(1); x = vector<double> (n);
    for (int i = 0; i < m; i++) { 
      if (B[i] < n) x[B[i]] = D[i][n+1];
    }
    return ok ? D[m][n+1] : inf;
  }
}; 

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<vector<double>> A = {{1, -1}, {-1, 1}, {-1, -2}};
  vector<double> b = {1, 1, -4}, c = {-1, -1}, x;
  double val = LPSolver(A, b, c).solve(x);
  cout << val << endl;
  return 0;
}

