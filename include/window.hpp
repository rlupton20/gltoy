#pragma once

#include <SDL2/SDL.h>

class Window
{
public:
  Window();
  virtual ~Window();

  void swap_buffers();

private:
  Window(Window&);
  Window(Window&&);
  void operator=(Window&);

  SDL_Window* window;
  SDL_GLContext glContext;
};
