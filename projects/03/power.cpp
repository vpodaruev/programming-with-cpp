/// @file power.cpp
/// Various implementations of the power function with integer powers.

#include <std_lib_facilities.h>

/// @brief Power function.
/// @returns @a x in the power of @a n.
/// @par Requirement
/// @a x must be non-zero if @a n is negative.
double pow (double x, int n)
{
  if (n < 0)
    x = 1. / x, n = -n;

  double res{1.};

  for (int i = 0; i < n; ++i)
    res *= x;

  return res;
}

/// @brief Recursive version of @ref pow(double, int).
double pow_r (double x, int n)
{
  if (n == 0)
    return 1.;  // ok, stop recursion

  if (n < 0)
    x = 1. / x, n = -n;

  return x * pow_r(x, n - 1);  // invoke recursively
}

/// @brief An optimized version of @ref pow_r(double, int).
/// @note The idea is to reduce the number of multiplications:
/// @f[
///     x^n = \left\{ \begin{array}{l}
///             (x\cdot x)^k, \text{if}~n = 2k, \\
///             x\cdot x^{n-1}, \text{if}~n = 2k+1.
///           \end{array}\right.
/// @f]
/// @par Complexity
/// Logarithmic.
double pow_opt (double x, int n)
{
  if (n == 0)
    return 1.;

  if (n < 0)
    x = 1. / x, n = -n;

  if (n % 2 == 0)
    return pow_opt(x * x, n / 2);  // optimized branch

  return x * pow_opt(x, n - 1);  // ordinary branch
}

void test_pow (double x, double tol)
{
  for (auto n : {0, -1, 1, -2, 2, -5, 5})
  {
    cout << "x = " << x << ", "
         << "n = " << n << ":" << endl;

    double etalon = std::pow(x, n);
    cout << "std::pow " << etalon << endl;

    using Func = double (*)(double, int);

#define FUN_NAME(function) make_pair(Func{function}, string{#function})

    auto powers = {FUN_NAME(pow), FUN_NAME(pow_r), FUN_NAME(pow_opt)};

#undef FUN_NAME

    for (auto [f, name] : powers)  // C++17
    {
      cout << setw(8) << left << name << " " << flush;

      double p = f(x, n);
      double diff = p - etalon;

      cout << p << " (difference is " << diff << ")"
           << "  [" << (abs(diff) < tol ? "OK" : "FAILED") << "]" << endl;
    }
    cout << "\n";
  }
}

int main ()
{
  constexpr double x = 1.3567;
  constexpr double tol = numeric_limits<double>::epsilon();

  test_pow(x, tol);
}
