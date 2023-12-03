#ifndef BOARD_H
#define BOARD_H

#include <ostream>
#include <utility>

#include "cell.h"

using Graph_lib::Address;
using Graph_lib::Point;

struct Chessboard : Graph_lib::Widget
{
  static constexpr int N = 4;  // board N by N
  static constexpr int margin = 30;
  static constexpr int size = N * Cell::size + 2 * margin;

  using Position = std::pair<char, int>;

  Chessboard(Point xy, Graph_lib::Callback cb_clicked);

  void show () override;
  void hide () override;
  void move (int dx, int dy) override;

  void attach (Graph_lib::Window& win) override;

  Cell& at (char c, int i);
  Position where (Cell& c) const;

  bool has_selected () const { return selected != nullptr; }

  Cell& get_selected ();

  void select (Cell& c1);  // toggle selection
  void move_figure (Cell& c2);

  static constexpr int N_max = 8;
  static_assert(N <= N_max,
                "do not allow board larger than N_max by N_max");

private:
  Graph_lib::Vector_ref<Cell> cells;
  Graph_lib::Marks x_labels;
  Graph_lib::Marks y_labels;

  Cell* selected{nullptr};  // activated cell
};

std::ostream& operator<< (std::ostream& os, const Chessboard::Position& p);

#endif  // #ifndef BOARD_H
