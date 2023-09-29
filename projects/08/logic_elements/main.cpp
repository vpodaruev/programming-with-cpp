#include <iostream>

#include "Logic.h"

int main ()
{
  using logic::Element;
  using logic::ElementType;

  Element source1{ElementType::SIGNAL_ON};
  Element source2{ElementType::SIGNAL_OFF};
  Element add1{ElementType::ADD};
  Element add2{ElementType::ADD};
  Element or1{ElementType::OR};

  source1 >> ~~add1 >> ~add2;
  source2 >> ~~add1;

  // source1 >> source2; // runtime error

  source1 >> ~or1;
  source2 >> or1;

  std::cout << "Add1: " << add1.IsSignal() << ", Add2: " << add2.IsSignal()
            << ", Or1: " << or1.IsSignal() << std::endl;

  return 0;
}
