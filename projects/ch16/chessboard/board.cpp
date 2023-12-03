#include <iostream>

#include "board.h"

using namespace Graph_lib;

My_window::My_window(Point xy, int w, int h, const std::string& title)
    : Simple_window{xy, w, h, title},
      quit_button{Point{x_max() - 70, 20}, 70, 20, "Quit", cb_quit}
{
  attach(quit_button);
}

void My_window::cb_quit(Address, Address widget)
{
  auto& btn = Graph_lib::reference_to<Graph_lib::Button>(widget);
  dynamic_cast<My_window&>(btn.window()).quit();
}

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

Chessboard::Chessboard(Point xy)
    : My_window{xy, width, height, "Chessboard"}, x_labels{letters()},
      y_labels{digits()}
{
  size_range(width, height, width, height);  // fixed window size

  // board
  constexpr int cw = Cell::size;

  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
      Point pos{margin + i * cw, margin + (N - 1 - j) * cw};
      cells.push_back(new Cell{pos, cb_clicked, type_of_cell(i, j)});
      attach(cells[cells.size() - 1]);
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
  attach(x_labels);
  attach(y_labels);
}

void Chessboard::clicked(Cell& c)
{
  if (!selected)
  {
    selected = &c;
    c.activate();
  }
  else
  {
    selected->deactivate();

    if (selected == &c)  // reset selection
    {
      selected = nullptr;
    }
    else  // choose another cell
    {
      selected = &c;
      c.activate();
    }
  }
  Fl::redraw();
}
