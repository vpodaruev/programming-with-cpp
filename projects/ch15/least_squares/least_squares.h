#ifndef LEAST_SQUARES_H
#define LEAST_SQUARES_H 1

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

namespace lsm {

struct Point
{
  double x, y;

  Point() = default;

  Point(double xx, double yy) : x{xx}, y{yy}
  { /* empty body */
  }
};

std::istream& operator>> (std::istream& is, Point& rhs);
std::ostream& operator<< (std::ostream& os, const Point& rhs);

/** Read data of an experiment from file given as command
 *  line argument and having the following format:
 *  @note
 *    // some comment (may be omitted)
 *    (x1, y1)
 *    ...
 *    (xN, yN)
 */
std::vector<Point> read (const std::string& filename);

struct Coeff
{
  double value;  // coefficient estimate
  double delta;  // confidence band

  Coeff(double v, double d) : value{v}, delta{d}
  { /* empty body */
  }
};

using BaseFunction = double (*)(double);
using CoeffTuple = std::tuple<Coeff, Coeff>;

/** For the given linear regression:
 *  @f[
 *      y = a + b f(x)
 *  @f]
 *  compute coefficients using the least squares method
 */
CoeffTuple least_squares (const std::vector<Point>& points, BaseFunction f);

}  // namespace lsm

#endif  // #ifndef LEAST_SQUARES_H
