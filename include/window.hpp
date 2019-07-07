#pragma once

#include <SDL2/SDL.h>

class Window
{
public:
  Window(const uint16_t width, const uint16_t height);
  virtual ~Window();

  void swap_buffers();
  void clear(float r = 0.0f,
             float g = 0.0f,
             float b = 0.0f,
             float alpha = 1.0f) const;

private:
  Window(Window&);
  Window(Window&&);
  void operator=(Window&);

  SDL_Window* window;
  SDL_GLContext glContext;
};
