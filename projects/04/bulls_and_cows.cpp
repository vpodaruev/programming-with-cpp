// A little guessing game called
//    (for some obscure reason) <<Bulls and Cows>>.

#include <std_lib_facilities.h>

int count (const vector<char>& digits, char d)
{
  int k{};

  for (int i = 0; i < digits.size(); ++i)
    if (digits[i] == d)
      ++k;

  return k;
}

void validate (const vector<char>& number)
{
  for (int i = 0; i < number.size(); ++i)
  {
    if (number[i] < '0' || '9' < number[i])
      error("the number contains not a digit");

    if (count(number, number[i]) != 1)
      error("digits of the number are not unique");
  }
}

vector<char> user_guess ()
{
  vector<char> number(4);

  cout << "guess the number: ";
  for (int i = 0; i < number.size(); ++i)
    cin >> number[i];

  if (!cin)
    error("invalid input");

  validate(number);

  return number;
}

int main ()
try
{
  cout << "<<Bulls and Cows>>\n"
       << "Computer sets a number of 4 unique digits.\n"
       << "Try to guess it.\n"
       << "<Bull> means right digit in the right position.\n"
       << "<Cow> means right digit in the wrong position.\n"
       << "\n"
       << "game is on" << endl;

  vector<char> number{'1', '3', '7', '2'};

  int bulls{};

  do
  {
    bulls = 0;
    int cows{};

    vector<char> uguess = user_guess();

    for (int i = 0; i < uguess.size(); ++i)
    {
      if (uguess[i] == number[i])
        ++bulls;
      else if (count(number, uguess[i]) == 1)
        ++cows;
    }

    cout << bulls << " bull(s) and " << cows << " cow(s)" << endl;
  }
  while (bulls != 4);

  cout << "game is over" << endl;
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
