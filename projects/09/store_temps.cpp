// An exercise 2 from chapter 10
// Write a program that creates a file of data in the form of the
// temperature Reading type defined in §10.5. For testing, fill
// the file with at least 50 "temperature readings". Call this program
// store_temps.cpp and the file it creates raw_temps.txt.

#include <std_lib_facilities.h>

struct Reading  /// a temperature reading
{
  int hour;            /// hour after midnight [0:23]
  double temperature;  /// in Celsius
};

double normreal (double mean, double stddev)
{
  static default_random_engine ran;
  return normal_distribution<>{mean, stddev}(ran);
}

const double pi = 4. * atan(1.);

auto generate_temps ()
{
  constexpr int n_hours = 24;
  constexpr double ave = 10.;        // average day temperature
  constexpr double ampl = 5.;        // amplitude of deviations
  constexpr double phase = 6. - 14;  // shift for a temperature maximum
  constexpr double std_dev = 0.5;    // standard deviation

  vector<Reading> temps{50};
  for (Reading& r : temps)
  {
    r.hour = randint(n_hours - 1);
    double mean = ave + ampl * sin(2. * pi * (r.hour + phase) / n_hours);
    r.temperature = normreal(mean, std_dev);
  }

  return temps;
}

void store_temps (const string& filename, const vector<Reading>& temps)
{
  ofstream ofs{filename};
  if (!ofs)
    error("can't open file '" + filename + "' to write");

  for (const Reading& r : temps)
    ofs << r.hour << " " << r.temperature << '\n';
}

int main ()
try
{
  auto temps = generate_temps();
  store_temps("raw_temps.txt", temps);
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
