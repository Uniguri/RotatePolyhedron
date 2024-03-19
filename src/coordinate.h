#ifndef LOTATEPOLYHEDRON_COORDINATE_H_
#define LOTATEPOLYHEDRON_COORDINATE_H_

namespace lotate_polyhedron {

template <typename FloatType, typename ShapeType>
class Coordinate {
 public:
  using DotType = Dot<FloatType>;
  using VertexVectorType = std::vector<DotType>;
  using LineType = Line<FloatType>;
  using LineIndicatorType = std::pair<size_t, size_t>;
  using LineIndicatorVectorType = std::vector<LineIndicatorType>;

 private:
};

}  // namespace lotate_polyhedron

#endif