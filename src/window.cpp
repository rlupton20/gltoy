#include <window.hpp>
#include <iostream>


static const uint16_t HEIGHT = 600;
static const uint16_t WIDTH = 600;


Window::Window()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "Init error" << std::endl;
  }

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  window = SDL_CreateWindow("opengl", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

  if (!window) {
    std::cerr << "Window could not be created" << std::endl;
  }

  // Give window to GPU to control - TODO does this need error checking?
  glContext = SDL_GL_CreateContext(window);
}

Window::~Window()
{
  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Window::swap_buffers()
{
  SDL_GL_SwapWindow(window);
}
