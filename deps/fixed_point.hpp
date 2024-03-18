#ifndef FIXEDPOINT_FIXED_POINT_HPP_
#define FIXEDPOINT_FIXED_POINT_HPP_

// Reference: http://www.sunshine2k.de/articles/coding/fp/sunfp.html

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

namespace fixed_point {

template <uint32_t NUMBER_OF_FRACTION_BITS = 16>
class FixedPoint {
 public:
  static const uint32_t kNumberOfFractionBits = NUMBER_OF_FRACTION_BITS;
  static const uint64_t kFractionMask = (1 << kNumberOfFractionBits) - 1;
  static const uint64_t kConversionFactor = (1 << kNumberOfFractionBits);

  constexpr FixedPoint(void) : value_(0) {}

  constexpr FixedPoint(int64_t value)
      : value_(value << kNumberOfFractionBits) {}
  constexpr FixedPoint(double value)
      : value_(static_cast<int64_t>(value * kConversionFactor)) {}

  constexpr FixedPoint(const FixedPoint& fp) : value_(fp.value_) {}

  inline static FixedPoint FromString(const std::string& s) {
    std::stringstream ss(s);
    double d;
    ss >> d;
    return FixedPoint(d);
  }

 private:
  constexpr FixedPoint(int64_t integer_part, int64_t fraction_part)
      : value_((integer_part << kNumberOfFractionBits) | fraction_part) {}

  constexpr inline static FixedPoint FromRawValue(int64_t raw_value) {
    FixedPoint ret;
    ret.value_ = raw_value;
    return ret;
  }

 public:
  constexpr inline double ToDouble(void) const {
    return static_cast<double>(value_) / kConversionFactor;
  }

  inline std::string ToString(void) const {
    std::stringstream ss;
    ss << ToDouble();
    return ss.str();
  }

  constexpr inline operator int32_t() const {
    return static_cast<int64_t>(*this);
  }

  constexpr inline operator int64_t() const {
    return value_ >> kNumberOfFractionBits;
  }

  constexpr inline operator float() const { return static_cast<double>(*this); }

  constexpr inline operator double() const { return ToDouble(); }

  constexpr inline bool operator==(const FixedPoint& rhs) {
    return value_ == rhs.value_;
  }

  constexpr inline FixedPoint& operator+=(const FixedPoint& rhs) {
    value_ += rhs.value_;
    return *this;
  }

  constexpr inline FixedPoint operator+(const FixedPoint& rhs) const {
    return FixedPoint(*this) += rhs;
  }

  constexpr inline FixedPoint& operator-=(const FixedPoint& rhs) {
    value_ -= rhs.value_;
    return *this;
  }

  constexpr inline FixedPoint operator-(const FixedPoint& rhs) const {
    return FixedPoint(*this) -= rhs;
  }

  constexpr FixedPoint& operator*=(const FixedPoint& rhs) {
#if FIXED_POINT_USE_FAST_OPERATION == 1
    value_ = (value_ * rhs.value_) >> kNumberOfFractionBits;
#else
    const int64_t integer_part1 = value_ >> kNumberOfFractionBits;
    const int64_t integer_part2 = rhs.value_ >> kNumberOfFractionBits;
    const int64_t fraction_part1 = value_ & kFractionMask;
    const int64_t fraction_part2 = rhs.value_ & kFractionMask;

    value_ = 0;
    value_ += (integer_part1 * integer_part2) << kNumberOfFractionBits;
    value_ += (integer_part1 * fraction_part1);
    value_ += (fraction_part1 * integer_part2);
    value_ += ((fraction_part1 * fraction_part2) >> kNumberOfFractionBits) &
              kFractionMask;
#endif
    return *this;
  }

  constexpr inline FixedPoint operator*(const FixedPoint& rhs) const {
    return FixedPoint(*this) *= rhs;
  }

  constexpr inline FixedPoint& operator/=(const FixedPoint& rhs) {
    value_ = (value_ << kNumberOfFractionBits) / rhs.value_;
    return *this;
  }

  constexpr inline FixedPoint operator/(const FixedPoint& rhs) const {
    return FixedPoint(*this) /= rhs;
  }

  constexpr inline FixedPoint operator-() const {
    FixedPoint temp{*this};
    temp.value_ *= -1;
    return temp;
  }

  constexpr inline FixedPoint& operator++() {
    value_ += (1 << kNumberOfFractionBits);
    return *this;
  }

  constexpr inline FixedPoint operator++(int junk) {
    FixedPoint temp{*this};
    value_ += (1 << kNumberOfFractionBits);
    return temp;
  }

  constexpr inline FixedPoint& operator--() {
    value_ -= (1 << kNumberOfFractionBits);
    return *this;
  }

  constexpr inline FixedPoint operator--(int junk) {
    FixedPoint temp{*this};
    value_ -= (1 << kNumberOfFractionBits);
    return temp;
  }

  constexpr inline static FixedPoint floor(const FixedPoint& fp) {
    return FixedPoint{fp.value_ >> kNumberOfFractionBits};
  }

  constexpr inline static FixedPoint ceil(const FixedPoint& fp) {
    return FixedPoint{(fp.value_ + ((1 << kNumberOfFractionBits) - 1)) >>
                      kNumberOfFractionBits};
  }

  constexpr inline static FixedPoint round(const FixedPoint& fp) {
    return floor(FromRawValue(fp.value_ + (1 << (kNumberOfFractionBits - 1))));
  }

  constexpr inline static FixedPoint abs(const FixedPoint& fp) {
    return fp.value_ >= 0 ? FixedPoint{fp} : FromRawValue(-fp.value_);
  }

 private:
  int64_t value_;

  friend std::istream& operator>>(std::istream& is, FixedPoint& fp) {
    std::string s;
    is >> s;
    fp = FixedPoint::FromString(s);
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, const FixedPoint& fp) {
    os << fp.ToString();
    return os;
  }
};

}  // namespace fixed_point

#endif