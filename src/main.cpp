#include <iostream>
#include <cstdint>

#include <SDL2/SDL.h>

#include <window.hpp>

int main(int argc, char *argv[])
{
  std::cerr << "Starting..." << std::endl;

  Window window = Window();
  window.swap_buffers();

  return 0;
}
