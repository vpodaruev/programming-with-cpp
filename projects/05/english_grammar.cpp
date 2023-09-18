//
// A program that checks if a sentence is correct according to the
// “English” grammar:
//
// Sentence:
//   Noun Verb
//   Sentence Conjunction Sentence
// Conjunction:
//   "and"
//   "or"
//   "but"
// Noun:
//   "birds"
//   "fish"
//   "C++"
// Verb:
//   "rules"
//   "fly"
//   "swim"
//
// Assume that every sentence is terminated by a full stop (.) surrounded by
// whitespace. For example, birds fly but the fish swim . is a sentence, but
// birds fly but the fish swim (terminating dot missing) and birds fly but
// the fish swim. (no space before dot) are not. For each sentence entered,
// the program should simply respond “OK” or “not OK.”
//

#include <std_lib_facilities.h>

vector<string> noun_items{"birds", "fish", "C++"};
vector<string> verb_items{"rules", "fly", "swim"};
vector<string> conjunction_items{"and", "or", "but"};

bool contains (const vector<string>& items, const string& val)
{
  for (const auto& x : items)
  {
    if (x == val)
      return true;
  }
  return false;
}

bool sentence ()
{
  string word;

  while (cin)
  {
    cin >> word;
    if (!cin || !contains(noun_items, word))
      return false;

    cin >> word;
    if (!cin || !contains(verb_items, word))
      return false;

    cin >> word;
    if (cin)
    {
      if (word == ".")  // full stop
        return true;
      else if (!contains(conjunction_items, word))
        return false;
    }
  }
  return false;
}

int main ()
{
  while (cin)
  {
    bool ok = sentence();
    cout << (ok ? "OK" : "not OK") << endl;
  }
}
