// Draw a Koch snowflake fractal curve

#include <exception>
#include <iostream>
#include <list>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>

#include <poly/poly.h>
#include <vec/vec2d.h>

using namespace Graph_lib;

/**
 * Apply Koch fractal for each segment of a closed polyline
 *             o m
 *   prev     / \     curr
 *     x --- o   o --- x
 *    /      p   q      \
 * @param curve - closed polyline as points list
 * @return modified points list back
 */
auto koch_fractal_step (std::list<Vec2d>&& curve)
{
  auto prev = --curve.end();
  for (auto curr = curve.begin(); curr != curve.end(); ++curr)
  {
    auto p = lerp(*prev, *curr, 1. / 3);
    auto q = lerp(*prev, *curr, 2. / 3);
    auto m = rotated(-pi / 3, p, q);
    curve.insert(curr, p);
    curve.insert(curr, m);
    curve.insert(curr, q);
    prev = curr;
  }
  return curve;
}

auto max_edge_length (const std::list<Vec2d>& curve)
{
  double d = 0.;  // minimum edge length
  auto prev = --curve.end();
  for (auto curr = curve.begin(); curr != curve.end(); ++curr)
  {
    d = std::max(d, length(*curr - *prev));
    prev = curr;
  }
  return d;
}

void draw_koch_snowflake (int w, int n)
{
  Simple_window win{Point{100, 100}, w, w, "Koch snowflake"};

  Vec2d c{w / 2., w / 2.};  // window center
  double r{0.85 * w / 2.};  // polygon radius
  auto ngon = regular_polygon(n, c, r, -pi / 2.);

  Text n_steps{as_point(c), "0"};
  n_steps.set_color(Color::blue);
  win.attach(n_steps);

  for (bool is_fine = false; !is_fine;)
  {
    Closed_polyline curve;
    append(curve, ngon);
    curve.set_color(Color::blue);

    ngon = koch_fractal_step(std::move(ngon));
    is_fine = max_edge_length(ngon) < 1.0;
    if (is_fine)
      n_steps.set_color(Color::red);

    win.attach(curve);
    win.wait_for_button();

    win.detach(curve);
    n_steps.set_label(std::to_string(std::stoi(n_steps.label()) + 1));
  }
}

void help (const char prog[])
{
  std::cerr << "Generate Koch fractal on a regular polygon\n\n"
               "Usage: "
            << prog
            << " [-h|--help] [window width] [number of polygon vertex]\n"
            << std::endl;
}

int main (int argc, char* argv[])
try
{
  int w = 410;  // window width
  int n = 3;    // number of initial polygon vertex

  // handle command line arguments
  if (argc > 1)
    w = std::stoi(argv[1]);
  if (argc > 2)
    n = std::stoi(argv[2]);
  if (argc > 3)  // unexpectedly too much arguments
  {
    help(argv[0]);
    return 2;
  }

  draw_koch_snowflake(w, n);
}
catch (std::invalid_argument& e)
{
  // check if user asks help
  for (int i = 1; i < argc; ++i)
  {
    std::string arg{argv[i]};
    if (arg == "-h" || arg == "--help")
    {
      help(argv[0]);
      return 2;
    }
  }

  // else expected an integer
  std::cerr << e.what() << ": not an integer\n" << std::endl;
  return 2;
}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
catch (...)
{
  std::cerr << "Oops, something went wrong..." << std::endl;
  return 2;
}
