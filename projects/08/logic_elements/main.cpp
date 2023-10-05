#include <iostream>

#include "logic.h"

int main ()
{
  using logic::Element;
  using logic::ElementType;
  using logic::Operation;
  using logic::SignalState;
  using logic::SourceState;

  Element src1{SourceState::on};
  Element src2{SourceState::off};
  Element and1{Operation::and_op};
  Element and2{Operation::and_op, SignalState::inverted};
  Element or1{Operation::or_op};

  src1 >> and1 >> ~and2;
  src2 >> ~and1;

  //  src1 >> src2;  // runtime error

  src1 >> ~or1;
  src2 >> or1;

  std::cout << "src1: " << src1.signal() << ", src2: " << src2.signal()
            << ", and1: " << and1.signal() << ", and2: " << and2.signal()
            << ", or1: " << or1.signal() << std::endl;

  src2.set(SourceState::on);

  std::cout << "src1: " << src1.signal() << ", src2: " << src2.signal()
            << ", and1: " << and1.signal() << ", and2: " << and2.signal()
            << ", or1: " << or1.signal() << std::endl;
}
