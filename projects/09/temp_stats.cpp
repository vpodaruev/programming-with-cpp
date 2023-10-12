// An exercise 3 from chapter 10
// Write a program that reads the data from raw_temps.txt created
// in exercise 2 into a vector and then calculates the mean and median
// temperatures in your data set. Call this program temp_stats.cpp.

#include <std_lib_facilities.h>

struct Reading  /// a temperature reading
{
  int hour;            /// hour after midnight [0:23]
  double temperature;  /// in Celsius
};

istream& operator>> (istream& is, Reading& r)
{
  int h;
  double t;
  if (is >> h >> t)
    r = Reading{h, t};
  return is;
}

auto read_temps (const string& filename)
{
  ifstream ifs{filename};
  if (!ifs)
    error("can't open file '" + filename + "' to read");

  ifs.exceptions(ifs.exceptions() | ios_base::badbit);

  vector<Reading> temps;
  for (Reading r; ifs >> r;)
    temps.push_back(r);

  if (ifs.eof())  // fine: we found the end of file
    return temps;

  error("not a reading encountered");
}

auto temp_stats (vector<Reading> temps)  // here we make a copy
{
  assert(!temps.empty());

  const unsigned n = temps.size();

  double mean{};
  for (const Reading& r : temps)
    mean += r.temperature;
  mean /= n;

  sort(temps.begin(), temps.end(),
       [] (const auto& a, const auto& b)
       { return a.temperature < b.temperature; });
  unsigned m = n / 2;
  double median{};
  if (n % 2)
    median = temps[m].temperature;
  else
    median = 0.5 * (temps[m - 1].temperature + temps[m].temperature);

  return make_pair(mean, median);
}

int main ()
try
{
  auto temps = read_temps("raw_temps.txt");
  auto [mean, median] = temp_stats(temps);  // C++17

  cout << "Mean temperature is " << mean << " C\n"
       << "Median of the set is " << median << " C" << endl;
}
catch (exception& e)
{
  cerr << e.what() << endl;
  return 1;
}
catch (...)
{
  cerr << "Oops, something went wrong..." << endl;
  return 2;
}
