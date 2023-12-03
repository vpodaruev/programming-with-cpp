#include "cell.h"
#include "figure.h"

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

Point Cell::center() const
{
  return Point{loc.x + width / 2, loc.y + height / 2};
}

void Cell::attach_figure(Figure& ch)
{
  if (fig)
    error("Cell::attach_figure(): already has a figure");

  ch.attach(*this);
  fig = &ch;
}

Figure& Cell::detach_figure()
{
  if (!fig)
    error("Cell::detach_figure(): no figure");

  Figure* p = fig;
  fig = nullptr;
  p->detach();
  return *p;
}

const Figure& Cell::figure() const
{
  if (!fig)
    error("Cell::figure(): no figure");

  return *fig;
}

void Cell::reset_color()
{
  if (!pw)
    error("Cell::reset_color(): cell is not attached to a window");

  if (is_black())
    pw->color(Color::black);
  else
    pw->color(Color::white);
}
