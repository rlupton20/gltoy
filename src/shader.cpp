#include <functional>

#include <shader.hpp>
#include <transform.hpp>

std::optional<GLuint>
make_program(GLuint vshader,
             GLuint fshader,
             std::ostream& errstream = std::cerr);
bool
checkForErrors(GLuint item,
               GLenum type,
               std::function<void(const char* const)> emitter);

std::optional<GLuint>
create_shader(const std::string& text, GLenum type, std::ostream& errstream)
{
  GLuint shader = glCreateShader(type);
  if (shader == 0) {
    errstream << "Shader creation failed" << std::endl;
    return {};
  }

  const GLchar* const shader_source = text.c_str();
  const GLint source_length = text.length();
  glShaderSource(shader, 1, &shader_source, &source_length);
  glCompileShader(shader);

  bool errors = checkForErrors(
    shader, GL_COMPILE_STATUS, [&errstream, &text](const char* const logs) {
      errstream << "ERROR::create_shader::compile" << std::endl
                << logs << std::endl
                << "while compiling:\n"
                << std::endl
                << text << std::endl;
    });

  return errors ? std::nullopt : std::make_optional(shader);
}

std::optional<GLuint>
make_program(GLuint vertshader, GLuint fragshader, std::ostream& errstream)
{
  GLuint program = glCreateProgram();
  glAttachShader(program, vertshader);
  glAttachShader(program, fragshader);

  glBindAttribLocation(program, 0, "position");
  glBindAttribLocation(program, 1, "text_coord");
  glBindAttribLocation(program, 2, "normal");

  glLinkProgram(program);
  const bool link_errors = checkForErrors(
    program, GL_LINK_STATUS, [&errstream](const char* const logs) {
      errstream << "ERROR::make_program::link" << std::endl
                << logs << std::endl
                << std::endl;
    });

  if (link_errors) {
    return {};
  } else {
    errstream << "SHADER::program linked" << std::endl;
  }

  glValidateProgram(program);
  const bool validate_errors = checkForErrors(
    program, GL_VALIDATE_STATUS, [&errstream](const char* const logs) {
      errstream << "ERROR::make_program::validate" << std::endl
                << logs << std::endl
                << std::endl;
    });

  if (validate_errors) {
    return {};
  } else {
    errstream << "SHADER::program validated" << std::endl;
  }

  return program;
}

ShaderPipeline::ShaderPipeline(GLuint program,
                               GLuint vertshader,
                               GLuint fragshader,
                               GLuint transform)
  : program(program)
  , vertex_shader(vertshader)
  , fragment_shader(fragshader)
  , transform(transform)
{}

ShaderPipeline::ShaderPipeline(ShaderPipeline&& rhs)
  : program(rhs.program)
  , vertex_shader(rhs.vertex_shader)
  , fragment_shader(rhs.fragment_shader)
  , transform(rhs.transform)
{
  if (this != &rhs)
    rhs.program = 0;
}

ShaderPipeline::~ShaderPipeline()
{
  if (program) {
    glDetachShader(program, vertex_shader);
    glDeleteShader(vertex_shader);
    glDetachShader(program, fragment_shader);
    glDeleteShader(fragment_shader);
    glDeleteProgram(program);
  }
}

void
ShaderPipeline::bind()
{
  glUseProgram(program);
  // The transform uniform needs to be set - set it to the trivial
  // transform
  set_transform(identity());
}

std::optional<ShaderPipeline>
ShaderPipeline::make_shader(GLuint vertshader, GLuint fragshader)
{
  const auto program = make_program(vertshader, fragshader);
  if (program) {
    const auto transform = glGetUniformLocation(program.value(), "transform");

    if (transform < 0) {
      return {};
    }

    return ShaderPipeline(program.value(), vertshader, fragshader, transform);
  } else {
    return {};
  }
}

void
ShaderPipeline::set_transform(const glm::mat4&& model_matrix) const
{
  glUniformMatrix4fv(transform, 1, GL_FALSE, &model_matrix[0][0]);
}

bool
checkForErrors(GLuint item,
               GLenum type,
               std::function<void(const char* const)> emitter)
{
  static const size_t LOG_LENGTH = 1024;
  int success = GL_TRUE;
  char log[LOG_LENGTH];
  glGetShaderiv(item, type, &success);
  if (success == GL_FALSE) {
    glGetShaderInfoLog(item, LOG_LENGTH, NULL, log);
    emitter(log);
  }
  return success == GL_FALSE;
}
