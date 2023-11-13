#include <iostream>
#include <sstream>
#include <exception>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Window.h>
#include <Graph_lib/Simple_window.h>

#include "logic.h"
#include "logic_shapes.h"


int main ()
try
{
  int win_w = 600;
  int win_h = 400;
  Graph_lib::Point lt{ Graph_lib::x_max()/2 - win_w/2, Graph_lib::y_max()/2 - win_h/2 };
  Simple_window win{ lt, win_w, win_h, "Scheme of Logic Elements" };
  //win.wait_for_button();

  using namespace Logic;

  //
  Source src1;
  Source src2;
  Source src3;
  Source src4;
  Source src5;
  Source src6;
  Source src7;

  And and1;
  And and2;
  And and3;
  And and4;
  And and5;
  And and6;
  And and7{ Out_state::inverted };
  And and8{ Out_state::inverted };

  Or or1;
  Or or2;
  Or or3;

  //
  src2 >> ~and1;
  src4 >> ~and1 >> or2 >> and5 >> and7;
  src3 >> ~and2 >> or2;
  src5 >> ~and2;

  src6 >> and5;
  src6 >> and6;

  src7 >> and7;
  src7 >> and8;

  src4 >>  and3;
  src2 >> ~and3 >> or3 >> ~and5;
  src5 >>  and4 >> or3;
  src3 >> ~and4;
  src1 >> ~or1 >> or3 >> and6 >> and8;
  src1 >> ~or1;

  //
  SchemeShape scheme{ Graph_lib::Point{5, 5}, win_w - 80, win_h - 10 };

  win.attach(scheme);

  auto column_x = [] (double c) -> int
  {
    return int(30 + 100 * c);
  };

  auto line_y = [] (double l) -> int
  {
    return int(40 + 75 * l);
  };

  SourceShape src_shape1{ scheme, src1, "src1", Graph_lib::Point{ column_x(0), line_y(4) } };
  SourceShape src_shape2{ scheme, src2, "src2", Graph_lib::Point{ column_x(0), line_y(0) } };
  SourceShape src_shape3{ scheme, src3, "src3", Graph_lib::Point{ column_x(0), line_y(1) } };
  SourceShape src_shape4{ scheme, src4, "src4", Graph_lib::Point{ column_x(0), line_y(2) } };
  SourceShape src_shape5{ scheme, src5, "src5", Graph_lib::Point{ column_x(0), line_y(3) } };
  SourceShape src_shape6{ scheme, src6, "src6", Graph_lib::Point{ column_x(2), line_y(2) } };
  SourceShape src_shape7{ scheme, src7, "src7", Graph_lib::Point{ column_x(3), line_y(2) + 5 } };

  AndShape and_shape1{ scheme, and1, "and1", Graph_lib::Point{ column_x(1), line_y(0) + 5 } };
  AndShape and_shape2{ scheme, and2, "and2", Graph_lib::Point{ column_x(1), line_y(1) + 5 } };
  AndShape and_shape3{ scheme, and3, "and3", Graph_lib::Point{ column_x(1), line_y(2) + 5 } };
  AndShape and_shape4{ scheme, and4, "and4", Graph_lib::Point{ column_x(1), line_y(3) + 5 } };
  AndShape and_shape5{ scheme, and5, "and5", Graph_lib::Point{ column_x(3), line_y(1) + 6 }, DEFAULT_WIDTH, DEFAULT_HEIGHT + DEFAULT_HEIGHT / 3 };
  AndShape and_shape6{ scheme, and6, "and6", Graph_lib::Point{ column_x(3), line_y(3) } };
  AndShape and_shape7{ scheme, and7, "and7", Graph_lib::Point{ column_x(4), line_y(1) + 17 } };
  AndShape and_shape8{ scheme, and8, "and8", Graph_lib::Point{ column_x(4), line_y(3) - 5 } };

  OrShape or_shape1{ scheme, or1, "or1", Graph_lib::Point{ column_x(1), line_y(4) } };
  OrShape or_shape2{ scheme, or2, "or2", Graph_lib::Point{ column_x(2), line_y(1) } };
  OrShape or_shape3{ scheme, or3, "or3", Graph_lib::Point{ column_x(2), line_y(3) }, DEFAULT_WIDTH, DEFAULT_HEIGHT + DEFAULT_HEIGHT / 3  };

  scheme.update_connections();

  win.wait_for_button();

  src1 = true;
  src6 = true;
  src7 = true;

  win.wait_for_button();

  src4 = true;

  win.wait_for_button();
  return 0;
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
