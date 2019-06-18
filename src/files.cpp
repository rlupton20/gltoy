#include <fstream>
#include <sstream>

#include <files.hpp>

std::string
read_file_to_string(const char* const filename)
{
  std::ifstream fstr(filename);
  std::stringstream buffer;
  buffer << fstr.rdbuf();
  return buffer.str();
}
