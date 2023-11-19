#ifndef CELL_H
#define CELL_H 1

#include <Graph_lib/GUI.h>

using Graph_lib::Point;

struct Cell : Graph_lib::Button
{
  enum Type
  {
    black,
    white
  };

  static constexpr int size = 100;

  Cell(Point xy, Graph_lib::Callback cb, Type t);

  void attach (Graph_lib::Window& win) override;

  void activate ();

  void deactivate () { reset_color(); }

  bool is_black () const { return type == black; }

private:
  Type type;

  void reset_color ();
};

#endif  // #ifndef CELL_H
