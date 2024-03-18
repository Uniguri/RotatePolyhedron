#ifndef LOTATEPOLYHEDRON_DOT_H_
#define LOTATEPOLYHEDRON_DOT_H_

#include <sstream>

#include "fixed_point.hpp"

namespace lotate_polyhedron {

template <typename T = FixedPoint<32>>
struct Dot {
  T x, y, z;

  constexpr explicit Dot(void) : x(0), y(0), z(0) {}
  constexpr Dot(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}

  constexpr explicit Dot(const Dot& dot) : x(dot.x), y(dot.y), z(dot.z) {}
  constexpr explicit Dot(Dot&& dot)
      : x(std::move(dot.x)), y(std::move(dot.y)), z(std::move(dot.z)) {}

  constexpr inline Dot& operator+=(const Dot& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  constexpr inline Dot operator+(const Dot& rhs) const {
    return Dot{x + rhs.x, y + rhs.y, z + rhs.z};
  }

  constexpr inline Dot& operator-=(const Dot& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  constexpr inline Dot operator-(const Dot& rhs) const {
    return Dot{x - rhs.x, y - rhs.y, z - rhs.z};
  }

  constexpr inline Dot& operator*(const T& rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
  }

  constexpr inline Dot operator*(const T& rhs) const {
    return Dot{x * rhs, y * rhs, z * rhs};
  }

  constexpr inline Dot ElementWiseMultiplication(const Dot& rhs) const {
    return Dot{x * rhs.x, y * rhs.y, z * rhs.z};
  }

  constexpr inline T DotProduct(const Dot& rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }

  friend std::ostream& operator<<(std::ostream& os, const Dot& dot) {
    std::stringstream ss;
    ss << '(' << dot.x << ", " << dot.y << ", " << dot.z << ')';
    os << ss.str();
    return os;
  }
};

}  // namespace lotate_polyhedron

#endif