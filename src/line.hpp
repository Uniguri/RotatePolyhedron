#ifndef LOTATEPOLYHEDRON_LINE_HPP_
#define LOTATEPOLYHEDRON_LINE_HPP_

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

#include "dot.hpp"

namespace lotate_polyhedron {

template <typename __FloatType>
struct Line {
  using FloatType = __FloatType;
  using DotType = Dot<FloatType>;

  DotType dot1, dot2;

  constexpr static FloatType kPi = FloatType(3.1415926535897932384626433832795);

  constexpr explicit Line() : dot1(), dot2() {}

  constexpr explicit Line(int64_t x0, int64_t y0, int64_t z0, int64_t x1,
                          int64_t y1, int64_t z1)
      : dot1(DotType(FloatType(x0), FloatType(y0), FloatType(z0))),
        dot2(DotType(FloatType(x1), FloatType(y1), FloatType(z1))) {}
  constexpr explicit Line(int32_t x0, int32_t y0, int32_t z0, int32_t x1,
                          int32_t y1, int32_t z1)
      : dot1(DotType(FloatType(x0), FloatType(y0), FloatType(z0))),
        dot2(DotType(FloatType(x1), FloatType(y1), FloatType(z1))) {}
  constexpr explicit Line(double x0, double y0, double z0, double x1, double y1,
                          double z1)
      : dot1(DotType(FloatType(x0), FloatType(y0), FloatType(z0))),
        dot2(DotType(FloatType(x1), FloatType(y1), FloatType(z1))) {}
  constexpr explicit Line(FloatType x0, FloatType y0, FloatType z0,
                          FloatType x1, FloatType y1, FloatType z1)
      : dot1(DotType(x0, y0, z0)), dot2(DotType(x1, y1, z1)) {}
  constexpr explicit Line(const DotType& dot1, const DotType& dot2)
      : dot1(dot1), dot2(dot2) {}
  constexpr explicit Line(DotType&& dot1, DotType&& dot2)
      : dot1(std::move(dot1)), dot2(std::move(dot2)) {}

  constexpr Line(const Line& line) : dot1(line.dot1), dot2(line.dot2) {}
  constexpr Line(Line&& line)
      : dot1(std::move(line.dot1)), dot2(std::move(line.dot2)) {}

  template <typename T>
  constexpr inline Line LotateAroundXAxisSelf(const T& angle) {
    dot1.LotateAroundXAxisSelf(angle);
    dot2.LotateAroundXAxisSelf(angle);
    return *this;
  }

  template <typename T>
  constexpr inline Line LotateAroundXAxis(const T& angle) const {
    return Line(*this).LotateAroundXAxisSelf(angle);
  }

  template <typename T>
  constexpr inline Line LotateAroundYAxisSelf(const T& angle) {
    dot1.LotateAroundYAxisSelf(angle);
    dot2.LotateAroundYAxisSelf(angle);
    return *this;
  }

  template <typename T>
  constexpr inline Line LotateAroundYAxis(const T& angle) const {
    return Line(*this).LotateAroundYAxisSelf(angle);
  }

  template <typename T>
  constexpr inline Line LotateAroundZAxisSelf(const T& angle) {
    dot1.LotateAroundZAxisSelf(angle);
    dot2.LotateAroundZAxisSelf(angle);
    return *this;
  }

  template <typename T>
  constexpr inline Line LotateAroundZAxis(const T& angle) const {
    return Line(*this).LotateAroundZAxisSelf(angle);
  }

  constexpr inline bool operator==(const Line& rhs) {
    return (dot1 == rhs.dot1) && (dot2 == rhs.dot2);
  }

  constexpr inline Line& operator+=(const Line& rhs) {
    dot1 += rhs.dot1;
    dot2 += rhs.dot2;
    return *this;
  }

  constexpr inline Line operator+(const Line& rhs) const {
    return Line(*this) += rhs;
  }

  constexpr inline Line& operator-=(const Line& rhs) {
    dot1 -= rhs.dot1;
    dot2 -= rhs.dot2;
    return *this;
  }

  constexpr inline Line operator-(const Line& rhs) const {
    return Line(*this) -= rhs;
  }

  template <typename F>
  constexpr inline Line& operator*=(const F& rhs) {
    dot1 *= FloatType(rhs);
    dot2 *= FloatType(rhs);
    return *this;
  }

  template <typename F>
  constexpr inline Line operator*(const F& rhs) const {
    return Line(*this) *= rhs;
  }

  template <typename F>
  constexpr inline Line& operator/=(const F& rhs) {
    dot1 /= FloatType(rhs);
    dot2 /= FloatType(rhs);
    return *this;
  }

  template <typename F>
  constexpr inline Line operator/(const F& rhs) const {
    return Line(*this) /= rhs;
  }

  friend std::ostream& operator<<(std::ostream& os, const Line& line) {
    std::stringstream ss;
    ss << '<' << line.dot1 << " - " << line.dot2 << '>';
    os << ss.str();
    return os;
  }
};

}  // namespace lotate_polyhedron

#endif