#include "console_coordinate.h"

#include <cmath>

#include "dot.hpp"
#include "fixed_point.hpp"
#include "line.hpp"

namespace lotate_polyhedron {

void ConsoleCoordinate::Draw(void) {
  SwapBuffer();
  for (size_t i = 0; i < GetShapeCount(); ++i) {
    for (const auto& line : GetShapeAt(i)) {
      DrawLineOnBuffer(line);
    }
  }
  ConsoleBuffer::Draw();
}

void ConsoleCoordinate::DrawLineOnBuffer(const LineType& line) {
  const FloatType& dx = kDrawDx;
  // Projection using z=0, so we does not need additional operation/
  const DotType& zoom_factor =
      DotType(width_zoom_factor_, height_zoom_factor_, 0.0);
  const DotType& dot1 =
      line.dot1.ElementWiseMultiplication(zoom_factor) + origin_;
  const DotType& dot2 =
      line.dot2.ElementWiseMultiplication(zoom_factor) + origin_;

  if (abs(dot1.x - dot2.x) < dx) {
    const size_t& x = round(dot1.x);
    if (x < 0 || x >= GetConsoleWidth()) {
      return;
    }
    const FloatType& min_y = std::min(dot1.y, dot2.y);
    const FloatType& max_y = std::max(dot1.y, dot2.y);
    const FloatType& loop_start = std::max(min_y, FloatType(0));
    const FloatType& loop_end = std::min(max_y, FloatType(GetConsoleHeight()));
    for (FloatType y = loop_start; y < loop_end; y += 1) {
      SetAt(x, round(y), '*');
    }
  } else {
    const FloatType& gradient = (dot2.y - dot1.y) / (dot2.x - dot1.x);
    const FloatType& y_intercept = dot1.y - gradient * dot1.x;
    const FloatType& min_x = std::min(dot1.x, dot2.x);
    const FloatType& max_x = std::max(dot1.x, dot2.x);
    const FloatType& loop_start = std::max(min_x, FloatType(0));
    const FloatType& loop_end = std::min(max_x, FloatType(GetConsoleWidth()));
    for (FloatType x = loop_start; x < loop_end; x += dx) {
      const size_t& y = round(gradient * x + y_intercept);
      if (y < 0 || y >= GetConsoleHeight()) {
        continue;
      }
      SetAt(round(x), y, '*');
    }
  }
}

}  // namespace lotate_polyhedron