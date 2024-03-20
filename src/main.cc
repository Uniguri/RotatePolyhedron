#include <chrono>
#include <thread>
#include <vector>

#include "console_coordinate.h"

using namespace lotate_polyhedron;

void LotateCube(void);

void LotatePyramid(void);

void LotateCubeAndPyramid(void);

int main() {
  // LotatePyramid();
  // LotateCube();
  LotateCubeAndPyramid();
  return 0;
}

void LotateCube(void) {
  std::vector<ConsoleCoordinate::DotType> vbo = {
      // Bottom four dots
      ConsoleCoordinate::DotType(1, 1, -1),
      ConsoleCoordinate::DotType(-1, 1, -1),
      ConsoleCoordinate::DotType(-1, -1, -1),
      ConsoleCoordinate::DotType(1, -1, -1),
      // Top four dots
      ConsoleCoordinate::DotType(1, 1, 1),
      ConsoleCoordinate::DotType(-1, 1, 1),
      ConsoleCoordinate::DotType(-1, -1, 1),
      ConsoleCoordinate::DotType(1, -1, 1),
  };
  std::vector<ConsoleCoordinate::LineIndicatorType> ebo = {
      // Bottom Lines
      {0, 1},
      {1, 2},
      {2, 3},
      {3, 0},
      // Top Lines
      {4, 5},
      {5, 6},
      {6, 7},
      {7, 4},
      // Pillar Lines
      {0, 4},
      {1, 5},
      {2, 6},
      {3, 7},
  };
  ConsoleCoordinate::ShapeType s(vbo, ebo);

  ConsoleCoordinate cc(10);
  cc.AddShpae(s);
  int64_t sleep_time = 100;
  ConsoleCoordinate::FloatType x(0.03), y(0.03), z(0.03);
  while (1) {
    cc.SyncConsoleSize();
    cc.Clear();
    cc.Draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    cc.LotateEveryShapeAroundXAxis(x);
    cc.LotateEveryShapeAroundYAxis(y);
    cc.LotateEveryShapeAroundZAxis(z);
  }
}

void LotatePyramid(void) {
  std::vector<ConsoleCoordinate::DotType> vbo = {
      // Bottom four dots
      ConsoleCoordinate::DotType(1, 1, -1),
      ConsoleCoordinate::DotType(-1, 1, -1),
      ConsoleCoordinate::DotType(-1, -1, -1),
      ConsoleCoordinate::DotType(1, -1, -1),
      // Top dot
      ConsoleCoordinate::DotType(0, 0, 1),
  };
  std::vector<ConsoleCoordinate::LineIndicatorType> ebo = {
      // Bottom Lines
      {0, 1},
      {1, 2},
      {2, 3},
      {3, 0},
      // Lines To Top
      {0, 4},
      {1, 4},
      {2, 4},
      {3, 4},

  };
  ConsoleCoordinate::ShapeType s(vbo, ebo);

  ConsoleCoordinate cc(10);
  cc.AddShpae(s);
  int64_t sleep_time = 100;
  ConsoleCoordinate::FloatType x(0.03), y(0.03), z(0.03);
  while (1) {
    cc.SyncConsoleSize();
    cc.Clear();
    cc.Draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    cc.LotateEveryShapeAroundXAxis(x);
    cc.LotateEveryShapeAroundYAxis(y);
    cc.LotateEveryShapeAroundZAxis(z);
  }
}

void LotateCubeAndPyramid(void) {
  ConsoleCoordinate cc(10);
  {
    std::vector<ConsoleCoordinate::DotType> vbo = {
        // Bottom four dots
        ConsoleCoordinate::DotType(1, 1, -1),
        ConsoleCoordinate::DotType(-1, 1, -1),
        ConsoleCoordinate::DotType(-1, -1, -1),
        ConsoleCoordinate::DotType(1, -1, -1),
        // Top dot
        ConsoleCoordinate::DotType(0, 0, 1),
    };
    std::vector<ConsoleCoordinate::LineIndicatorType> ebo = {
        // Bottom Lines
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0},
        // Lines To Top
        {0, 4},
        {1, 4},
        {2, 4},
        {3, 4},

    };
    ConsoleCoordinate::ShapeType s(vbo, ebo);
    cc.AddShpae(std::move(s));
  }
  {
    std::vector<ConsoleCoordinate::DotType> vbo = {
        // Bottom four dots
        ConsoleCoordinate::DotType(1, 1, -1),
        ConsoleCoordinate::DotType(-1, 1, -1),
        ConsoleCoordinate::DotType(-1, -1, -1),
        ConsoleCoordinate::DotType(1, -1, -1),
        // Top four dots
        ConsoleCoordinate::DotType(1, 1, 1),
        ConsoleCoordinate::DotType(-1, 1, 1),
        ConsoleCoordinate::DotType(-1, -1, 1),
        ConsoleCoordinate::DotType(1, -1, 1),
    };
    std::vector<ConsoleCoordinate::LineIndicatorType> ebo = {
        // Bottom Lines
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0},
        // Top Lines
        {4, 5},
        {5, 6},
        {6, 7},
        {7, 4},
        // Pillar Lines
        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7},
    };
    ConsoleCoordinate::ShapeType s(vbo, ebo);
    cc.AddShpae(std::move(s));
  }

  int64_t sleep_time = 100;
  ConsoleCoordinate::FloatType x(0.03), y(0.03), z(0.03);
  while (1) {
    cc.SyncConsoleSize();
    cc.Clear();
    cc.Draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    cc.LotateEveryShapeAroundXAxis(x);
    cc.LotateEveryShapeAroundYAxis(y);
    cc.LotateEveryShapeAroundZAxis(z);
  }
}