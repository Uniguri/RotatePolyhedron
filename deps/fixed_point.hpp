#ifndef FIXEDPOINT_FIXED_POINT_HPP_
#define FIXEDPOINT_FIXED_POINT_HPP_

// Reference: http://www.sunshine2k.de/articles/coding/fp/sunfp.html

#include <cassert>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

namespace fixed_point {

namespace utility {
constexpr inline uint64_t Factorial(const uint64_t n) {
  if (n <= 2) {
    return n;
  }
  return n * Factorial(n - 1llu);
}
}  // namespace utility

template <uint32_t NUMBER_OF_FRACTION_BITS = 16>
class FixedPoint {
 public:
  static const uint32_t kNumberOfFractionBits = NUMBER_OF_FRACTION_BITS;
  static const uint64_t kFractionMask = (1llu << kNumberOfFractionBits) - 1;
  static const uint64_t kConversionFactor = (1llu << kNumberOfFractionBits);

  static constexpr FixedPoint kFixedPi{3.1415926535897932384626433832795};

  constexpr explicit FixedPoint(void) : value_(0) {}

  constexpr explicit FixedPoint(int32_t value)
      : FixedPoint(static_cast<int64_t>(value)) {}
  constexpr explicit FixedPoint(int64_t value)
      : value_(value << kNumberOfFractionBits) {}

  constexpr explicit FixedPoint(float value)
      : FixedPoint(static_cast<double>(value)) {}
  constexpr explicit FixedPoint(double value)
      : value_(static_cast<int64_t>(value * kConversionFactor)) {}

  constexpr FixedPoint(const FixedPoint& fp) : value_(fp.value_) {}
  constexpr FixedPoint(FixedPoint&& fp) : value_(fp.value_) {}

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

  constexpr inline int64_t ToInt64(void) const {
    return (value_ >> kNumberOfFractionBits);
  }

  inline std::string ToString(void) const {
    std::stringstream ss;
    ss << ToDouble();
    return ss.str();
  }

  constexpr inline operator int32_t() const {
    return static_cast<int32_t>(ToInt64());
  }

  constexpr inline operator int64_t() const { return ToInt64(); }

  constexpr inline operator float() const {
    return static_cast<float>(ToDouble());
  }

  constexpr inline operator double() const { return ToDouble(); }

  constexpr inline bool operator<(const FixedPoint& rhs) const {
    return value_ < rhs.value_;
  }

  constexpr inline bool operator<=(const FixedPoint& rhs) const {
    return value_ <= rhs.value_;
  }

  constexpr inline bool operator>(const FixedPoint& rhs) const {
    return value_ > rhs.value_;
  }

  constexpr inline bool operator>=(const FixedPoint& rhs) const {
    return value_ >= rhs.value_;
  }

  constexpr inline bool operator==(const FixedPoint& rhs) const {
    return value_ == rhs.value_;
  }

  constexpr inline bool operator!=(const FixedPoint& rhs) const {
    return value_ != rhs.value_;
  }

  constexpr inline FixedPoint& operator=(const FixedPoint& rhs) {
    value_ = rhs.value_;
    return *this;
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
    value_ += (integer_part1 * fraction_part2);
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
#if FIXED_POINT_USE_FAST_OPERATION == 1
    value_ = (value_ << kNumberOfFractionBits) / rhs.value_;
#else
    const FixedPoint temp =
        FromRawValue((1llu << (2 * kNumberOfFractionBits - 1)) / rhs.value_) *
        (*this);
    value_ = temp.value_ << 1;
#endif
    return *this;
  }

  constexpr inline FixedPoint operator/(const FixedPoint& rhs) const {
    return FixedPoint(*this) /= rhs;
  }

  template <typename F>
  constexpr inline bool operator<(const F& rhs) const {
    return value_ < FixedPoint(rhs);
  }

  template <typename F>
  constexpr inline bool operator<=(const F& rhs) const {
    return value_ <= FixedPoint(rhs);
  }

