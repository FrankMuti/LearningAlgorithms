/** 
 *    author:     stein
 *    created:    2020.09.29 16:35:59
 *
 *    GEOMETRY 
**/
#include <bits/stdc++.h>
using namespace std;

// Geometric Primitives

// Point
// Class to handle points in the place. 
template<class T>
int sng(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x=0, T y=0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); } 
  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(T d) const { return P(x*d, y*d); }
  P operator/(T d) const { return P(x/d, y/d); }
  T dot (P p) const { return x*p.x + y*p.y; }
  T cross (P p) const { return x*p.y - y*p.x; }
  T cross (P a, P b) const { return (a-*this).cross(b-*this); }
  T dist2() const { return x*x + y*y; }
  double dist() const { return sqrt((double) dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this/dist(); } // makes dist() = 1 
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const { return P(x*cos(a)-y*sin(a), x*sin(a)+y*cos(a)); }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")";  
  }
};

// LineDistance
// Returns the signed distance between point p and the line containing points
// a and . Positive value on left side and negative on right as seen from a 
// towards b. a==b gives nan. P is supposed yo be Point<T> or Point3D<T>.
// It uses products in intermediate steps so watch out for overflow if using
// int or long long. Using Point3D will always give a non-negative distance. 
// For Point3D, call dist on the cross product
template<class P>
double lineDist(const P& a, const P& b, const P& p) {
  return (double) (b-a).cross(p-a)/(b-a).dist();
}

// SegmentDistance
// Returns the shortest distance between point p and the line
// segment from point s to e
// Usage: Point<double> a, b (2, 2), p (1, 1);
//        bool onSegment = segDist(a, b, p) < 1e-10
double segDist(Point<double>& s, Point<double>& e, Point<double>& p) {
  if (s == e) return (p-s).dist();
  auto d = (e-s).dist2(), t = min(d, max(0., (p-s).dot(e-s)));
  return ((p-s)*d-(e-s)*t).dist() / d;
}

// OnSegment
// Returns true iff p lines on the line segment from s to e
// use (segDist(s, e, p) <= epsilon) instead of Point<double>
template<class P>
bool onSegment(P s, P e, P p) {
  return p.cross(s,e) == 0 && (s-p).dot(e-p) <= 0;
}

// SegmentIntersection
// If a unique intersection point between the line segments going from s1 
// to e1 and from s2 to e2 exists the it is returned else empty vector.
// If infinitely many exists, a vector with two elements is returned
// containing the endpoints of the common line segment. The wrong position will be
// returned if P is Point<long long> and the intersection point does not have 
// interger coordinates. Products of the three coordinates are used so watch out for 
// overflow if using int or long long
//
// Usage: 
// vector<Point> inter = segInter(s1, e1, s2, e2);
// if (inter.size() == 1) cout << "Intersection: " << inter[0] << endl;
template<class T>
vector<Point<T>> segInter(Point<T> a, Point<T> b, Point<T> c, Point<T> d) {
  auto oa = c.cross(d, a), ob = c.cross(d, b), 
       oc = a.cross(b, c), od = a.cross(b, d);
  // checks if intersection is single non-endpoint point
  if (sng(oa) * sng(ob) < 0 && sng(oc) * sng(od) < 0) {
    return { (a * ob - b * oa) / (ob - oa) };
  }
  set<Point<T>> s;
  if (onSegment(c, d, a)) s.insert(a);
  if (onSegment(c, d, b)) s.insert(b);
  if (onSegment(a, b, c)) s.insert(c);
  if (onSegment(a, b, d)) s.insert(d);
  return { s.begin(), s.end() };
}

// LineIntersection
// If a unique intersection point of the lines going from s1, e1, and s2, e2
// exists {1, point} is returned. If no intersection point exists {0, (0, 0)}
// is returned and if infinitely many exists {-1, (0, 0)} is returned if P
// is Point<long long> and the intersection point does not have integer 
// coordinates. Products of three coordinates are used in intermediate
// steps so watch out for overflow if using int ot long long
//
// Usage:
// auto res = lineInter(s1, e1, s2, e2);
// if (res.first == 1) cout << "Inter " << res.second << endl;
template<class T>
pair<int, Point<T>> lineInter(Point<T> s1, Point<T> e1, Point<T> s2, Point<T> e2 ) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0) {
    // if parallel
    return {-(s1.cross(e1, s2) == 0), Point<T> (0, 0)};
  }
  auto p = s2.cross(e1, s2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};  
}

