#ifndef LOTATEPOLYHEDRON_SHAPE_HPP_
#define LOTATEPOLYHEDRON_SHAPE_HPP_

#include <memory>
#include <vector>

#include "dot.hpp"
#include "fixed_point.hpp"
#include "line.hpp"

namespace lotate_polyhedron {

template <typename FloatType, typename IteratorType>
class LineIterator {
 private:
  using DotType = Dot<FloatType>;
  using LineType = Line<FloatType>;

 public:
  explicit LineIterator(void) {}
  explicit LineIterator(const LineIterator& li) = delete;

  virtual IteratorType& operator++(void) = 0;
  virtual IteratorType operator++(int junk) = 0;

  virtual bool operator==(const IteratorType& li) const = 0;
  virtual bool operator!=(const IteratorType& li) const = 0;

  virtual LineType operator*(void) const = 0;
  virtual std::unique_ptr<LineType> operator->(void) const = 0;
};

template <typename FloatType, typename IteratorType>
class Shape {
 protected:
  using DotType = Dot<FloatType>;
  using LineType = Line<FloatType>;

 public:
  explicit Shape(void) = delete;

 protected:
  explicit Shape(size_t dot_count, size_t line_count)
      : dot_count_(dot_count), line_count_(line_count) {}

  Shape(const Shape& shape)
      : dot_count_(shape.dot_count_), line_count_(shape.line_count_) {}

 public:
  virtual IteratorType begin(void) const = 0;
  virtual IteratorType end(void) const = 0;

  inline size_t GetDotCount(void) const { return dot_count_; }
  inline size_t GetLineCount(void) const { return line_count_; }

  virtual void LotateAroundXAxis(const FloatType& angle) = 0;
  virtual void LotateAroundYAxis(const FloatType& angle) = 0;
  virtual void LotateAroundZAxis(const FloatType& angle) = 0;

 protected:
  const size_t dot_count_;
  const size_t line_count_;
};

}  // namespace lotate_polyhedron

#endif