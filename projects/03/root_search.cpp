#include <std_lib_facilities.h>


enum class SolverMethod
{
  binary,
  chords,
  newton
  // ...
};


struct SolverResult
{
  double       root;
  bool         valid;
  unsigned int stepsNumber;
  SolverMethod method;

  SolverResult () = delete;
};


auto solver_binary (double a, double b, double eps, double (*f)(double))
{
  assert (a < b && eps > 0.);

  unsigned steps{ 0 };
  double x{};

  while (b - a > eps)
  {
    x = 0.5 * (a + b);

    if (f(x) * f(a) <= 0.)
      b = x;
    else
      a = x;

    ++steps;
  }

  return SolverResult{ x, true, steps, SolverMethod::binary };
}


auto solver_chords (double a, double b, double eps, double (*f)(double))
{
  assert (abs(b - a) > 0. && eps > 0.);

  unsigned steps{ 0 };

  while (abs(b - a) > eps)
  {
    double fa = f(a);
    double fb = f(b);
    if (fb - fa == 0.)
      return SolverResult{ b, false, steps, SolverMethod::chords };

    double temp = b;
    b = a - fa * (b - a) / (fb - fa);
    a = temp;

    ++steps;
  }

  return SolverResult{ b, true, steps, SolverMethod::chords };
}


auto solver_newton (double a, double b, double eps, double (*f)(double))
{
  assert (abs(b - a) > 0. && eps > 0.);

  unsigned int steps{ 0 };
  const double dx{ eps * 0.1 };
  double x{ 0.5 * (a + b) };
  double x0{};

  do
  {
    x0 = x;
    double df = (f(x0 + dx) - f(x0)) / dx;
    if (df == 0.)
      return SolverResult{ 0., false, steps, SolverMethod::newton };

    x = x0 - f(x0) / df;

    ++steps;
  }
  while (abs(x - x0) > eps);

  return SolverResult{ x, true, steps, SolverMethod::newton };
}


auto solve_equation (double a, double b, double eps,
                     SolverMethod method, double (*f)(double))
{
  switch (method)
  {
  case SolverMethod::binary: return solver_binary (a, b, eps, f);
  case SolverMethod::chords: return solver_chords (a, b, eps, f);
  case SolverMethod::newton: return solver_newton (a, b, eps, f);
  }
  error ("unreachable code point");
}


void print_results (SolverResult res)
{
#define PRINT_METHOD(method)    \
  case method:    \
  cout << #method <<"\t";    \
  break

  switch (res.method)
  {
  PRINT_METHOD (SolverMethod::binary);
  PRINT_METHOD (SolverMethod::chords);
  PRINT_METHOD (SolverMethod::newton);
  default:
    error ("unreachable code point");
  }

#undef PRINT_METHOD

  if (res.valid)
    cout <<"x = "<< res.root
         <<"\t after "<< res.stepsNumber
         <<" steps"<< endl;
  else
    cout <<"root is not found"<< endl;
}


double any_func (double x)
{
  return (x - 1.) * (x + 1.) * x;
}


int main ()
{
  constexpr double eps = 1.e-5;  // root search precision

  vector<SolverMethod> methods
  {
    SolverMethod::binary,
    SolverMethod::chords,
    SolverMethod::newton
  };

  double a = 3., b = 4.;
  for (auto method : methods)
  {
    auto res = solve_equation (a, b, eps, method, sin);
    print_results (res);
  }

  a = 0.5, b = 4.;
  for (auto method : methods)
  {
    auto res = solve_equation (a, b, eps, method, any_func);
    print_results (res);
  }
}
