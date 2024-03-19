#ifndef thisLOTATEPOLYHEDRON_DOT_HPP_
#define thisLOTATEPOLYHEDRON_DOT_HPP_

#include <cmath>
#include <sstream>

#include "fixed_point.hpp"

namespace lotate_polyhedron {

template <typename T>
struct Dot {
  T x, y, z;
  constexpr static T kPi{3.14159265359};

  constexpr explicit Dot(void) : x(T()), y(T()), z(T()) {}
  constexpr explicit Dot(int32_t x, int32_t y, int32_t z)
      : x(T(x)), y(T(y)), z(T(z)) {}
  constexpr explicit Dot(int64_t x, int64_t y, int64_t z)
      : x(T(x)), y(T(y)), z(T(z)) {}
  constexpr explicit Dot(float x, float y, float z)
      : x(T(x)), y(T(y)), z(T(z)) {}
  constexpr explicit Dot(double x, double y, double z)
      : x(T(x)), y(T(y)), z(T(z)) {}
  constexpr explicit Dot(const T& x, const T& y, const T& z)
      : x(x), y(y), z(z) {}

  constexpr Dot(const Dot& dot) : x(dot.x), y(dot.y), z(dot.z) {}

  constexpr inline Dot round(void) const {
    return Dot(round(x), round(y), round(z));
  }

  constexpr inline Dot floor(void) const {
    return Dot(floor(x), floor(y), floor(z));
  }

  constexpr inline Dot ceil(void) const {
    return Dot(ceil(x), ceil(y), ceil(z));
  }

  constexpr inline Dot& LotateAroundXAxisSelf(T angle) {
    if (abs(angle) >= kPi) {
      angle /= kPi;
    }
    const T new_y = y * cos(angle) - z * sin(angle);
    const T new_z = y * sin(angle) + z * cos(angle);
    y = new_y;
    z = new_z;
    return *this;
  }

  constexpr inline Dot LotateAroundXAxis(T angle) const {
    return Dot(*this).LotateAroundXAxisSelf(angle);
  }

  constexpr inline Dot LotateAroundYAxisSelf(T angle) {
    if (abs(angle) >= kPi) {
      angle /= kPi;
    }
    const T new_x = x * cos(angle) + z * sin(angle);
    const T new_z = -x * sin(angle) + z * cos(angle);
    x = new_x;
    z = new_z;
    return *this;
  }

  constexpr inline Dot LotateAroundYAxis(T angle) const {
    return Dot(*this).LotateAroundYAxisSelf(angle);
  }

  constexpr inline Dot LotateAroundZAxisSelf(T angle) {
    if (abs(angle) >= kPi) {
      angle /= kPi;
    }
    const T new_x = x * cos(angle) - y * sin(angle);
    const T new_y = x * sin(angle) + y * cos(angle);
    x = new_x;
    y = new_y;
    return *this;
  }

  constexpr inline Dot LotateAroundZAxis(T angle) const {
    return Dot(*this).LotateAroundZAxisSelf(angle);
  }

  constexpr inline Dot ElementWiseMultiplication(const Dot& rhs) const {
    return Dot{x * rhs.x, y * rhs.y, z * rhs.z};
  }

  constexpr inline T DotProduct(const Dot& rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }

  constexpr inline bool operator==(const Dot& rhs) {
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
  }

  constexpr inline Dot& operator=(const Dot& rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }

  constexpr inline Dot& operator+=(const Dot& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  constexpr inline Dot operator+(const Dot& rhs) const {
    return Dot(*this) += rhs;
  }

  constexpr inline Dot& operator-=(const Dot& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  constexpr inline Dot operator-(const Dot& rhs) const {
    return Dot(*this) -= rhs;
  }

  constexpr inline Dot& operator*=(const T& rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
  }

  constexpr inline Dot operator*(const T& rhs) const {
    return Dot(*this) *= rhs;
  }

  constexpr inline Dot& operator/=(const T& rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
  }

  constexpr inline Dot operator/(const T& rhs) const {
    return Dot(*this) /= rhs;
  }

  template <typename F>
  constexpr inline Dot<T>& operator*=(const F& rhs) {
    x *= T(rhs);
    y *= T(rhs);
    z *= T(rhs);
    return *this;
  }

  template <typename F>
  constexpr inline Dot<T> operator*(const F& rhs) const {
    return Dot(*this) *= T(rhs);
  }

  template <typename F>
  constexpr inline Dot<T>& operator/=(const F& rhs) {
    x /= T(rhs);
    y /= T(rhs);
    z /= T(rhs);
    return *this;
  }

  template <typename F>
  constexpr inline Dot<T> operator/(const F& rhs) const {
    return Dot(*this) /= T(rhs);
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