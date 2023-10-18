#include <cassert>

#include "poly.h"

using Graph_lib::pi;

Vec2d rotated (double angle, Vec2d point, Vec2d center)
{
  Vec2d r{point - center};
  double cos_a = std::cos(angle);
  double sin_a = std::sin(angle);

  return center +
         Vec2d{cos_a * r.x - sin_a * r.y, sin_a * r.x + cos_a * r.y};
}

std::list<Vec2d> regular_polygon (int n, Vec2d center, double radius,
                                  double angle)
{
  assert(n > 2);

  Vec2d p{radius, 0.};  // direct along X-axis
  std::list<Vec2d> poly;

  for (int j = 0; j < n; ++j)
  {
    double phi = -2. * pi * j / n;      // rotate clockwise around (0, 0)
    Vec2d q = rotated(angle + phi, p);  //   starting from initial angle,
    poly.push_back(center + q);         // then shift and append
  }
  return poly;
}

void append (Closed_polyline& poly, const std::list<Vec2d>& points)
{
  for (const auto& item : points)
    poly.add(as_point(item));
}
