#ifndef LOTATEPOLYHEDRON_SHAPE_USING_EB_HPP_
#define LOTATEPOLYHEDRON_SHAPE_USING_EB_HPP_

#include <cstdint>
#include <memory>
#include <vector>

#include "dot.hpp"
#include "line.hpp"
#include "shape.hpp"

namespace lotate_polyhedron {

template <typename __FloatType>
class BELineIterator
    : public LineIterator<__FloatType, BELineIterator<__FloatType>> {
 private:
  using FloatType = __FloatType;
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

  inline BELineIterator& operator++(void) override {
    ++line_idx_;
    return *this;
  }

  inline BELineIterator operator++(int junk) override {
    BELineIterator temp(*this);
    ++(*this);
    return temp;
  }

  inline bool operator==(const BELineIterator& li) const override {
    return (line_idx_ == li.line_idx_) && (&vertices_ == &li.vertices_) &&
           (&line_elements_ == &li.line_elements_);
  }

  inline bool operator!=(const BELineIterator& li) const override {
    return !(*this == li);
  }

  inline LineType operator*(void) const override {
    const auto& line_indices = line_elements_[line_idx_];
    return LineType(vertices_[line_indices.first],
                    vertices_[line_indices.second]);
  }

  inline std::unique_ptr<LineType> operator->(void) const override {
    const auto& line_indices = line_elements_[line_idx_];
    return std::make_unique<LineType>(vertices_[line_indices.first],
                                      vertices_[line_indices.second]);
  }

 private:
  size_t line_idx_;
  const VertexVectorType& vertices_;
  const LineIndicatorVectorType& line_elements_;
};

template <typename __FloatType>
class ElementBufferLineShape
    : public Shape<__FloatType, BELineIterator<__FloatType>> {
 private:
  using FloatType = __FloatType;
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
      const std::vector<std::pair<size_t, size_t>>& line_elements)
      : vertices_(vertices), line_elements_(line_elements) {}

  explicit ElementBufferLineShape(
      std::vector<DotType>&& vertices,
      std::vector<std::pair<size_t, size_t>>&& line_elements)
      : vertices_(std::move(vertices)),
        line_elements_(std::move(line_elements)) {}

  explicit ElementBufferLineShape(const ElementBufferLineShape& ebs)
      : vertices_(ebs.vertices_), line_elements_(ebs.line_elements_) {}

  explicit ElementBufferLineShape(ElementBufferLineShape&& ebs)
      : vertices_(std::move(ebs.vertices_)),
        line_elements_(std::move(ebs.line_elements_)) {}

 public:
  inline BELineIterator<FloatType> begin(void) const override {
    return BELineIterator<FloatType>(0, vertices_, line_elements_);
  }

  inline BELineIterator<FloatType> end(void) const override {
    return BELineIterator<FloatType>(line_elements_.size(), vertices_,
                                     line_elements_);
  }

  virtual inline size_t GetDotCount(void) const { return vertices_.size(); }

  virtual inline size_t GetLineCount(void) const {
    return line_elements_.size();
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