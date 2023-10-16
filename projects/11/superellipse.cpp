// Write a program that draws “starlike” patterns by connecting points
// on a superellipse. Take a, b, m, n, and N as arguments. Select N
// points on the superellipse defined by a, b, m, and n. Make the points
// equally spaced for some definition of “equal.” Connect each of those
// N points to one or more other points (if you like you can make
// the number of points to which to connect a point another argument or
// just use N–1, i.e., all the other points).

#include <cmath>
#include <exception>
#include <iostream>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>

using namespace Graph_lib;

double sign (double x) { return x > 0 ? 1 : (x < 0 ? -1 : 0); }

void add_superellipse (Point center, double a, double b, double m, double n,
                       int npoints, Closed_polyline& curve)
{
  for (int i = 0; i < npoints; ++i)
  {
    double t = 2. * pi * i / npoints;
    double cos_t = cos(t);
    double sin_t = sin(t);

    Point p{center};
    p.x += a * sign(cos_t) * pow(abs(cos_t), 2. / m);
    p.y += b * sign(sin_t) * pow(abs(sin_t), 2. / n);

    curve.add(p);
  }
}

int main ()
try
{
  Simple_window win{Point{100, 100}, 410, 410, "Superellipse"};

  constexpr int npoints{100};  // number of points
  constexpr int a{200};        // major half-axis
  constexpr int b{180};        // minor half-axis

  Point c{win.x_max() / 2, win.y_max() / 2};  // window center
  Vector_ref<Closed_polyline> curve;

  for (double n : {4.0, 2.0, 1.5, 1.0, 2. / 3., 0.4})
  {
    curve.push_back(new Closed_polyline{});
    add_superellipse(c, a, b, n, n, npoints, curve[curve.size() - 1]);
    win.attach(curve[curve.size() - 1]);
  }

  // color and style ellipses
  Line_style bold{Line_style::solid, 2};

  Text ng2{Point{20, 20}, "n>2"};
  ng2.set_color(Color::green);
  win.attach(ng2);

  curve[0].set_color(Color::green);

  Text n2{Point{50, 60}, "n=2"};
  win.attach(n2);
  curve[1].set_style(bold);
  curve[1].set_color(Color::red);
  n2.set_color(Color::red);

  curve[2].set_color(Color::blue);

  Text n1{Point{90, 100}, "n=1"};
  win.attach(n1);
  curve[3].set_style(bold);
  curve[3].set_color(Color::dark_blue);
  n1.set_color(Color::dark_blue);

  curve[4].set_color(Color::dark_magenta);
  curve[5].set_color(Color::magenta);

  Text nl1{Point{190, 190}, "n<1"};
  nl1.set_color(Color::magenta);
  win.attach(nl1);

  win.wait_for_button();
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
