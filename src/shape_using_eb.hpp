#ifndef LOTATEPOLYHEDRON_SHAPE_USING_EB_HPP_
#define LOTATEPOLYHEDRON_SHAPE_USING_EB_HPP_

#include <cstdint>
#include <memory>
#include <vector>

#include "dot.hpp"
#include "line.hpp"
#include "shape.hpp"

namespace lotate_polyhedron {

template <typename FloatType>
class BELineIterator
    : public LineIterator<FloatType, BELineIterator<FloatType>> {
 private:
  using DotType = Dot<FloatType>;
  using VertexVectorType = std::vector<DotType>;
  using LineType = Line<FloatType>;
  using LineIndicatorType = std::pair<size_t, size_t>;
  using LineIndicatorVectorType = std::vector<LineIndicatorType>;

 private:
  explicit BELineIterator(void) = delete;

 public:
  explicit BELineIterator(size_t line_idx, const VertexVectorType& vertices,
                          const LineIndicatorVectorType& line_elements)
      : line_idx_(line_idx),
        vertices_(vertices),
        line_elements_(line_elements) {}

  BELineIterator(const BELineIterator& li)
      : line_idx_(li.line_idx_),
        vertices_(li.vertices_),
        line_elements_(li.line_elements_) {}

  BELineIterator& operator++(void) override {
    ++line_idx_;
    return *this;
  }

  BELineIterator operator++(int junk) override {
    BELineIterator temp(*this);
    ++(*this);
    return temp;
  }

  bool operator==(const BELineIterator& li) const override {
    return (line_idx_ == li.line_idx_) && (&vertices_ == &li.vertices_) &&
           (&line_elements_ == &li.line_elements_);
  }

  bool operator!=(const BELineIterator& li) const override {
    return !(*this == li);
  }

  LineType operator*(void) const override {
    const auto& line_indices = line_elements_[line_idx_];
    return LineType(vertices_[line_indices.first],
                    vertices_[line_indices.second]);
  }

  std::unique_ptr<LineType> operator->(void) const override {
    const auto& line_indices = line_elements_[line_idx_];
    return std::make_unique<LineType>(vertices_[line_indices.first],
                                      vertices_[line_indices.second]);
  }

 private:
  size_t line_idx_;
  const VertexVectorType& vertices_;
  const LineIndicatorVectorType& line_elements_;
};

template <typename FloatType>
class ElementBufferLineShape
    : public Shape<FloatType, BELineIterator<FloatType>> {
 private:
  using DotType = Dot<FloatType>;
  using VertexVectorType = std::vector<DotType>;
  using LineType = Line<FloatType>;
  using LineIndicatorType = std::pair<size_t, size_t>;
  using LineIndicatorVectorType = std::vector<LineIndicatorType>;

  constexpr static FloatType kPi{3.14159265359};

 public:
  explicit ElementBufferLineShape(void) = delete;

  explicit ElementBufferLineShape(
      const std::vector<DotType>& vertices,
      const std::vector<std::pair<size_t, size_t>> line_elements)
      : Shape<FloatType, BELineIterator<FloatType>>(vertices.size(),
                                                    line_elements.size()),
        vertices_(vertices),
        line_elements_(line_elements) {}

  explicit ElementBufferLineShape(const ElementBufferLineShape& ebs)
      : Shape<FloatType, BELineIterator<FloatType>>(ebs),
        vertices_(ebs.vertices_),
        line_elements_(ebs.line_elements_) {}

 public:
  BELineIterator<FloatType> begin(void) const override {
    return BELineIterator<FloatType>(0, vertices_, line_elements_);
  }

  BELineIterator<FloatType> end(void) const override {
    return BELineIterator<FloatType>(line_elements_.size(), vertices_,
                                     line_elements_);
  }

  void LotateAroundXAxis(const FloatType& angle) override {
    for (size_t i = 0; i < vertices_.size(); ++i) {
      vertices_[i].LotateAroundXAxisSelf(angle);
    }
  }

  void LotateAroundYAxis(const FloatType& angle) override {
    for (size_t i = 0; i < vertices_.size(); ++i) {
      vertices_[i].LotateAroundYAxisSelf(angle);
    }
  }

  void LotateAroundZAxis(const FloatType& angle) override {
    for (size_t i = 0; i < vertices_.size(); ++i) {
      vertices_[i].LotateAroundZAxisSelf(angle);
    }
  }

 private:
  VertexVectorType vertices_;
  LineIndicatorVectorType line_elements_;
};

}  // namespace lotate_polyhedron

#endif