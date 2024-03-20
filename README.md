# LotatePolyhedron
Lotate polyhedron on linux console.

# Usage
You can define polyhedron using std::vector like VBO and EBO.
Then define shape with them and add it to ConsoleCoordinate object.
Finally you can draw them!!

## Example
Full examples is in [main.cc](./src/main.cc).
```C++
ConsoleCoordinate cc(10);
// Define shape s.
cc.AddShpae(s);

int64_t sleep_time = 100;
// x, y and z are (radian) angle for lotation.
ConsoleCoordinate::FloatType x(0.03), y(0.03), z(0.03);
while (1) {
  cc.Clear();
  cc.Draw();
  std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
  // Lotate every shape around ? axis
  cc.LotateEveryShapeAroundXAxis(x);
  cc.LotateEveryShapeAroundYAxis(y);
  cc.LotateEveryShapeAroundZAxis(z);
}
```

# Demo
[![Demo video](http://img.youtube.com/vi/Nl9Az6YDndc/0.jpg)](https://youtu.be/Nl9Az6YDndc)

# Library
- https://github.com/Uniguri/FixedPoint
