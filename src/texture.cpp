#include <cstdint>
#include <optional>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

#include <texture.hpp>

class StbImage
{
public:
  StbImage(StbImage&& rhs)
    : image_data(rhs.image_data)
    , _width(rhs._width)
    , _height(rhs._height)
  {
    if (this != &rhs) {
      rhs.image_data = nullptr;
    }
  }

  virtual ~StbImage()
  {
    if (image_data != nullptr) {
      stbi_image_free(image_data);
    }
  }

  static std::optional<StbImage> from_file(const char* const filename)
  {
    int32_t width = 0, height = 0, components = 0;
    uint8_t* image_data = stbi_load(filename, &width, &height, &components, 4);

    if (image_data != nullptr) {
      return StbImage(image_data, width, height);
    } else {
      return {};
    }
  }

  inline const uint8_t* bytes() const { return image_data; }
  inline int32_t height() const { return _height; }
  inline int32_t width() const { return _width; }

private:
  StbImage(uint8_t* image_data, int32_t width, int32_t height)
    : image_data(image_data)
    , _width(width)
    , _height(height)
  {}
  StbImage(StbImage&);
  void operator=(StbImage&);

  uint8_t* image_data;
  int32_t _width, _height;
};

std::optional<Texture>
Texture::from_file(const char* const filename)
{
  auto image = StbImage::from_file(filename);

  if (!image) {
    return {};
  } else {
    return Texture(std::move(image.value()));
  }
}

Texture::Texture(StbImage&& image)
  : texture(0)
{
  glGenTextures(1, &texture);
  assert(texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // How should we wrap the texture?
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               image.width(),
               image.height(),
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               image.bytes());
}

Texture::Texture(Texture&& rhs)
  : texture(rhs.texture)
{
  if (this != &rhs) {
    rhs.texture = 0;
  }
}

Texture::~Texture()
{
  if (texture) {
    glDeleteTextures(1, &texture);
  }
}

void
Texture::bind(uint32_t unit)
{
  assert(0 <= unit && unit < 32);
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, texture);
}
