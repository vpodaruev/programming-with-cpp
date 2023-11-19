// Compute the number of combinations of n things by k pieces.

#include <iostream>
#include <stdexcept>
#include <vector>

class Combinations
{
public:
  int operator() (int n, int k) { return compute(n, k); }

private:
  void allocate (int n);
  int compute (int n, int k);

  std::vector<std::vector<int>> cache;
  static constexpr int invalid{-1};
};

constexpr int Combinations::invalid;  // may be dropped since c++17

void Combinations::allocate(int n)
{
  size_t i = cache.size();
  cache.resize(n + 1);           // add rows from i to n+1,
  for (; i < cache.size(); ++i)  // initialize them
  {
    cache[i].resize(i + 1, invalid);  // with an invalid value
    cache[i][0] = cache[i][i] = 1;    // and borders are reset to 1
  }
}

int Combinations::compute(int n, int k)
{
  if (n < 0 || k < 0 || n < k)
    throw std::out_of_range{"invalid n or k"};

  if (n > static_cast<int>(cache.size()))
    allocate(n);

  if (cache[n][k] == invalid)
    cache[n][k] = compute(n - 1, k - 1) + compute(n - 1, k);

  return cache[n][k];
}

int main ()
try
{
  Combinations c;
  std::cout << c(50, 25) << std::endl;
}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
