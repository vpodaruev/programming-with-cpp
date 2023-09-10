#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cassert>


/*!
 * Find all primes up to @a max using
 * algorithm of the Eratosthenes sieve
 */
auto eratosthen_sieve (int max)
{
  assert (max > 1);

  // apply the sieve
  std::vector<bool> sieved (max+1, false);

  for (int i = 2; i*i <= max; ++i)
  {
    if (!sieved[i])
    {
      int step = (i != 2) ? 2*i : i;

      for (int j = i*i; j <= max; j += step)
        sieved[j] = true;
    }
  }

  // collect primes
  std::vector<int> primes;

  for (int i = 2; i <= max; ++i)
    if (!sieved[i]) primes.push_back(i);

  return primes;
}


bool is_prime (int x)
{
  for (int i = 2; i*i <= x; ++i)
    if (x % i == 0) return false;

  return true;
}


int main ()
{
  for (int max : {-1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 10000})
  {
    std::cout <<"max "<< max <<": ";
    for (auto p : eratosthen_sieve (max))
    {
      if (!is_prime (p))
        throw std::runtime_error{"not a prime ("+ std::to_string(p) +")"};
      std::cout << p <<' ';
    }
    std::cout << std::endl;
  }
}
