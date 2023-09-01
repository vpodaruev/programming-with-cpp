// Read data of an experiment from file given as command line argument and
// having the following format:
//   x1 y1
//   ...
//   xN yN
// Compute linear regression [y = a + b*x] coefficients using the least
// squares method.

#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

struct Point
{
  double x, y;

  Point() = default;

  Point(double xx, double yy) : x{xx}, y{yy}
  { /* empty body */
  }
};

std::istream& operator>> (std::istream& is, Point& rhs)
{
  return is >> rhs.x >> rhs.y;
}

std::ostream& operator<< (std::ostream& os, const Point& rhs)
{
  return os << rhs.x << " " << rhs.y;
}

auto read (const std::string& filename)
{
  std::ifstream ifs{filename};
  if (!ifs)
    throw std::runtime_error{"can't open file '" + filename + "'"};

  return std::vector<Point>{std::istream_iterator<Point>{ifs},
                            std::istream_iterator<Point>{}};
}

struct Coeff
{
  double value;  // coefficient estimate
  double delta;  // confidence band

  Coeff(double v, double d) : value{v}, delta{d}
  { /* empty body */
  }
};

auto least_squares (const std::vector<Point>& points)
{
  // compute average values
  size_t N = points.size();
  double x_ave = 0., x2_ave = 0.;
  double y_ave = 0., xy_ave = 0.;

  for (const auto& p : points)
  {
    x_ave += p.x;
    x2_ave += p.x * p.x;
    y_ave += p.y;
    xy_ave += p.x * p.y;
  }
  x_ave /= N;
  x2_ave /= N;
  y_ave /= N;
  xy_ave /= N;

  // compute linear coefficient estimate
  double b = (xy_ave - x_ave * y_ave) / (x2_ave - x_ave * x_ave);

  if (!std::isfinite(b))
    throw std::overflow_error{"division by zero"};

  // compute constant coefficient estimate
  double a = y_ave - b * x_ave;

  return std::make_tuple(Coeff{a, 0.}, Coeff{b, 0.});
}

int main (int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "usage: " << argv[0] << "  file_with_data" << std::endl;
    return 2;
  }

  try
  {
    std::string datafile{argv[1]};

    auto [a, b] = least_squares(read(datafile));  // C++17

    std::cout << datafile << "  " << a.value << " " << a.delta << "  "
              << b.value << " " << b.delta << std::endl;
  }
  catch (std::exception& e)
  {
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  }
}
