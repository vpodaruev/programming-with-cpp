#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

int main ()
try
{
  const std::string src = "dir.txt";
  const std::string dst = "rev.txt";
  constexpr int chunk = 128;

  std::array<char, chunk> buffer;

  std::ifstream ifs{src};
  if (!ifs)
    throw std::runtime_error{"can't read file " + src};

  std::ofstream ofs{dst};
  if (!ofs)
    throw std::runtime_error{"can't write file " + dst};

  ifs.seekg(0, std::ios::end);
  int pos = ifs.tellg();

  while (pos > 0)
  {
    int count = (pos > chunk) ? chunk : pos;

    pos -= count;

    ifs.seekg(pos);
    ifs.read(buffer.data(), count);

    std::reverse(buffer.begin(), buffer.begin() + count);

    ofs.write(buffer.data(), count);
  }
}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
