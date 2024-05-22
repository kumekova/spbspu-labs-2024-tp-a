#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>

namespace novokhatskiy
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& p);
  std::ostream& operator<<(std::ostream& out, const Point& p);

  struct Polygon
  {
    std::vector< Point > points;
  };

  double getArea(const std::vector< Point >& points);

  std::istream& operator>>(std::istream& in, Polygon& p);
  std::ostream& operator<<(std::ostream& out, const Polygon& p);
  bool operator==(Point& lhs, Point& rhs);
  bool operator<(const Point& lhs, const Point& rhs);
  bool operator<(const Polygon& lhs, const Polygon& rhs);
}

#endif
