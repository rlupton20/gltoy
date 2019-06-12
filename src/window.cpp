#include <window.hpp>
#include <iostream>

#include <GL/glew.h>


static const uint16_t HEIGHT = 600;
static const uint16_t WIDTH = 600;


// TODO Refactor
Window::Window()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    throw "Failed to initialize SDL.";
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
    SDL_Quit();
    throw "Window could not be created";
  }

  // Give window to GPU to control - TODO does this need error checking?
  glContext = SDL_GL_CreateContext(window);

  GLenum status = glewInit();

  if (status != GLEW_OK) {
    std::cerr << "GLEW failed to initialize" << std::endl;
  }

  glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
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