  template <typename F>
  constexpr inline bool operator>(const F& rhs) const {
    return value_ > FixedPoint(rhs);
  }

  template <typename F>
  constexpr inline bool operator>=(const F& rhs) const {
    return value_ >= FixedPoint(rhs);
  }

  template <typename F>
  constexpr inline bool operator==(const F& rhs) const {
    return value_ == FixedPoint(rhs);
  }

  template <typename F>
  constexpr inline bool operator!=(const F& rhs) const {
    return value_ != FixedPoint(rhs);
  }

  template <typename F>
  constexpr inline FixedPoint& operator+=(const F& rhs) {
    return *this += FixedPoint(rhs);
  }

  template <typename F>
  constexpr inline FixedPoint operator+(const F& rhs) const {
    return FixedPoint(*this) += rhs;
  }

  template <typename F>
  constexpr inline FixedPoint& operator-=(const F& rhs) {
    return *this -= FixedPoint(rhs);
  }

  template <typename F>
  constexpr inline FixedPoint operator-(const F& rhs) const {
    return FixedPoint(*this) -= rhs;
  }

  template <typename F>
  constexpr inline FixedPoint& operator*=(const F& rhs) {
    return *this *= FixedPoint(rhs);
  }

  template <int32_t>
  constexpr inline FixedPoint& operator*=(int32_t rhs) {
    return *this *= static_cast<int64_t>(rhs);
  }

  template <int64_t>
  constexpr inline FixedPoint& operator*=(int64_t rhs) {
#if FIXED_POINT_USE_FAST_OPERATION == 1
    value_ = (value_ * rhs);
#else
    const int64_t integer_part1 = value_ >> kNumberOfFractionBits;
    const int64_t integer_part2 = rhs;
    const int64_t fraction_part1 = value_ & kFractionMask;

    value_ = 0;
    value_ += (integer_part1 * integer_part2) << kNumberOfFractionBits;
    value_ += (fraction_part1 * integer_part2);
#endif
    return *this;
  }

  template <typename F>
  constexpr inline FixedPoint operator*(const F& rhs) const {
    return FixedPoint(*this) *= rhs;
  }

  template <int32_t>
  constexpr inline FixedPoint operator*(int32_t rhs) const {
    return FixedPoint(*this) *= rhs;
  }

  template <int64_t>
  constexpr inline FixedPoint operator*(int64_t rhs) const {
    return FixedPoint(*this) *= rhs;
  }

  template <typename F>
  constexpr inline FixedPoint& operator/=(const F& rhs) {
    return *this /= FixedPoint(rhs);
  }

  template <int32_t>
  constexpr inline FixedPoint& operator/=(int32_t rhs) {
    return *this /= static_cast<int64_t>(rhs);
  }

  template <int64_t>
  constexpr inline FixedPoint& operator/=(int64_t rhs) {
    value_ /= rhs;
    return *this;
  }

  template <typename F>
  constexpr inline FixedPoint operator/(const F& rhs) const {
    return FixedPoint(*this) /= rhs;
  }

  template <int32_t>
  constexpr inline FixedPoint operator/(int32_t rhs) const {
    return FixedPoint(*this) /= rhs;
  }

  template <int64_t>
  constexpr inline FixedPoint operator/(int64_t rhs) const {
    return FixedPoint(*this) /= rhs;
  }

  constexpr inline FixedPoint operator-() const {
    FixedPoint temp{*this};
    temp.value_ *= -1;
    return temp;
  }

  constexpr inline FixedPoint& operator++() {
    *this += 1;
    return *this;
  }

  constexpr inline FixedPoint operator++(int junk) {
    FixedPoint temp{*this};
    *this += 1;
    return temp;
  }

  constexpr inline FixedPoint& operator--() {
    *this -= 1;
    return *this;
  }

  constexpr inline FixedPoint operator--(int junk) {
    FixedPoint temp{*this};
    *this -= 1;
    return temp;
  }

