#include <iostream>

#include "board.h"

using namespace Graph_lib;

Cell::Type type_of_cell (int i, int j)
{
  if (i % 2 == 0)
    return (j % 2 == 0) ? Cell::black : Cell::white;
  else
    return (j % 2 == 0) ? Cell::white : Cell::black;
}

std::string letters ()
{
  std::string s(Chessboard::N_max, '\0');

  for (int i = 0; i < Chessboard::N_max; ++i)
    s[i] = 'a' + i;

  return s;
}

std::string digits ()
{
  std::string s(Chessboard::N_max, '\0');

  for (int i = 0; i < Chessboard::N_max; ++i)
    s[i] = '1' + i;

  return s;
}

Chessboard::Chessboard(Point xy, Graph_lib::Callback cb_clicked)
    : Widget{xy, size, size, "Chessboard", nullptr}, x_labels{letters()},
      y_labels{digits()}
{
  // board
  constexpr int cw = Cell::size;

  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
      Point pos{margin + i * cw, margin + (N - 1 - j) * cw};
      cells.push_back(new Cell{pos, cb_clicked, type_of_cell(i, j)});
    }
  }

  // labels
  constexpr Point lb{margin, margin + N * cw};  // left bottom board corner
  constexpr int dm = 10;                        // margin from cells

  for (int i = 0; i < N; ++i)
  {
    int dl = i * cw + cw / 2;  // distance from corner
    x_labels.add(Point{lb.x + dl, lb.y + dm});
    y_labels.add(Point{lb.x - dm, lb.y - dl});
  }
}

void Chessboard::show()
{
  for (int i = 0; i < cells.size(); ++i)
    cells[i].show();

  x_labels.set_color(Color::black);
  y_labels.set_color(Color::black);
}

void Chessboard::hide()
{
  for (int i = 0; i < cells.size(); ++i)
    cells[i].hide();

  x_labels.set_color(Color::invisible);
  y_labels.set_color(Color::invisible);
}

void Chessboard::move(int dx, int dy)
{
  for (int i = 0; i < cells.size(); ++i)
    cells[i].move(dx, dy);

  x_labels.move(dx, dy);
  y_labels.move(dx, dy);
}

void Chessboard::attach(Graph_lib::Window& win)
{
  for (int i = 0; i < cells.size(); ++i)
    win.attach(cells[i]);

  win.attach(x_labels);
  win.attach(y_labels);

  own = &win;
}

Cell& Chessboard::at(char c, int i)
{
  --i;  // the first cell has index 1
  int j = c - 'a';

  if (i < 0 || N <= i)
    error("Chessboard::at(): out of range (i = " + std::to_string(i) + ")");
  if (j < 0 || N <= j)
    error("Chessboard::at(): out of range (c = " + std::string{c} + ")");

  return cells[j * N + i];
}

auto Chessboard::where(Cell& c) const -> Position
{
  // find linear location in array
  int k = 0;
  for (; k < cells.size(); ++k)
  {
    if (&cells[k] == &c)
      break;
  }
  if (k == cells.size())
    error("Chessboard::where(): cell not found");

  // transform in board position
  int i = k / N;
  int j = k % N;
  return {'a' + i, j + 1};
}

Cell& Chessboard::get_selected()
{
  if (!selected)
    error("Chessboard::get_selected(): none of cells is selected");

  return *selected;
}

void Chessboard::select(Cell& c1)
{
  if (selected)
    selected->deactivate();

  if (selected != &c1)
  {
    selected = &c1;
    selected->activate();
  }
  else
    selected = nullptr;
}

void Chessboard::move_figure(Cell& c2)
{
  if (!has_selected())
    error("Chessboard::move_figure(): can't move, no selection");

  if (!selected->has_figure())
    error("Chessboard::move_figure(): can't move, no figure");

  Cell& c1 = *selected;
  select(c1);  // unselect

  c2.attach_figure(c1.detach_figure());
}

std::ostream& operator<< (std::ostream& os, const Chessboard::Position& p)
{
  return os << "(" << p.first << ", " << p.second << ")";
}
