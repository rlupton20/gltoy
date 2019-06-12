#pragma once

#include <string>
#include <iostream>
#include <optional>

#include <GL/glew.h>

std::optional<GLuint> create_shader(const std::string& text,
                                    GLenum type,
                                    std::ostream &errstream = std::cerr);


class ShaderPipeline {
public:
  ShaderPipeline(ShaderPipeline &&rhs);
  virtual ~ShaderPipeline();

  static std::optional<ShaderPipeline> make_shader(GLuint vertshader, GLuint fragshader);

  void bind();

private:
  ShaderPipeline(GLuint program, GLuint vertshader, GLuint fragshader);
  // Hide the various copy operators
  void operator=(ShaderPipeline &rhs);
  ShaderPipeline(ShaderPipeline &rhs);

  GLuint program;
  GLuint vertex_shader;
  GLuint fragment_shader;
};
