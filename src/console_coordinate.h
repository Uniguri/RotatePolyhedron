#ifndef LOTATE_POLYHEDRON_CONSOLE_COORDINATE_H_
#define LOTATE_POLYHEDRON_CONSOLE_COORDINATE_H_

#include <cstdint>

#include "console_buffer.h"
#include "coordinate.hpp"
#include "dot.hpp"
#include "fixed_point.hpp"
#include "line.hpp"
#include "shape_using_eb.hpp"

namespace lotate_polyhedron {

class ConsoleCoordinate
    : public ConsoleBuffer,
      public Coordinate<FixedPoint<32>,
                        ElementBufferLineShape<FixedPoint<32>>> {
 public:
  using FloatType = FixedPoint<32>;
  using DotType = Dot<FloatType>;
  using LineType = Line<FloatType>;
  using LineIndicatorType = std::pair<size_t, size_t>;
  using ShapeType = ElementBufferLineShape<FloatType>;

 private:
  constexpr static FloatType kDrawDx = FloatType(0.5);
  constexpr static int WidthPerHeightZoomFactor = 2;

 public:
  explicit ConsoleCoordinate(void)
      : ConsoleBuffer(),
        Coordinate(),
        width_zoom_factor_(2.0),
        height_zoom_factor_(1.0) {
    SetOriginCentor();
  }

  explicit ConsoleCoordinate(double zoom_factor)
      : ConsoleBuffer(),
        Coordinate(),
        width_zoom_factor_(WidthPerHeightZoomFactor * zoom_factor),
        height_zoom_factor_(zoom_factor) {
    SetOriginCentor();
  }

  explicit ConsoleCoordinate(double width_zoom_factor,
                             double height_zoom_factor)
      : ConsoleBuffer(),
        Coordinate(),
        width_zoom_factor_(width_zoom_factor),
        height_zoom_factor_(height_zoom_factor) {
    SetOriginCentor();
  }

  ConsoleCoordinate(const ConsoleCoordinate& cc)
      : ConsoleBuffer(cc),
        Coordinate(cc),
        origin_(cc.origin_),
        width_zoom_factor_(cc.width_zoom_factor_),
        height_zoom_factor_(cc.height_zoom_factor_) {}
  ConsoleCoordinate(ConsoleCoordinate&& cc)
      : ConsoleBuffer(std::move(cc)),
        Coordinate(std::move(cc)),
        origin_(std::move(cc.origin_)),
        width_zoom_factor_(cc.width_zoom_factor_),
        height_zoom_factor_(cc.height_zoom_factor_) {}

 public:
  inline DotType GetOrigin(void) const { return origin_; }
  inline double GetWidthZoomFactor(void) const { return width_zoom_factor_; }
  inline double GetHeightZoomFactor(void) const { return height_zoom_factor_; }

  inline void SetOriginCentor(void) {
    origin_ = DotType(ConsoleBuffer::GetConsoleWidth() / 2,
                      ConsoleBuffer::GetConsoleHeight() / 2, 0);
  }
  inline void SetOrigin(const DotType& dot) { origin_ = dot; }
  inline void SetOrigin(DotType&& dot) { origin_ = std::move(dot); }
  inline void SetZoomFactor(double factor) {
    SetWidthZoomFactor(WidthPerHeightZoomFactor * factor);
    SetHeightZoomFactor(factor);
  }
  inline void SetWidthZoomFactor(double factor) { width_zoom_factor_ = factor; }
  inline void SetHeightZoomFactor(double factor) {
    height_zoom_factor_ = factor;
  }

  void Draw(void);

  inline void SyncConsoleSize(void) {
    ConsoleBuffer::SyncConsoleSize();
    SetOriginCentor();
  }

 private:
  void DrawLineOnBuffer(const LineType& line);

 private:
  DotType origin_;
  double width_zoom_factor_;
  double height_zoom_factor_;
};

}  // namespace lotate_polyhedron

#endif