  constexpr inline static FixedPoint floor(const FixedPoint& fp) {
    return FixedPoint{fp.ToInt64()};
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

  constexpr inline static FixedPoint sin(const FixedPoint& fp) {
    assert(-kFixedPi <= fp && fp <= kFixedPi);
    constexpr int64_t fact3 = static_cast<int64_t>(utility::Factorial(3));
    constexpr int64_t fact5 = static_cast<int64_t>(utility::Factorial(5));
    constexpr int64_t fact7 = static_cast<int64_t>(utility::Factorial(7));
    constexpr int64_t fact9 = static_cast<int64_t>(utility::Factorial(9));

    FixedPoint res{fp};
    res -= FixedPoint::pow(fp, 3) / fact3;
    res += FixedPoint::pow(fp, 5) / fact5;
    res -= FixedPoint::pow(fp, 7) / fact7;
    res += FixedPoint::pow(fp, 9) / fact9;
    return res;
  }

  constexpr inline static FixedPoint cos(const FixedPoint& fp) {
    assert(-kFixedPi <= fp && fp <= kFixedPi);
    constexpr int64_t fact2 = static_cast<int64_t>(utility::Factorial(2));
    constexpr int64_t fact4 = static_cast<int64_t>(utility::Factorial(4));
    constexpr int64_t fact6 = static_cast<int64_t>(utility::Factorial(6));
    constexpr int64_t fact8 = static_cast<int64_t>(utility::Factorial(8));

    FixedPoint res{1};
    res -= FixedPoint::pow(fp, 2) / fact2;
    res += FixedPoint::pow(fp, 4) / fact4;
    res -= FixedPoint::pow(fp, 6) / fact6;
    res += FixedPoint::pow(fp, 7) / fact8;
    return res;
  }

  constexpr inline static FixedPoint tan(const FixedPoint& fp) {
    assert(-kFixedPi <= fp && fp <= kFixedPi);
    const FixedPoint& sin = FixedPoint::sin(fp);
    const FixedPoint& cos = FixedPoint::cos(fp);
    assert(cos != FixedPoint(0));
    return sin / cos;
  }

  constexpr inline static FixedPoint artanh(const FixedPoint& fp) {
    constexpr FixedPoint factorial3(
        static_cast<int64_t>(utility::Factorial(3)));
    constexpr FixedPoint factorial5(
        static_cast<int64_t>(utility::Factorial(5)));
    constexpr FixedPoint factorial7(
        static_cast<int64_t>(utility::Factorial(7)));
    constexpr FixedPoint factorial9(
        static_cast<int64_t>(utility::Factorial(9)));

    FixedPoint res{fp};
    res += FixedPoint::pow(fp, 3) / factorial3;
    res += FixedPoint::pow(fp, 5) / factorial5;
    res += FixedPoint::pow(fp, 7) / factorial7;
    res += FixedPoint::pow(fp, 9) / factorial9;
    return res;
  }

  constexpr static FixedPoint exp(const FixedPoint& fp) {
    FixedPoint ret(1);
    for (int i = 1; i <= 14; ++i) {
      const FixedPoint fact(static_cast<int64_t>(utility::Factorial(i)));
      const FixedPoint power(FixedPoint::pow(fp, i));
      ret += (power / fact);
    }
    return ret;
  }

  constexpr static FixedPoint pow(const FixedPoint& fp, unsigned int n) {
    if (n == 0) {
      return FixedPoint{1};
    } else {
      FixedPoint res{fp};
      for (unsigned int i = 0; i < n - 1; ++i) {
        res *= fp;
      }
      return res;
    }
  }

  constexpr inline static FixedPoint log(const FixedPoint& fp) {
    assert(FixedPoint(0) <= fp);
    return FixedPoint(2) * FixedPoint::artanh(fp);
  }

  constexpr static FixedPoint sqrt(const FixedPoint& fp) {
    FixedPoint res{1};
    constexpr FixedPoint error{0.001};
    int i = 0;
    while ((i < 10) && (FixedPoint::abs(res * res - fp) >= error)) {
      res = FixedPoint(0.5) * (res + fp / res);
    }
    return res;
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

template <uint32_t NUMBER_OF_FRACTION_BITS>
constexpr inline FixedPoint<NUMBER_OF_FRACTION_BITS> floor(
    const FixedPoint<NUMBER_OF_FRACTION_BITS>& fp) {
  return FixedPoint<NUMBER_OF_FRACTION_BITS>::floor(fp);
}

template <uint32_t NUMBER_OF_FRACTION_BITS>
constexpr inline FixedPoint<NUMBER_OF_FRACTION_BITS> ceil(
    const FixedPoint<NUMBER_OF_FRACTION_BITS>& fp) {
  return FixedPoint<NUMBER_OF_FRACTION_BITS>::ceil(fp);
}

template <uint32_t NUMBER_OF_FRACTION_BITS>
constexpr inline FixedPoint<NUMBER_OF_FRACTION_BITS> round(
    const FixedPoint<NUMBER_OF_FRACTION_BITS>& fp) {
  return FixedPoint<NUMBER_OF_FRACTION_BITS>::round(fp);
}

template <uint32_t NUMBER_OF_FRACTION_BITS>
constexpr inline FixedPoint<NUMBER_OF_FRACTION_BITS> abs(
    const FixedPoint<NUMBER_OF_FRACTION_BITS>& fp) {
  return FixedPoint<NUMBER_OF_FRACTION_BITS>::abs(fp);
}

template <uint32_t NUMBER_OF_FRACTION_BITS>
constexpr inline FixedPoint<NUMBER_OF_FRACTION_BITS> sin(
    const FixedPoint<NUMBER_OF_FRACTION_BITS>& fp) {
  return FixedPoint<NUMBER_OF_FRACTION_BITS>::sin(fp);
}

template <uint32_t NUMBER_OF_FRACTION_BITS>
constexpr inline FixedPoint<NUMBER_OF_FRACTION_BITS> cos(
    const FixedPoint<NUMBER_OF_FRACTION_BITS>& fp) {
  return FixedPoint<NUMBER_OF_FRACTION_BITS>::cos(fp);
}

template <uint32_t NUMBER_OF_FRACTION_BITS>
constexpr inline FixedPoint<NUMBER_OF_FRACTION_BITS> tan(
    const FixedPoint<NUMBER_OF_FRACTION_BITS>& fp) {
  return FixedPoint<NUMBER_OF_FRACTION_BITS>::tan(fp);
}

template <uint32_t NUMBER_OF_FRACTION_BITS>
constexpr inline FixedPoint<NUMBER_OF_FRACTION_BITS> exp(
    const FixedPoint<NUMBER_OF_FRACTION_BITS>& fp) {
  return FixedPoint<NUMBER_OF_FRACTION_BITS>::exp(fp);
}

template <uint32_t NUMBER_OF_FRACTION_BITS>
constexpr inline FixedPoint<NUMBER_OF_FRACTION_BITS> pow(
    const FixedPoint<NUMBER_OF_FRACTION_BITS>& fp, unsigned int n) {
  return FixedPoint<NUMBER_OF_FRACTION_BITS>::pow(fp, n);
}

template <uint32_t NUMBER_OF_FRACTION_BITS>
constexpr inline FixedPoint<NUMBER_OF_FRACTION_BITS> log(
    const FixedPoint<NUMBER_OF_FRACTION_BITS>& fp) {
  return FixedPoint<NUMBER_OF_FRACTION_BITS>::log(fp);
}

template <uint32_t NUMBER_OF_FRACTION_BITS>
constexpr inline FixedPoint<NUMBER_OF_FRACTION_BITS> sqrt(
    const FixedPoint<NUMBER_OF_FRACTION_BITS>& fp) {
  return FixedPoint<NUMBER_OF_FRACTION_BITS>::sqrt(fp);
}

}  // namespace fixed_point

#endif