#include "variable.h"

vector<Variable> var_table;

double get_value (const string& s)
{
  for (const auto& var : var_table)
  {
    if (var.name == s)
      return var.value;
  }

  error("get: undefined name ", s);
}

void set_value (const string& s, double d)
{
  for (auto& var : var_table)
  {
    if (var.name == s)
    {
      var.value = d;
      return;
    }
  }

  error("set: undefined name ", s);
}

bool is_declared (const string& s)
{
  for (const auto& var : var_table)
  {
    if (var.name == s)
      return true;
  }

  return false;
}

double define_name (const string& var, double val)
{
  if (is_declared(var))
    error(var, " declared twice");

  var_table.push_back(Variable{var, val});

  return val;
}