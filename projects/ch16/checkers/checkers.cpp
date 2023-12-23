#include "checkers.h"
#include "utils.h"

using namespace Graph_lib;

Checkers::Checkers(Point xy)
    : Window{xy, Chessboard::size, Chessboard::size, "Checkers"},
      board{Point{0, 0}, cb_clicked}
{
  size_range(Chessboard::size, Chessboard::size, Chessboard::size,
             Chessboard::size);  // fixed window size

  board.attach(*this);

  using Positions = std::vector<Chessboard::Position>;

  for (auto [c, j] : Positions{{'a', 1}, {'c', 1}})
  {
    checkers.push_back(new BlackChecker{*this});
    board.at(c, j).attach_figure(checkers[checkers.size() - 1]);
  }

  for (auto [c, j] : Positions{{'b', 4}, {'d', 4}})
  {
    checkers.push_back(new WhiteChecker{*this});
    board.at(c, j).attach_figure(checkers[checkers.size() - 1]);
  }
}

void Checkers::clicked(Cell& c2)
{
  DEBUG_OUT(board.where(c2));

  if (!c2.is_black())
    return;

  if (c2.has_figure())
    board.select(c2);
  else if (board.has_selected())
    board.move_figure(c2);

  Fl::redraw();
}
