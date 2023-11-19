#include <cmath>
#include <exception>
#include <iostream>
#include <sstream>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>

using namespace Graph_lib;

struct Func : Function
{
  Func(Fct f, double rmin, double rmax, Point orig, int count = 100,
       double xscale = 25, double yscale = 25);

  void move (int dx, int dy) override;

  void set_function (Fct f);
  void set_range (double rmin, double rmax);
  void set_scale (double xscale, double yscale);

private:
  void redistribute ();

  Fct func;       /// function for graphing
  double a, b;    /// in range [a,b]
  Point xy;       /// with origin at `xy` point
  double xs, ys;  /// and x-axis and y-axis scales
};

Func::Func(Fct f, double rmin, double rmax, Point orig, int count,
           double xscale, double yscale)
    : Function{f, rmin, rmax, orig, count, xscale, yscale}, func{f},
      a{rmin}, b{rmax}, xy{orig}, xs{xscale}, ys{yscale}
{
}

void Func::move(int dx, int dy)
{
  xy.x += dx;
  xy.y += dy;
  Function::move(dx, dy);
}

void Func::set_function(Fct f)
{
  func = f;
  redistribute();
}

void Func::set_range(double rmin, double rmax)
{
  if (rmax - rmin <= 0)
    error("bad graphing range");

  a = rmin, b = rmax;
  redistribute();
}

void Func::set_scale(double xscale, double yscale)
{
  xs = xscale, ys = yscale;
  redistribute();
}

void Func::redistribute()
{
  double dist = (b - a) / number_of_points();
  double r = a;
  for (int i = 0; i < number_of_points(); ++i)
  {
    set_point(i, Point{xy.x + int(r * xs), xy.y - int(func(r) * ys)});
    r += dist;
  }
}

double term (int k) { return pow(-1., k) / (2. * k + 1.); }

double leibniz (int n)
{
  double sum = 0.;
  for (int i = 0; i < n; ++i)
    sum += term(i);
  return sum;
}

void ex_func ()
{
  constexpr int xmax = 600;  // window size
  constexpr int ymax = 400;

  constexpr int x_orig = xmax / 2;  // position of (0,0) is center of window
  constexpr int y_orig = ymax / 2;
  const Point orig{x_orig, y_orig};

  constexpr double r_min = -10;  // graphing range [rmin,rmax)
  constexpr double r_max = 11;

  constexpr int npoints = 400;  // number of points used in range

  constexpr int x_scale = 25;  // scaling factor
  constexpr int y_scale = 25;

  Simple_window win{Point{100, 100}, xmax, ymax, "Function changes"};

  constexpr int xlength = xmax - 40;  // make the axis a bit smaller
  constexpr int ylength = ymax - 40;  //  than the window

  Axis x{Axis::x, Point{20, y_orig}, xlength, xlength / x_scale,
         "one notch == 1"};
  Axis y{Axis::y, Point{x_orig, ylength + 20}, ylength, ylength / y_scale,
         "one notch == 1"};
  win.attach(x);
  win.attach(y);

  std::vector<Fct> funs{sin, cos, [] (double x) { return sin(x) + cos(x); },
                        [] (double x)
                        { return pow(sin(x), 2) + pow(cos(x), 2); }};

  Func func{funs[0], r_min, r_max, orig, npoints, x_scale, y_scale};
  func.set_color(Color::blue);
  func.set_style(Line_style{Line_style::solid, 2});
  win.attach(func);
  win.wait_for_button();

  for (auto f : funs)
  {
    func.move(20, -20);
    func.set_function(f);
    func.set_scale(x_scale * randint(1, 3), y_scale * randint(1, 2));
    func.set_range(r_min / randint(1, 2), r_max / randint(1, 3));
    win.wait_for_button();
  }
}

void ex_leibniz ()
{
  constexpr int xmax = 600;  // window size
  constexpr int ymax = 400;

  constexpr int x_orig = xmax / 2;  // position of (0,0) is center of window
  constexpr int y_orig = ymax / 2;
  const Point orig{x_orig, y_orig};

  constexpr double r_min = -10;  // graphing range [rmin,rmax)
  constexpr double r_max = 11;

  constexpr int npoints = 20;  // number of points used in range

  constexpr int x_scale = 25;  // scaling factor
  constexpr int y_scale = 180;

  constexpr double pi = acos(-1);

  Simple_window win{Point{100, 100}, xmax, ymax, "Leibniz's series"};

  constexpr int xlength = xmax - 40;  // make the axis a bit smaller
  constexpr int ylength = ymax - 40;  //  than the window

  Axis x{Axis::x, Point{20, y_orig}, xlength, xlength / x_scale,
         "one notch == 1"};
  Axis y{Axis::y, Point{x_orig, ylength + 20}, ylength, ylength / y_scale,
         "one notch == 1"};
  win.attach(x);
  win.attach(y);

  Function le{[] (double) { return pi / 4; },
              r_min,
              r_max,
              orig,
              npoints,
              x_scale,
              y_scale};
  le.set_color(Color::green);
  win.attach(le);

  Text label{Point{x_orig + 10, le.point(0).y + 20}, "pi/4"};
  label.set_color(Color::green);
  win.attach(label);

  Func la{[] (double) { return leibniz(0); },
          r_min,
          r_max,
          orig,
          npoints,
          x_scale,
          y_scale};
  la.set_color(Color::red);

  for (int n = 0; n < 50; ++n)
  {
    std::ostringstream ss;
    ss << "Leibniz's series approximation; n == " << n;
    win.set_label(ss.str());
    la.set_function([n] (double) { return leibniz(n); });
    win.attach(la);
    win.wait_for_button();
    win.detach(la);
  }
}

int main ()
try
{
  ex_func();
  ex_leibniz();
}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
catch (...)
{
  std::cerr << "Oops, something went wrong..." << std::endl;
  return 2;
}
