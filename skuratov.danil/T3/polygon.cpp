#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>
#include "delimiter.hpp"

bool skuratov::Point::operator==(const Point& diff) const
{
  return ((x == diff.x) && (y == diff.y));
}

std::istream& skuratov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimiter;
  Point pos = {};

  in >> del{ '(' } >> pos.x >> del{ ';' } >> pos.y >> del{ ')' };
  if (in)
  {
    point = pos;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& skuratov::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t verticesNumb = {};
  in >> verticesNumb;

  std::vector< Point > pos;
  using inputItT = std::istream_iterator< Point >;
  std::copy_n(inputItT{ in }, verticesNumb, std::back_inserter(pos));

  if (pos.size() == verticesNumb)
  {
    polygon.points = pos;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

double skuratov::ŅalculateArea::operator()(double res, const Point& point2, const Point& point3)
{
  res += 0.5 * (std::abs((point2.x - point1.x) * (point3.y - point1.y) - (point3.x - point1.x) * (point2.y - point1.y)));
  point1 = point2;
  return res;
}

double skuratov::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto res = std::bind(ŅalculateArea{ points[1] }, _1, _2, points[0]);
  return std::accumulate(points.begin(), points.end(), 0.0, res);
}

bool skuratov::ŅalculateCorners::operator()(const Point& point3)
{
  Point side1 = { point2.x - point1.x, point2.y - point1.y };
  Point side2 = { point3.x - point1.x, point3.y - point1.y };

  point1 = point2;
  point2 = point3;

  return side1.x * side2.x + side1.y * side2.y == 0;
}

int skuratov::Polygon::getCorners() const
{
  std::vector< bool > corners(points.size());
  std::generate_n(corners.begin(), corners.size(), [this, i = 0]() mutable
  {
    bool result = ŅalculateCorners{ points[i == 0 ? points.size() - 1 : i - 1], points[i++] }(points[i]);
    return result;
  });
  return std::count(corners.begin(), corners.end(), true);
}
