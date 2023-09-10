#include <cmath>
#include <iostream>
#include <string>
#include <utility>


double f (double x)
{
  return std::sin(x);
}


// Computes integral from a to b by rectangle rule.
double integrate_rectangle (double a, double b, int N)
{
  double h{ (b - a) / N };
  double sum{};

  for (int i = 0; i < N; ++i)
    sum += f(a + i*h);

  return h * sum;
}


// Computes integral from a to b by trapezoid rule.
double integrate_trapezium (double a, double b, int N)
{
  double h{ (b - a) / N };
  double sum{};

  for (int i = 1; i < N; ++i)
    sum += f(a + i*h);

  return h * (0.5*f(a) + sum + 0.5*f(b));
}


// Computes integral from a to b by Simpson rule.
double integrate_simpson (double a, double b, int N)
{
  const double h{ (b - a) / (2*N) };
  double sum{};

  for (int i = 1; i <= N; ++i)
    sum += 4*f(a + (2*i-1)*h) + 2*f(a + 2*i*h);

  return h/3. * (f(a) + sum - f(b));
}


int main ()
{
  const double a = 0., b = 2.*std::atan(1.);

  std::cout <<"integral from a = "<< a <<" to b = "<< b << std::endl;
  constexpr double exact = 1.;


  using Func = double (*)(double, double, int);

#define FUN_NAME(function) \
        std::make_pair(Func{function}, std::string{#function})

  auto integrators = {
    FUN_NAME(integrate_rectangle),
    FUN_NAME(integrate_trapezium),
    FUN_NAME(integrate_simpson)
  };

#undef FUN_NAME


  std::cout.precision(15);

  for (int N : {1, 10, 100, 1000})
  {
    std::cout <<"N = "<< N << std::endl;

    for (auto [fun, name] : integrators)
    {
      double res = fun (a, b, N);

      std::cout << name <<": "<< res
                <<", err = "<< std::abs(exact - res) << std::endl;
    }
  }
}