// SideOf
// Returns where p is as seen from s towards e. 1/0/-1 <=> left/line/right
// if the optional eps is given 0 is returned if p is within distance eps from the
// line. It useds products in intermediate steps so watch out for overflow if using
// or long long.
// 
// Usage: bool left = sideOf(p1, p2, q) == 1;
template<class T>
int sideOf(Point<T> s, Point<T> e, Point<T> p) { return sng(s.cross(e, p)); }
template<class T>
int sideOf(const Point<T>& s, const Point<T>& e, const Point<T>& p, double eps) {
  auto a = (e-s).cross(p-s);
  double l = (e-s).dist() * eps;
  return (a > l) - (a < -l);
}

// OnSegment 
// Returns true iff p lies on the line segment from s to e.
// (segDist(s, e, p) <= epsilon) instead of when using Point<double>
template<class T>
bool onSegment(Point<T> s, Point<T> e, Point<T> p) {
  return p.cross(s, e) == 0 && (s-p).dot(e-p) <= 0;
}

// LineTransformation
// Apply the linear transformation (translation, rotation and scaling)
// which takes line p0-p1 to line q0-q1 to point r
// 
// Use double || long doubles 
template<class T>
Point<T> linearTransformation(const Point<T>& p0, const Point<T>& p1,   
  const Point<T>& q0, const Point<T>& q1, const Point<T>& r) {
  Point<T> dp = p1 - p0, dq = q1 - q0, num(dp.cross(dq), dp.dot(dq));
  return q0 + Point<double> ((r - p0).cross(num), (r-p0).dot(num)) / dp.dist2();
}

// Angle
// A class for ordering angles (as rep by int points and a number of 
// rotations arounf the origin). Useful for rotational sweeping.
// Useful for rotational sweeping. Sometimes also rep points or vectors.
//
// Usage: 
// vector<Angle> v = { w[0], w[0].t360(), ... }; // sorted 
// int j = 0;
// for (int i = 0; i < n; i++) {
//    while (v[j] < v[i].t180()) ++j;
// }
// // sweeps j such that (j-i) represents the number of positively oriented triangles
// // with vertices 0 and i
struct Angle {
  typedef int T;
  T x, y, t;
  Angle(T x, T y, T t = 0) : x (x), y (y), t (t) {}
  Angle operator-(Angle b) const { return {x-b.x, y-b.y, t}; }
  T half () const {
    assert(x || y);
    return y < 0 || (y == 0 && x < 0);
  } 
  Angle t90() const { return {-y, x, t + (half() && x >= 0) }; }
  Angle t180() const { return {-x, -y, t + half()}; }
  Angle t360() const { return {x, y, t + 1}; }
};
bool operator<(Angle a, Angle b) {
  // add a.dist2() and b.dist2() to also compare distances
  return make_tuple(a.t, a.half(), a.y * (long long)b.x) <
         make_tuple(b.t, b.half(), a.x * (long long)b.y);
}

// Given two points, this calculates the smallest angle between
// them, i.e, the angle that cover the defined line segment.
pair<Angle, Angle> segmentAngles(Angle a, Angle b) {
  if (b < a) swap(a, b);
  return (b < a.t180() ? make_pair(a, b) : make_pair(b, a.t360()));
} 
Angle operator+(Angle a, Angle b) {
  // point a + vector b
  Angle r (a.x + b.x, a.y + b.y, a.t);
  if (a.t180() < r) r.t--;
  return r.t180() < a ? r.t360() : r;
}
Angle angleDiff(Angle a, Angle b) {
  // angle b - angle a
  int tu = b.t - a.t;
  a.t = b.t;
  return {a.x*b.x + a.y*b.y, a.x*b.y - a.y*b.y, tu - (b < a)}; 
}

/// CIRCLES

// CircleIntersection
// Computes the pair of points at which two circles intersect.
// Returns false in case of no intersection.
// T represents preferably floating points, double or long double
template<class T>
bool circleInter(Point<T> a, Point<T> b, T r1, T r2, pair<Point<T>, Point<T>>* out) {
  if (a == b) {
    assert(r1 != r2);
    return false;
  }
  Point<T> vec = b - a;
  T d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
    p = (d2 + r1*r1 - r2*r2) / (d2*2), h2 = r1*r1 - p*p*d2;
  if (sum*sum < d2 || dif*dif > d2) return false;
  Point<T> mid = a + vec.p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
  *out = {mid + per, mid - per};
  return true;
}

// CircleTangents
// Finds the external tangents of two circles, or internal of r2 is negated
// Can return 0, 1, or 2 tangents .
// 0 - one circle contains the other; 1, if the circles are tangent to each other
//
// T : doubles or long doubles
template<class T>
vector<pair<Point<T>, Point<T>>> tangents (Point<T> c1, T r1, Point<T> c2, T r2) {
  Point<T> d = c2 - c1;
  T dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
  if (d2 == 0 || h2 < 0) return {};
  vector<pair<Point<T>, Point<T>>> out;
  for (auto sign : {-1, 1}) {
    Point<T> v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
    out.push_back({c1 + v * r1, c2 + v * r2});
  }
  if (h2 == 0) out.pop_back();
  return out;
} 

