#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <tuple>

#include <Graph_lib/Simple_window.h>
#include <Graph_lib/ext/graph.h>
#include <poly/poly.h>


using namespace Graph_lib;


void cross_wheel (int win_w)
{
  Point win_lt{ 100, 100 };       // window left top corner
  Simple_window win{ win_lt, win_w, win_w, "Cross wheel" };

  Line_style st{ Line_style::solid, 4 };
  Vector_ref<Graph_lib::Arc> cross;

  int w = 0.30 * win_w/2;
  int h = 0.95 * win_w/2;
  double d = 0.38 * win_w/2;
  Vec2d c{ win_w/2., win_w/2. };  // center of cross

  cross.push_back (new Graph_lib::Arc{ as_point(c + Vec2d{  d,  0 }), w, h, 110,  250 });
  cross.push_back (new Graph_lib::Arc{ as_point(c + Vec2d{ -d,  0 }), w, h, -70,   70 });
  cross.push_back (new Graph_lib::Arc{ as_point(c + Vec2d{  0,  d }), h, w,  20,  160 });
  cross.push_back (new Graph_lib::Arc{ as_point(c + Vec2d{  0, -d }), h, w, -20, -160 });

  Mark m{ as_point(c), 'o' };
  m.set_style (st);
  m.set_color (Color::dark_red);
  win.attach (m);

  for (int i = 0; i < cross.size(); ++i)
  {
    cross[i].set_style (st);
    cross[i].set_color (Color::dark_red);

    win.attach (cross[i]);
  }
  win.wait_for_button();
}


int main ()
try
{
  cross_wheel (400);
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
