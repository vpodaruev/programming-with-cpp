/* A variant of a solution of the exercise 7 from chapter 8.
 *
 * Read five names into a vector<string> name, then prompt the user for the
 * ages of the people named and store the ages in a vector<double> age. Then
 * print out the five (name[i], age[i]) pairs. Sort the names
 * (sort(name.begin(), name.end())) and print out the (name[i], age[i])
 * pairs. The tricky part here is to get the age vector in the correct order
 * to match the sorted name vector.
 *
 * Hint: Before sorting name, take a copy and use that to make a copy of age
 * in the right order after sorting name. Then, do that exercise again but
 * allowing an arbitrary number of names. We do the final part of the
 * exercise, allowing an arbitrary number of names.
 */

#include <std_lib_facilities.h>

int find_next (const vector<string>& arr, const string& val, int start_pos)
{
  for (size_t i = start_pos; i < arr.size(); ++i)
  {
    if (val == arr[i])
      return i;
  }
  error("value '" + val + "' not found");
}

auto sync_age (const vector<string>& name, const vector<string>& name_old,
               const vector<int>& age_old)
{
  vector<int> age(age_old.size(), -1);

  for (size_t i = 0; i < name.size();)
  {
    const string& item = name[i];
    int pos = 0;
    for (; i < name.size() && item == name[i]; ++i)  // equal range
    {
      pos = find_next(name_old, item, pos);
      age[i] = age_old[pos];
      ++pos;
    }
  }  // for i

  return age;
}

void sort (vector<string>& name, vector<int>& age)
{
  if (name.size() != age.size())
    error("dimension mismatch");

  vector<string> name_old{name};
  sort(name.begin(), name.end());
  age = sync_age(name, name_old, age);
}

void input (vector<string>& name, vector<int>& age)
{
  vector<string> name_loc;
  vector<int> age_loc;

  string s;
  int i = -1;
  while (cin >> s >> i)
  {
    name_loc.push_back(s);
    age_loc.push_back(i);
  }

  name = name_loc;
  age = age_loc;
}

void print (const vector<string>& name, const vector<int>& age)
{
  for (size_t i = 0; i < name.size(); ++i)
    cout << (i + 1) << ". " << name[i] << " " << age[i] << "\n";
}

int main ()
try
{
  vector<string> name;
  vector<int> age;

  cout << "Enter name and age pairs:" << endl;
  input(name, age);

  cout << "Original name/age pairs:" << endl;
  print(name, age);

  sort(name, age);

  cout << '\n' << "Sorted name/age pairs:" << endl;
  print(name, age);
}
catch (exception& e)
{
  cerr << "exception: " << e.what() << endl;
  return 1;
}
catch (...)
{
  cerr << "Oops, unknown exception" << endl;
  return 2;
}
