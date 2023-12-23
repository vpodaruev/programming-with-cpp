#ifndef UTILS_H
#define UTILS_H 1

#include <iostream>

/** Debug output of variable with code location
 */
#define DEBUG_OUT(x)                                                       \
  std::cerr << #x << " = " << x << " [" << __FILE__ << ": " << __LINE__    \
            << "]" << std::endl;

#endif  // #ifndef UTILS_H
