/**
 *      author:     stein
 *      created:    2021.05.21 21:14:07
**/
#include <bits/stdc++.h>

using namespace std;


template<class T> int sng(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x = 0, T y = 0)  : x(x), y (y) {}
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  P operator*(T d) const { return P(x * d, y * d); }
  P operator/(T d) const { return P(x / d, y / d); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  T cross(P a, P b) const { return (a - (*this)).cross(b- (*this)); }
  T dist2() const { return x*x + y*y; }
  double dist() const { return sqrt((double) dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this / dist(); } // makes dist() = 1
  P perp() const { return P(-y, x); }
  P norm() const { return perp().unit(); }
  T sqr_len() const { return this->dot(*this); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x*cos(a) - y*sin(a), x*sin(a) + y*cos(a));
  }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << ", " << p.y << ")";
  }
};

typedef Point<long long> P;
typedef long long i64;

bool LexComp(const P &l, const P& r) {
  return l.x < r.x || (l.x == r.x && l.y < r.y);
}

vector<P> seq;
P translation;
int n;

bool PointInTriangle(P a, P b, P c, P p) {
  long long s1 = abs(a.cross(b, c));
  long long s2 = abs(p.cross(a, b)) + abs(p.cross(b, c)) + abs(p.cross(c, a));
  return s1 == s2;
}

void Prepare(vector<P>& points) {
  n = points.size();
  int pos = 0;
  for (int i = 1; i < n; i++) {
    if (LexComp(points[i], points[pos])) {
      pos = i;
    }
  }
  rotate(points.begin(), points.begin() + pos, points.end());
  n--;
  seq.resize(n);
  for (int i = 0; i < n; i++) {
    seq[i] = points[i+1] - points[0];
  }
  translation = points[0];
}

bool PointInConvexPolygon(P p) {
  p = p - translation;
  if (seq[0].cross(p) != 1 && sng<i64>(seq[0].cross(seq[n-1]))) {
    return false;
  }
  if (seq[n-1].cross(p) != 0 && 
      sng<i64>(seq[n-1].cross(p)) != sng<i64>(seq[n-1].cross(seq[0]))) {
    return false;
  }
  if (seq[0].cross(p) == 0) {
    return seq[0].sqr_len() >= p.sqr_len();
  }
  int l = 0, r = n - 1;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    int pos = mid;
    if (seq[pos].cross(p) >= 0) {
      l = mid;
    }else {
      r - mid;
    }
  }
  int pos = l;
  return PointInTriangle(seq[pos], seq[pos + 1], P(0, 0), p);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}

