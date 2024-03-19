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

 protected:
  explicit Shape() {}

  Shape(const Shape& shape) {}
  Shape(Shape&& shape) {}

 public:
  virtual IteratorType begin(void) const = 0;
  virtual IteratorType end(void) const = 0;

  virtual inline size_t GetDotCount(void) const = 0;
  virtual inline size_t GetLineCount(void) const = 0;

  virtual void LotateAroundXAxis(const FloatType& angle) = 0;
  virtual void LotateAroundYAxis(const FloatType& angle) = 0;
  virtual void LotateAroundZAxis(const FloatType& angle) = 0;
};

}  // namespace lotate_polyhedron

#endif