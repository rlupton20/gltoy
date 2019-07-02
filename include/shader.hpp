#pragma once

#include <iostream>
#include <optional>
#include <string>

#include <GL/glew.h>
#include <glm/gtx/transform.hpp>

std::optional<GLuint>
create_shader(const std::string& text,
              GLenum type,
              std::ostream& errstream = std::cerr);

class ShaderPipeline
{
public:
  ShaderPipeline(ShaderPipeline&& rhs);
  virtual ~ShaderPipeline();

  static std::optional<ShaderPipeline> make_shader(GLuint vertshader,
                                                   GLuint fragshader);

  void bind();

  void set_transform(const glm::mat4&& model) const;

private:
  ShaderPipeline(GLuint program,
                 GLuint vertshader,
                 GLuint fragshader,
                 GLuint transform);
  // Hide the various copy operators
  void operator=(ShaderPipeline& rhs);
  ShaderPipeline(ShaderPipeline& rhs);

  GLuint program;
  GLuint vertex_shader;
  GLuint fragment_shader;
  GLuint transform;
};
