#include <iostream>
#include <exception>

#include <Graph_lib/Simple_window.h>
#include <Graph_lib/ext/graph.h>

using namespace Graph_lib;


int main ()
try
{
  Simple_window win{Point{100, 100}, 300, 200, "Arcs"};

  Line_style st{Line_style::solid, 2};
  Vector_ref<Shape> face;

  Arc smile{Point{150, 100}, 60, 50, -30, -150};
  smile.set_style(st);
  smile.set_fill_color(Color::red);
  face.push_back(smile);

  int y = smile.center().y - 20;
  Arc eye_l{Point{smile.center().x - 30, y}, 10, 5, 0, 180};
  eye_l.set_style(st);
  face.push_back(eye_l);
  Arc eye_r{Point{smile.center().x + 30, y}, 10, 5, 0, 180};
  eye_r.set_style(st);
  face.push_back(eye_r);

  Arc ear_l{Point{smile.center().x - smile.major(), y}, 10, 20, 90, 270};
  ear_l.set_fill_color(Color::yellow);
  face.push_back(ear_l);
  Arc ear_r{Point{smile.center().x + smile.major(), y}, 10, 20, -90, 90};
  ear_r.set_fill_color(Color::yellow);
  face.push_back(ear_r);

  Mark nose{smile.center(), 'J'};
  face.push_back(nose);

  for (int i = 0; i < face.size(); ++i)
    win.attach(face[i]);

  win.wait_for_button();


  win.set_label("Boxes");

  Box edge{smile.point(0), 2*smile.major(), 2*smile.minor()};
  face.push_back(edge);

  constexpr int m = 25;  // margin
  Box frame{Point{smile.point(0).x - m, smile.point(0).y - m},
            2*(smile.major() + m), 2*(smile.minor() + m)};
  frame.set_style(st);
  frame.set_color(Color::magenta);
  frame.set_fill_color(Color::white);
  win.attach(frame);

  Box b1{Point{m/2, m/2}, win.x_max() - m, win.y_max() - m, 2};
  win.attach(b1);
  Box b2{b1.point(0), win.x_max() - m, win.y_max() - m};
  b2.set_color(Color::magenta);
  win.attach(b2);

  for (int i = 0; i < face.size(); ++i)
    win.put_on_top(face[i]);

  win.wait_for_button();
}
catch (std::exception & e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
catch (...)
{
  std::cerr <<"Oops, something went wrong..."<< std::endl;
  return 2;
}
