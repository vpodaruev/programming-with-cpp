#include "logic.h"

#include <stdexcept>

namespace logic {

void CheckLoop (const Element& loop, const Element& elem)
{
  if (&loop == &elem)
    throw std::runtime_error{
        "loop detected in connections of logic elements"};

  for (const auto& output : loop.GetOutputs())
    CheckLoop(output, elem);
}

Element& operator>> (Element& lhs, Input rhs)
{
  auto rhs_operation = rhs.GetElement().m_type;

  if (rhs_operation == ElementType::SIGNAL_OFF ||
      rhs_operation == ElementType::SIGNAL_ON)
  {
    throw std::runtime_error(
        "inputs for SIGNAL_ON/OFF elements are not allowed");
  }

  CheckLoop(rhs.GetElement(), lhs);

  rhs.GetElement().m_inputs.push_back(Input(lhs, rhs.GetState()));
  lhs.m_outputs.push_back(rhs.GetElement());

  return rhs.GetElement();
}

Element& operator>> (Element& lhs, Element& rhs)
{
  return lhs >> Input{rhs, InputState::DIRECT};
}

bool Input::IsSignal() const
{
  bool res = GetElement().IsSignal();
  if (m_inverted)
    res = !res;
  return res;
}

bool Element::IsSignal() const
{
  switch (m_type)
  {
  case ElementType::SIGNAL_OFF:
    return false;
  case ElementType::SIGNAL_ON:
    return true;
  case ElementType::ADD:
  {
    bool signal = !(GetInputs().empty());
    for (const auto& input : GetInputs())
    {
      if (!input.IsSignal())
      {
        signal = false;
        break;
      }
    }
    return signal;
  }
  case ElementType::OR:
  {
    for (const auto& input : GetInputs())
      if (input.IsSignal())
        return true;
    return false;
  }
  default:
    throw std::logic_error("unsupported element type!");
  }
}

}  // namespace logic