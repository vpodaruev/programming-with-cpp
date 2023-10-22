#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <tuple>

#include <Graph_lib/Simple_window.h>
#include <Graph_lib/ext/graph.h>
#include <poly/poly.h>


using namespace Graph_lib;


auto fib_next (int n, int np)
{
  return std::make_tuple (n + np, n);
}


void draw_fibonacci_spiral (int win_w, int win_h)
{
  Point win_lt{ 100, 100 };           // window left top corner
  Simple_window win{ win_lt, win_w, win_h, "Fibonacci spiral" };

  Line_style st{ Line_style::solid, 4 };
  Color gold {134};
  Vector_ref<Graph_lib::Arc> spiral;

  constexpr int n_steps = 13;
  constexpr double scale = 2.0;

  int f = 1, fp = 1;                  // fibonacci numbers
  Vec2d c{ 0.72*win_w, 0.71*win_h };  // center of next arc
  int w = std::round (f * scale);

  spiral.push_back (new Graph_lib::Arc{ as_point(c), w, w, -180, 0 });

  Vec2d e{ -1, 0 };                   // center move direction
  int phi = -90;
  for (int i = 2; i < n_steps; ++i)
  {
    Shape& arc = spiral[ spiral.size() - 1 ];
    arc.set_style (st);
    arc.set_color (gold);

    win.attach (arc);

    c += std::round(fp * scale) * e;
    std::tie(f, fp) = fib_next(f, fp);
    w = std::round (f * scale);
    phi = (phi + 90) % 360;

    spiral.push_back (new Graph_lib::Arc{ as_point(c), w, w, phi, phi + 90 });

    e = rotated (-pi/2, e);
  }
  win.wait_for_button();
}


int main ()
try
{
  draw_fibonacci_spiral (480, 300);
}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
catch (...)
{
  std::cerr <<"Oops, something went wrong..."<< std::endl;
  return 2;
}
