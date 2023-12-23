#ifndef FIGURE_H
#define FIGURE_H 1

#include <Graph_lib/Graph.h>
#include <Graph_lib/Window.h>

#include "cell.h"

struct Figure
{
  virtual bool is_black () const = 0;
  virtual void attach (const Cell& c) = 0;

  bool is_attached () const { return cell != nullptr; }

  void detach () { cell = nullptr; }

  virtual ~Figure() = default;

protected:
  const Cell* cell{nullptr};
};

struct Checker : Figure, Graph_lib::Circle
{
  Checker(Graph_lib::Window& win);

  void attach (const Cell& c) override;
  void draw_lines () const override;

private:
  static constexpr int r = 0.9 * Cell::size / 2;  // outer radius of checker
  static constexpr double f = 0.50;  // fraction of outer radius
};

struct WhiteChecker : Checker
{
  WhiteChecker(Graph_lib::Window& win);

  bool is_black () const override { return false; }
};

struct BlackChecker : Checker
{
  BlackChecker(Graph_lib::Window& win);

  bool is_black () const override { return true; }
};

#endif  // #ifndef FIGURE_H
