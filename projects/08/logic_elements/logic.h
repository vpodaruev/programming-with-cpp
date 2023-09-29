#pragma once

#include <stdexcept>
#include <vector>

namespace logic {

enum class ElementType
{
  SIGNAL_OFF,
  SIGNAL_ON,
  ADD,
  OR
};
enum class InputState
{
  DIRECT = 0,
  INVERTED = 1
};

class Element;

class Input
{
public:
  Input(Element& element, InputState state)
      : m_element(element), m_inverted(state == InputState::INVERTED)
  {
  }

  InputState GetState () const
  {
    return m_inverted ? InputState::INVERTED : InputState::DIRECT;
  }

  Element& GetElement () const { return m_element; }

  bool IsSignal () const;

  Input operator~()
  {
    InputState changed_state =
        m_inverted ? InputState::DIRECT : InputState::INVERTED;
    return {m_element, changed_state};
  }

private:
  const std::reference_wrapper<Element> m_element;
  const bool m_inverted;
};

using InputContainer = std::vector<Input>;
using OutputContainer = std::vector<std::reference_wrapper<Element>>;

class Element
{
public:
  explicit Element(ElementType type) : m_type(type) {}

  const InputContainer& GetInputs () const { return m_inputs; }

  const OutputContainer& GetOutputs () const { return m_outputs; }

  bool IsSignal () const;

  Input operator~() { return {*this, InputState::INVERTED}; }

private:
  ElementType m_type;

  InputContainer m_inputs;
  OutputContainer m_outputs;

  friend Element& operator>> (Element& lhs, Input rhs);
  friend Element& operator>> (Element& lhs, Element& rhs);
};

Element& operator>> (Element& lhs, Input rhs);
Element& operator>> (Element& lhs, Element& rhs);

}  // namespace logic