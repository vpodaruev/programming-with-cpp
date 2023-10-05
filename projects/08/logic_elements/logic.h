#ifndef LOGIC_H
#define LOGIC_H 1

#include <stdexcept>
#include <vector>

namespace logic {

enum class ElementType
{
  source = 0,
  and_op,
  or_op
};

enum class SignalState
{
  direct = 0,
  inverted
};

enum class SourceState
{
  off = 0,
  on
};

enum class Operation
{
  and_op = int(ElementType::and_op),
  or_op = int(ElementType::or_op)
};

class Element;

class Input
{
public:
  Input(Element& elem, SignalState st);

  Element& element () { return m_elem; }

  const Element& element () const { return m_elem; }

  bool signal () const;
  SignalState state () const;

private:
  const std::reference_wrapper<Element> m_elem;
  const bool m_inv;
};

using InputContainer = std::vector<Input>;
using OutputContainer = std::vector<std::reference_wrapper<Element>>;

class Element
{
public:
  explicit Element(Operation op, SignalState out = SignalState::direct);
  explicit Element(SourceState st);

  const InputContainer& inputs () const { return m_inputs; }

  const OutputContainer& outputs () const { return m_outputs; }

  bool signal () const;
  SignalState state () const;

  void set (SourceState st);

  Input operator~() { return {*this, SignalState::inverted}; }

  friend Element& operator>> (Element& lhs, Input rhs);

private:
  InputContainer m_inputs;
  OutputContainer m_outputs;
  ElementType m_type{ElementType::source};
  bool m_src_on{false};
  bool m_out_inv{false};

  bool calc () const;
};

Element& operator>> (Element& lhs, Element& rhs);

}  // namespace logic

#endif  // #ifndef LOGIC_H
