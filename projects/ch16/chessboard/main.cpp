#include <exception>
#include <iostream>

#include "board.h"

using namespace Graph_lib;

int ex_my_window ()
{
  My_window win{Point{100, 100}, 600, 50, "My window"};
  win.wait_for_button();
  return gui_main();
}

int ex_chessboard ()
{
  Chessboard board{Point{100, 100}};
  return gui_main();
}

int main ()
try
{
//  ex_my_window();
  ex_chessboard();
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
