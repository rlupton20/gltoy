#pragma once

#include <GL/glew.h>

class Texture
{
public:
  Texture(const char* const filename);
  virtual ~Texture();

  void bind(uint32_t unit);

private:
  Texture(Texture&);
  Texture(Texture&&);
  void operator=(Texture&);

  GLuint texture;
};
