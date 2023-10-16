#ifndef POLY_H
#define POLY_H 1

#include <cmath>
#include <list>

#include <Graph_lib/Graph.h>

#include <vec/vec2d.h>

using Graph_lib::Closed_polyline;
using Graph_lib::Point;

Vec2d rotated (double angle, Vec2d point, Vec2d center = Vec2d{});

/**
 * Compute regular polygon vertices
 *
 * @param n -- vertex number
 * @param center -- polygon center
 * @param radius -- circumcircle radius
 * @param angle -- first vertex position (phase angle, in radians)
 *
 * @return vertex list
 */
std::list<Vec2d> regular_polygon (int n, Vec2d center, double radius,
                                  double angle = 0.);

/// similar to C++20 std::lerp() function
inline Vec2d lerp (Vec2d a, Vec2d b, double t) { return a + (b - a) * t; }

inline auto as_point (Vec2d p)
{
  return Point{int(std::round(p.x)), int(std::round(p.y))};
}

void append (Closed_polyline& poly, const std::list<Vec2d>& points);

#endif  // #ifndef POLY_H
