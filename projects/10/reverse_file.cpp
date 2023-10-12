// Reverse the order of symbols in a file(s) given as program
// command line argument(s) using small chunks of data
//
//        | lpos                            | rpos
//        v_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _v
//        |_|_|_|_|_|_|_|_ _ _|_|_|_|_|_|_|_|
//         '--- n ---'           '--- n ---'

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

void reverse_file (const std::string& name)
{
  constexpr int chunk = 128;
  std::array<char, chunk> lbuf, rbuf;

  std::fstream lfs{name}, rfs{name};
  if (!lfs || !rfs)
    throw std::runtime_error{"can't open file '" + name + "'"};

  rfs.seekg(0, std::ios_base::end);  // go to the most right
                                     //   position in a file
  std::streampos lpos = lfs.tellg(), rpos = rfs.tellg();

  while (rpos - lpos > 1)
  {
    lpos = lfs.tellg();  // update l-position

    int n = (rpos - lpos) / 2;  // amount of bytes to swap
    if (n > chunk)
      n = chunk;  // cut it to chunk

    rpos -= n;        // update r-position because of
    rfs.seekg(rpos);  //   forward read/write direction

    lfs.read(lbuf.data(), n);
    rfs.read(rbuf.data(), n);

    std::reverse(lbuf.begin(), lbuf.begin() + n);
    std::reverse(rbuf.begin(), rbuf.begin() + n);

    // restore positions to write
    lfs.seekp(lpos);
    rfs.seekp(rpos);

    // swap buffers when write to get proper reverse order
    lfs.write(rbuf.data(), n);
    rfs.write(lbuf.data(), n);
  }
}

int main (int argc, char* argv[])
try
{
  if (argc < 2)
  {
    std::cerr << "usage: " << argv[0] << " file1 [file2 ...]" << std::endl;
    return 2;
  }

  for (int i = 1; i < argc; ++i)
    reverse_file(argv[i]);
}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
