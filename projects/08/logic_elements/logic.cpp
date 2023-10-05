#include <stdexcept>

#include "logic.h"

namespace {

using logic::Element;

void check_loop (const Element& loop, const Element& elem)
{
  if (&loop == &elem)
    throw std::runtime_error{"loop detected"
                             " in connections of logic elements"};

  for (const auto& out : loop.outputs())
    check_loop(out, elem);
}

}  // namespace

namespace logic {

Input::Input(Element& elem, SignalState st)
    : m_elem{elem}, m_inv{st == SignalState::inverted}
{
}

bool Input::signal() const
{
  bool res = element().signal();
  return m_inv ? !res : res;
}

SignalState Input::state() const
{
  return m_inv ? SignalState::inverted : SignalState::direct;
}

Element::Element(Operation op, SignalState out)
    : m_type{ElementType{int(op)}}, m_out_inv{out == SignalState::inverted}
{
}

Element::Element(SourceState st)
    : m_type{ElementType::source}, m_src_on{st == SourceState::on}
{
}

bool Element::signal() const
{
  bool s = calc();
  return m_out_inv ? !s : s;
}

SignalState Element::state() const
{
  return m_out_inv ? SignalState::inverted : SignalState::direct;
}

bool Element::calc() const
{
  switch (m_type)
  {
  case ElementType::source:
    return m_src_on;

  case ElementType::and_op:
  {
    for (const auto& in : inputs())
    {
      if (!in.signal())
        return false;
    }
    return !inputs().empty();
  }

  case ElementType::or_op:
  {
    for (const auto& in : inputs())
    {
      if (in.signal())
        return true;
    }
    return false;
  }
  }
  throw std::logic_error{"unknown element type"};
}

void Element::set(SourceState st)
{
  if (m_type != ElementType::source)
    throw std::runtime_error{"can't set state for non-source element"};

  m_src_on = (st == SourceState::on);
}

Element& operator>> (Element& lhs, Input rhs)
{
  auto op = rhs.element().m_type;

  if (op == ElementType::source)
    throw std::runtime_error{"inputs for source elements not allowed"};

  check_loop(rhs.element(), lhs);

  rhs.element().m_inputs.push_back(Input{lhs, rhs.state()});
  lhs.m_outputs.push_back(rhs.element());

  return rhs.element();
}

Element& operator>> (Element& lhs, Element& rhs)
{
  return lhs >> Input{rhs, SignalState::direct};
}

}  // namespace logic