// CircumCircle
// The circumcircle of a triangle is the circle intersecting all
// three vertices. ccRadius returns the radius of the circle going
// through points A, B, and C and ccCenter returns the center
// of the same circle.
//
// T: preferable double, long doubles
template<class T>
T ccRadius(const Point<T>& A, const Point<T>& B, const Point<T>& C) {
  return (B-A).dist()*(C-B).dist()*(A-C).dist()/abs((B-A).cross(C-A))/2;
}
template<class T>
Point<T> ccCenter(const Point<T>& A, const Point<T>& B, const Point<T>& C) {
  Point<T> b = C-A, c = B-A;  
  return A + (b*c.dist2() - c*b.dist2()).perp() / b.cross(c) / 2;
} 

// MinimumEnclosingCircle
// Computes the minimum circle that encloses a set of points
// Time: O(n)
// 
// T: preferably double, long doubles
template<class T>
pair<Point<T>, T> mec(vector<Point<T>> ps) {
  shuffle(ps.begin(), ps.end(), mt19937(time(0)));
  Point<T> o = ps[0];
  T r = 0, EPS = 1 + 1e-8;
  for (int i = 0; i < (int) ps.size(); i++) {
    if ((o - ps[i]).dist() > r * EPS) {
      o = ps[i], r = 0;
      for (int j = 0; j < i; j++) {
        if ((o - ps[j]).dist() > r * EPS) {
          o = (ps[i] + ps[j]) / 2;
          r = (o - ps[i]).dist();
          for (int k = 0; k < j; k++) {
            if ((o - ps[k]).dist() > r * EPS) {
              o = ccCenter(ps[i], ps[j], ps[k]);
              r = (o - ps[i]).dist();
            }
          } 
        }     
      }
    }  
  }
  return {o, r};
}


/// POLYGONS

// InsidePolygon
// Returns true if p lies within the polygon. If strict is true, it
// returns false for points on the boundary. The algorithm uses products
// in intermediate steps so watch out for overflow.
//
// Usage:
// Point<double> p1 {4, 4}, p2 {1, 3}, p3 {2, 1};
// vector<Point<double>> v = { p1, p2, p3 };
// Point<double> q {3, 3}
// bool in = inPolygon(v, q, false);
template<class T>
bool inPolygon(vector<Point<T>> &p, Point<T>& a, bool strict = true) {
  int cnt = 0, n = p.size();
  for (int i = 0; i < n; i++) {
    Point<T> q = p[(i+1) % n];
    if (onSegment(p[i], q, a)) return !strict;
    // or: if (segDist(p[i], q, a) <= eps) return !strict;
    cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
  }
  return cnt;
} 

// PolygonArea
// Returns twice the signed area of a polygon. 
// Clockwise enumeration gives negative ares.
// Watch out overflow in using int T as T
template<class T>
T polygonArea2(vector<Point<T>>& v) {
  T a = v.back().cross(v[0]);
  for (int i = 0; i < (int) v.size() - 1; i++) {
    a += v[i].cross(v[i+1]);
  } 
  return a;
}

// PolygonCenter
// Returns the center of mass for a polygon
template<class T>
Point<T> polygonCenter(const vector<Point<T>>& v) {
  Point<T> res {0, 0};
  T A = 0;
  for (int i = 0, j = (int) v.size() - 1; i < (int) v.size(); j = i++) {
    res = res + (v[i] + v[j]) * v[j].cross(v[i]);
    A += v[j].cross(v[i]);
  } 
  return res / A / 3;
}

// PolygonCut
// Returns a vector with the vertices of a polygon with everything to the 
// left of of the line going from s to e cut away.
//
// Usage: 
// vector<Point<T> p = ...;
// p = polygonCut(p, P(0, 0), P(1, 0));
template<class T>
vector<Point<T>> polygonCut (const vector<Point<T>>& poly, Point<T>& s, Point<T>& e) {
  vector<Point<T>> res;
  for (int i = 0; i < (int) poly.size(); i++) {
    Point<T> cur = poly[i], prev = i ? poly[i-1] : poly.back();
    bool side = s.cross(e, cur) < 0;
    if (side != (s.cross(e, prev) < 0)) {
      res.push_back(lineInter(s, e, cur, prev).second);  
    }
    if (side) res.push_back(cur);
  } 
  return res;
}

