#ifndef LOTATEPOLYHEDRON_COORDINATE_HPP_
#define LOTATEPOLYHEDRON_COORDINATE_HPP_

#include <vector>

namespace lotate_polyhedron {

template <typename __FloatType, typename __ShapeType>
class Coordinate {
 private:
  class ShapeIterator {
   private:
    using FloatType = __FloatType;
    using ShapeType = __ShapeType;
    using IteratorType = typename std::vector<ShapeType>::iterator;

   public:
    explicit ShapeIterator(void) = delete;
    explicit ShapeIterator(const IteratorType& itr) : itr_(itr) {}

    inline ShapeIterator& operator++(void) {
      ++itr_;
      return *this;
    }
    inline ShapeIterator operator++(int junk) {
      ShapeIterator temp(*this);
      ++*(this);
      return temp;
    }

    inline bool operator==(const ShapeIterator& rhs) const {
      return itr_ == rhs.itr_;
    }
    inline bool operator!=(const ShapeIterator& rhs) const {
      return !(*this == rhs);
    }

    inline ShapeType& operator*(void) const { return *itr_; }
    inline IteratorType operator->(void) const { return itr_; }

   private:
    IteratorType itr_;
  };

 public:
  using FloatType = __FloatType;
  using ShapeType = __ShapeType;
  using IteratorType = ShapeIterator;

 public:
  explicit Coordinate(void) : shapes_() {}

  inline size_t GetShapeCount(void) const { return shapes_.size(); }
  inline ShapeType& GetShapeAt(size_t idx) { return shapes_[idx]; }

  inline IteratorType begin(void) { return IteratorType{shapes_.begin()}; }
  inline IteratorType end(void) { return IteratorType{shapes_.end()}; }

  inline void AddShpae(const ShapeType& shape) { shapes_.push_back(shape); }
  void AddShpae(ShapeType&& shape) { shapes_.push_back(std::move(shape)); }

  void LotateEveryShapeAroundXAxis(const FloatType& angle) {
    for (auto& shape : shapes_) {
      shape.LotateAroundXAxis(angle);
    }
  }

  void LotateEveryShapeAroundYAxis(const FloatType& angle) {
    for (auto& shape : shapes_) {
      shape.LotateAroundYAxis(angle);
    }
  }

  void LotateEveryShapeAroundZAxis(const FloatType& angle) {
    for (auto& shape : shapes_) {
      shape.LotateAroundZAxis(angle);
    }
  }

  inline IteratorType DeleteShape(IteratorType pos) {
    return IteratorType{shapes_.erase(pos.itr_)};
  }

 private:
  std::vector<ShapeType> shapes_;
};

}  // namespace lotate_polyhedron

#endif