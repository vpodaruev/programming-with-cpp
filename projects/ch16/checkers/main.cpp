#include <exception>
#include <iostream>

#include "checkers.h"

using namespace Graph_lib;

int main ()
try
{
  Checkers win{Point{100, 100}};
  return gui_main();
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