// ConvexHull
// Returns a vector of the points of the convex hull in counter-clockwise order
// Points on the edge of the hull between two other points are
// not considered part of the hull
// Time: O(nlogn)
template<class T>
vector<Point<T>> convexHull (vector<Point<T>> pts) {
  if (pts.size() <= 1) return pts;
  sort(pts.begin(), pts.end());
  vector<Point<T>> h (pts.size() + 1);
  int s = 0, t = 0;
  for (int it = 2; it--; s = --t, reverse(pts.begin(), pts.end())) {
    for (Point<T> p : pts) {
      while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
      h[t++] = p;
    }
  }
  return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])}; 
}

// Hull Diameter
// Returns the two points with max distance on a convex hull
template<class T>
array<Point<T>, 2> hullDiameter(vector<Point<T>> S) {
  int n = S.size(), j = n < 2 ? 0 : 1;
  pair<T, array<Point<T>, 2>> res ({0, {S[0], S[0]}});
  for (int i = 0; i < j; i++) {
    for (;; j = (j+1) % n) {
      res = max(res, {(S[i] - S[j]).dist2(), {S[i], S[j]}});
      if ((S[(j+1) % n] - S[j]).cross(S[i+1] - S[i]) >= 0) break;
    }
  }
  return res.second;
}

// PointsInsideHull
// Determine whether a point t lies inside a convex hull (CCW order, 
// with no collinear points). Returns true if point lies within the hull.
// If strict is true, points on the boundary aren't included.
// Time: O(log N)
template<class T>
bool inHull(const vector<Point<T>>& l, Point<T> p, bool strict = true) {
  int a = 1, b = l.size() - 1, r = !strict;
  if (l.size() < 3) return r && onSegment(l[0], l.back(), p);
  if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
  if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p) <= -r) return false;
  while (abs(a-b) > 1) {
    int c = (a+b) / 2;
    (sideOf(l[0], l[c], p) > 0 ? b : a) = c;
  }
  return sng(l[a].cross(l[b], p)) < r;
}

// LineHullIntersection
// Line-convex polygon intersection. The polygon must be ccw
// and have no colinear points. lineHull(line, poly) returns a
// pair describing the intersection of a line with polygon:
// (-1, -1) if no collision, (i, -1) if touching the corner i
// (i, i) if along size (i, i+1), (i, j) if crossing sides (i, i+1)
// and (j, j+1). In the last case, if a corner i is crossed, this
// is treated as happening on side (i, i+1). The points are returned
// in the same order as the line hits the polygon. extrVertex returns 
// the point of a hull with the max projection onto a line.
// Time: O(N + Qlogn)
#define cmp(i, j) sng(dir.perp().cross(poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i+1, i) >= 0 && cmp(i, i-1+n) < 0
template<class T>
int extrVertex(vector<Point<T>>& poly, Point<T> dir) {
  int n = poly.size(), lo = 0, hi = n;
  if (extr(0)) return 0;
  while (lo + 1 < hi) {
    int m = (lo + hi) / 2;
    if (extr(m)) return m;
    int ls = cmp(lo+1, lo), ms = cmp(m+1, m);
    (ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
  }
  return lo;
}
#define cmpL(i) sng(a.cross(poly[i], b))
template<class T>
array<T, 2> lineHull(Point<T> a, Point<T> b, vector<Point<T>> poly) {
  int endA = extrVertex(poly, (a-b).perp());
  int endB = extrVertex(poly, (b-a).perp());
  if (cmpL(endA) < 0 || cmpL(endB) > 0) return {-1, -1};
  array<T, 2> res;
  for (int i = 0; i < 2; i++) {
    int lo = endB, hi = endA, n = poly.size();
    while ((lo+1) % n != hi) {
      int m = ((lo+hi + (lo < hi ? 0 : n)) / 2) % n;
      (cmpL(m) == cmpL(endB) ? lo : hi) = m;
    }
    res[i] = (lo + !cmpL(hi)) % n;
    swap(endA, endB);
  }
  if (res[0] == res[1]) return { res[0], -1 };
  if (!cmpL(res[0]) && !cmpL(res[1])) {
    switch((res[0] - res[1] + poly.size() + 1) % poly.size()) {
      case 0: return { res[0], res[0] };
      case 2: return { res[1], res[1] };
    }
  }
  return res;
}

///

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Point<int64_t> s1 {0, 0}, e1 {5, 5}, s2{3, 3}, e2 {5, 0}, s {1, -1}, e {1, 6};
  vector<Point<int64_t>> f {s1, s2, e1, e2, s, e};
  vector<Point<int64_t>> hul = convexHull(f);
  auto res = lineHull(s1, e1, hul);
  cout << res[0] << " " << res[1] << endl;
  return 0;
}

