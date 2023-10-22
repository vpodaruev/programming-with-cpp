#include <iostream>
#include <exception>

#include <Graph_lib/Simple_window.h>
#include <Graph_lib/ext/graph.h>

using namespace Graph_lib;


void tile_window ()
{
  Simple_window win{ Point{100, 100}, 600, 400, "Tile with hexagons" };

  Hexagon_tile tile{ Point{-20, -34},
                     win.x_max() + 40, win.y_max() + 60, 20 };
  win.attach (tile);

  win.wait_for_button();
}


void hexagon_tiles ()
{
  Simple_window win{ Point{100, 100}, 600, 400, "Hexagon tiles" };

  Hexagon_tile tile1{ Point{-50, -50}, 250, 200, 10 };
  win.attach (tile1);

  Hexagon_tile tile2{ Point{100, 75}, 350, 250, 20 };
  tile2.set_color (Color::black);
  win.attach (tile2);

  Hexagon_tile tile3{ Point{200, 200}, 450, 300, 40 };
  tile3.set_color (Color::red);
  tile3.set_style (Line_style{ Line_style::dot, 2 });
  tile3.set_fill_color (Color::dark_blue);
  win.attach (tile3);

  win.wait_for_button();
}


int main ()
try
{
  hexagon_tiles();
  tile_window();
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
