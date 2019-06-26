#pragma once

#include <GL/glew.h>

class StbImage;

class Texture
{
public:
  Texture(Texture&&);
  virtual ~Texture();

  static std::optional<Texture> from_file(const char* const filename);

  void bind(uint32_t unit);

private:
  Texture(StbImage&& image);
  Texture(Texture&);
  void operator=(Texture&);

  GLuint texture;
};
