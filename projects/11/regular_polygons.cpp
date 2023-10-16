// Draw a series of regular polygons, one inside the other. The innermost
// should be an equilateral triangle, enclosed by a square, enclosed by
// a pentagon, etc.

#include <exception>
#include <iostream>
#include <vector>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>

#include <poly/poly.h>

using namespace Graph_lib;

int main ()
try
{
  Point pos{100, 100};  // initial window position
  Simple_window win{pos, 410, 410, "Nested regular polygons"};

  constexpr int N{10};                               // number of polygons
  constexpr int minR{20};                            // minimum radius
  constexpr int maxR{200};                           // maximum radius
  Vec2d center{win.x_max() / 2., win.y_max() / 2.};  // window center
  std::vector<Color> purple{213, 212, 211, 210, 209, 208};

  Vector_ref<Closed_polyline> regular_poly;

  for (int i = 0, npoly = 3; i < N; ++i, ++npoly)
  {
    regular_poly.push_back(new Closed_polyline{});

    int r = minR + i * (maxR - minR) / (N - 1);  // polygon radius
    auto ngon = regular_polygon(npoly, center, r);
    append(regular_poly[i], ngon);

    int c = i * purple.size() / N;
    regular_poly[i].set_fill_color(purple[c]);
  }

  for (int i = N; i > 0; --i)         // reverse order to prevent
    win.attach(regular_poly[i - 1]);  // inner polygons from shadowing

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
