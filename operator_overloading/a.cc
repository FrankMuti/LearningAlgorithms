/**
 *   author:  stein
 *   created: 2020.09.12 13:39:45
**/
#include <bits/stdc++.h>
using namespace std;

// Complex Numbers
namespace no_std {
  using std::decay_t;
  template<typename value_t>
  struct complex {
    value_t x;
    value_t y;
    complex& operator += (const value_t& x) {
      this->x += x;
      return *this;
    }
    complex& operator += (const complex& other) {
      this->x += other.x;
      this->y += other.y;
      return *this;
    }
    complex& operator -= (const value_t& x) {
      this->x -= x;
      return *this;
    }
    complex& operator -= (const complex& other) {
      this->x -= other.x;
      this->y -= other.y;
      return *this;
    }
    complex& operator *= (const value_t& s) {
      this->x *= s;
      this->y *= s;
      return *this;
    }
    complex& operator *= (const complex& other) {
      (*this) = (*this) * other;
      return *this;
    }
    complex& operator /= (const value_t& s) {
      this->x /= s;
      this->y /= s;
      return *this;
    }
    complex& operator /= (const complex& other) {
      (*this) = (*this) / other;
      return *this;
    }
    complex(const value_t_t& x, const value_t& y) : x{x}, y{y} {}
    template<typename other_value_t>
    explicit complex(const complex<other_value_t>& other) 
      : x {static_cast<const value_t&> (other.x)},
        y {static_cast<const value_t&> (other.y)} {}
    complex& operator = (const complex&) = default;
    complex& operator = (complex &&) = default;
    complex (const complex &) = default;
    complex (complex &&) = default;
    complex() = default;
  };
  
} // namespace no_std


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);


  return 0;
}
