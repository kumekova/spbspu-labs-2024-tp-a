#include "polygon.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iterator>
#include <numeric>
#include "commandsSolving.hpp"
#include "delimiter.hpp"

std::istream& novokhatskiy::operator>>(std::istream& in, Point& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point tmp = {};
  in >> strictDel{ '(' } >> tmp.x >> strictDel{ ';' } >> tmp.y >> strictDel{ ')' };
  if (in)
  {
    p = tmp;
  }
  return in;
}

std::ostream& novokhatskiy::operator<<(std::ostream& out, const Point& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << p.x << ';' << p.y << ')';
  return out;
}

std::istream& novokhatskiy::operator>>(std::istream& in, Polygon& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t countPoints = {};
  in >> countPoints;
  if (countPoints < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > tmp;
  using InputIt = std::istream_iterator< Point >;
  std::copy_n(InputIt{ in }, countPoints, std::back_inserter(tmp));
  if (in)
  {
    p.points = tmp;
  }
  return in;
}

std::ostream& novokhatskiy::operator<<(std::ostream& out, const Polygon& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  using outIt = std::ostream_iterator< Point >;
  out << p.points.size();
  std::copy(p.points.cbegin(), p.points.cend(), outIt{ out, " " });
  return out;
}

bool novokhatskiy::operator==(Point& lhs, Point& rhs)
{
  if (lhs.x == rhs.x && lhs.y == rhs.y)
  {
    return true;
  }
  else
  {
    std::swap(lhs.x, lhs.y);
    return (lhs.x == rhs.x && lhs.y == rhs.y);
  }
}

bool novokhatskiy::operator<(const Point& lhs, const Point& rhs)
{
  if (lhs.x == rhs.x)
  {
    return lhs.y < rhs.y;
  }
  return lhs.x < rhs.x;
}

bool novokhatskiy::operator<(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points.size() < rhs.points.size();
}

double novokhatskiy::getArea(const std::vector< Point >& points)
{
  using namespace std::placeholders;
  auto res = std::bind(commands::AccumulateArea{ points[1] }, _1, _2, points[0]);
  return std::accumulate(points.begin(), points.end(), 0.0, res);
}
