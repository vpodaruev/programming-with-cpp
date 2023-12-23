#ifndef CHECKERS_H
#define CHECKERS_H 1

#include <Graph_lib/Window.h>

#include "board.h"
#include "cell.h"
#include "figure.h"

using Graph_lib::Address;
using Graph_lib::Point;

struct Checkers : Graph_lib::Window
{
  Checkers(Point xy);

private:
  Chessboard board;
  Graph_lib::Vector_ref<Figure> checkers;

  static void cb_clicked (Address, Address widget)
  {
    auto& btn = Graph_lib::reference_to<Cell>(widget);
    dynamic_cast<Checkers&>(btn.window()).clicked(btn);
  }

  void clicked (Cell& c2);
};

#endif  // #ifndef CHECKERS_H
