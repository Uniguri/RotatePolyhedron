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

  DotType dot1_, dot2_;

  constexpr static FloatType kPi = FloatType(3.14159265359);

  constexpr explicit Line() : dot1_(), dot2_() {}

  constexpr explicit Line(int64_t x0, int64_t y0, int64_t z0, int64_t x1,
                          int64_t y1, int64_t z1)
      : dot1_(DotType(FloatType(x0), FloatType(y0), FloatType(z0))),
        dot2_(DotType(FloatType(x1), FloatType(y1), FloatType(z1))) {}
  constexpr explicit Line(int32_t x0, int32_t y0, int32_t z0, int32_t x1,
                          int32_t y1, int32_t z1)
      : dot1_(DotType(FloatType(x0), FloatType(y0), FloatType(z0))),
        dot2_(DotType(FloatType(x1), FloatType(y1), FloatType(z1))) {}
  constexpr explicit Line(double x0, double y0, double z0, double x1, double y1,
                          double z1)
      : dot1_(DotType(FloatType(x0), FloatType(y0), FloatType(z0))),
        dot2_(DotType(FloatType(x1), FloatType(y1), FloatType(z1))) {}
  constexpr explicit Line(FloatType x0, FloatType y0, FloatType z0,
                          FloatType x1, FloatType y1, FloatType z1)
      : dot1_(DotType(x0, y0, z0)), dot2_(DotType(x1, y1, z1)) {}
  constexpr explicit Line(const DotType& dot1, const DotType& dot2)
      : dot1_(dot1), dot2_(dot2) {}
  constexpr explicit Line(DotType&& dot1, DotType&& dot2)
      : dot1_(std::move(dot1)), dot2_(std::move(dot2)) {}

  constexpr Line(const Line& line) : dot1_(line.dot1_), dot2_(line.dot2_) {}
  constexpr Line(Line&& line)
      : dot1_(std::move(line.dot1_)), dot2_(std::move(line.dot2_)) {}

  template <typename T>
  constexpr inline Line LotateAroundXAxisSelf(const T& angle) {
    dot1_.LotateAroundXAxisSelf(angle);
    dot2_.LotateAroundXAxisSelf(angle);
    return *this;
  }

  template <typename T>
  constexpr inline Line LotateAroundXAxis(const T& angle) const {
    return Line(*this).LotateAroundXAxisSelf(angle);
  }

  template <typename T>
  constexpr inline Line LotateAroundYAxisSelf(const T& angle) {
    dot1_.LotateAroundYAxisSelf(angle);
    dot2_.LotateAroundYAxisSelf(angle);
    return *this;
  }

  template <typename T>
  constexpr inline Line LotateAroundYAxis(const T& angle) const {
    return Line(*this).LotateAroundYAxisSelf(angle);
  }

  template <typename T>
  constexpr inline Line LotateAroundZAxisSelf(const T& angle) {
    dot1_.LotateAroundZAxisSelf(angle);
    dot2_.LotateAroundZAxisSelf(angle);
    return *this;
  }

  template <typename T>
  constexpr inline Line LotateAroundZAxis(const T& angle) const {
    return Line(*this).LotateAroundZAxisSelf(angle);
  }

  constexpr inline bool operator==(const Line& rhs) {
    return (dot1_ == rhs.dot1_) && (dot2_ == rhs.dot2_);
  }

  constexpr inline Line& operator+=(const Line& rhs) {
    dot1_ += rhs.dot1_;
    dot2_ += rhs.dot2_;
    return *this;
  }

  constexpr inline Line operator+(const Line& rhs) const {
    return Line(*this) += rhs;
  }

  constexpr inline Line& operator-=(const Line& rhs) {
    dot1_ -= rhs.dot1_;
    dot2_ -= rhs.dot2_;
    return *this;
  }

  constexpr inline Line operator-(const Line& rhs) const {
    return Line(*this) -= rhs;
  }

  template <typename F>
  constexpr inline Line& operator*=(const F& rhs) {
    dot1_ *= FloatType(rhs);
    dot2_ *= FloatType(rhs);
    return *this;
  }

  template <typename F>
  constexpr inline Line operator*(const F& rhs) const {
    return Line(*this) *= rhs;
  }

  template <typename F>
  constexpr inline Line& operator/=(const F& rhs) {
    dot1_ /= FloatType(rhs);
    dot2_ /= FloatType(rhs);
    return *this;
  }

  template <typename F>
  constexpr inline Line operator/(const F& rhs) const {
    return Line(*this) /= rhs;
  }

  friend std::ostream& operator<<(std::ostream& os, const Line& line) {
    std::stringstream ss;
    ss << '<' << line.dot1_ << " - " << line.dot2_ << '>';
    os << ss.str();
    return os;
  }
};

}  // namespace lotate_polyhedron

#endif