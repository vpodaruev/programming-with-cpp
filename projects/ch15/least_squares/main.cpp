#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>

#include "least_squares.h"

using namespace Graph_lib;

double linear (double x) { return x; }

double non_linear (double x) { return 10 * sin(x) * cos(2.5 * x); }

std::string as_str (double x, std::streamsize precision = 3)
{
  std::ostringstream oss;
  oss.precision(precision);
  oss << std::fixed << x;
  return oss.str();
}

auto make_regression (lsm::Coeff a, lsm::Coeff b, lsm::BaseFunction f)
{
  return [a, b, f] (double x) { return a.value + b.value * f(x); };
}

class Scale  // data value to coordinate conversion
{
  int cbase;     // coordinate base
  double vbase;  // base of values
  double scale;

public:
  Scale(int b, double vb, double s) : cbase{b}, vbase{vb}, scale{s} {}

  int operator() (double v) const { return cbase + (v - vbase) * scale; }
};

int main ()
try
{
  constexpr int xmax = 600;  // window size
  constexpr int ymax = 450;

  constexpr int xoffset = 40;  // distance from left-hand side of window
                               // to y axis
  constexpr int yoffset = 40;  // distance from bottom of window to x axis

  constexpr int xspace = 40;  // space beyond axis
  constexpr int yspace = 40;

  constexpr int xlength = xmax - xoffset - xspace;  // length of axes
  constexpr int ylength = ymax - yoffset - yspace;

  constexpr Point orig{xoffset,  // axes origin
                       ymax - yoffset};

  constexpr int rmin = 0;  // data range
  constexpr int rmax = 10;
  constexpr double xscale = double(xlength) / (rmax - rmin);
  constexpr double yscale = double(ylength) / 250;

  constexpr int npoints = 1000;  // number of points in range

  Scale xs{xoffset, rmin, xscale};
  Scale ys{ymax - yoffset, 0, -yscale};

  Point lt{100, 100};  // left top window corner
  Simple_window win{lt, xmax, ymax, "Least Squares"};
  win.color(Color::white);

  // draw axes
  Axis x{Axis::x, orig, xlength, int(xlength / xscale), "X"};
  Axis y{Axis::y, orig, ylength, 10, "Y"};
  x.label.move(xoffset + xlength - 200, 0);
  win.attach(x);
  win.attach(y);
  win.wait_for_button();

  // draw raw data (scatter plot)
  auto data = lsm::read("data.txt");

  Marks scatter{"O"};
  for (auto p : data)
    scatter.add(Point{xs(p.x), ys(p.y)});
  win.attach(scatter);
  win.wait_for_button();

  // draw linear regression
  auto [a, b] = lsm::least_squares(data, linear);  // C++17

  Function line1{make_regression(a, b, linear),
                 rmin,
                 rmax,
                 orig,
                 npoints,
                 xscale,
                 yscale};
  line1.set_style(Line_style{Line_style::solid, 2});
  line1.set_color(Color::red);
  win.attach(line1);

  Point p1{xoffset + 50, yspace + 20};
  Text eq1{p1, "y = " + as_str(a.value) + " + " + as_str(b.value) + "*x"};
  eq1.set_color(Color::red);
  eq1.set_font_size(15);
  win.attach(eq1);
  win.wait_for_button();

  // draw non-linear regression
  auto [c, d] = lsm::least_squares(data, non_linear);  // C++17

  Function line2{make_regression(c, d, non_linear),
                 rmin,
                 rmax,
                 orig,
                 npoints,
                 xscale,
                 yscale};
  line2.set_style(Line_style{Line_style::solid, 2});
  line2.set_color(Color::blue);
  win.attach(line2);

  Point p2{xoffset + 50, yspace + 40};
  Text eq2{p2, "y = " + as_str(c.value) + " + " + as_str(d.value) +
                   "*sin(x)*cos(2.5*x)"};
  eq2.set_color(Color::blue);
  eq2.set_font_size(15);
  win.attach(eq2);
  win.wait_for_button();
}
catch (std::exception& e)
{
  std::cerr << "error: " << e.what() << std::endl;
  return 1;
}
