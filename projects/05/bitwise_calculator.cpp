//
// A bitwise logical expression is much like an arithmetic expression except
// that the operators are ! (not), ~ (complement), & (and), | (or), and ^
// (exclusive or). Each operator does its operation to each bit of its
// integer operands (see §25.5). ! and ~ are prefix unary operators. A ^
// binds tighter than a | (just as * binds tighter than +) so that x|y^z
// means x|(y^z) rather than (x|y)^z. The & operator binds tighter than ^ so
// that x^y&z means x^(y&z).
//

/*
  Grammar of a bitwise logical expression.

  Expression:
    Term
    Expression "|" Term
  Term:
    Subterm
    Term "^" Subterm
  Subterm:
    Primary
    Subterm "&" Primary
  Primary:
    Number
    "(" Expression ")"
    "!" Primary
    "~" Primary
  Number:
    integer_literal

*/

#include <std_lib_facilities.h>

int expression ()
{
  // to be implemented
}

int main ()
try
{
  int val{};

  while (cin)
  {
    Token t = ts.get();

    if (t.kind == 'q')
      break;            // 'q' for quit
    if (t.kind == ';')  // ';' for "print now"
      cout << "=" << val << '\n';
    else
      ts.putback(t);

    val = expression();
  }
}
catch (exception& e)
{
  cerr << "error: " << e.what() << '\n';
  return 1;
}
catch (...)
{
  cerr << "Oops: unknown exception!\n";
  return 2;
}
