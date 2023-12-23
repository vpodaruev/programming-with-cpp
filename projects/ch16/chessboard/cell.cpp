#include "cell.h"

using namespace Graph_lib;

Cell::Cell(Point xy, Callback cb, Type t)
    : Button{xy, size, size, "", cb}, type{t}
{
  /* All done */
}

void Cell::attach(Graph_lib::Window& win)
{
  Button::attach(win);
  reset_color();
}

void Cell::activate()
{
  if (pw)
    pw->color(FL_SELECTION_COLOR);
}

void Cell::reset_color()
{
  if (!pw)
    error("Cell is not attached to a window");

  if (is_black())
    pw->color(Color::black);
  else
    pw->color(Color::white);
}
