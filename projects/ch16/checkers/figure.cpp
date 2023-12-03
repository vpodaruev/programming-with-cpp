#include "figure.h"

using namespace Graph_lib;

Checker::Checker(Graph_lib::Window& win) : Circle{Point{0, 0}, r}
{
  set_style(Line_style{Line_style::solid, 2});
  win.attach(*this);
}

void Checker::attach(const Cell& c)
{
  if (is_attached())
    error("Checker::attach(): already attached");

  cell = &c;
  move(c.center().x - center().x, c.center().y - center().y);
}

void Checker::draw_lines() const
{
  Circle::draw_lines();

  if (color().visibility())
  {
    int r = f * radius();
    fl_arc(center().x - r, center().y - r, r + r, r + r, 0, 360);
  }
}

namespace {

const Color white{17};  // near white, to separate from cell's white
const Color black{30};  // near black, to separate from cell's black

}  // namespace

WhiteChecker::WhiteChecker(Graph_lib::Window& win) : Checker{win}
{
  set_color(black);  // checker's edge color
  set_fill_color(white);
}

BlackChecker::BlackChecker(Graph_lib::Window& win) : Checker{win}
{
  set_color(white);  // checker's edge color
  set_fill_color(black);
}
