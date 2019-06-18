#include <cstdint>
#include <iostream>
#include <unistd.h>

#include <files.hpp>
#include <mesh.hpp>
#include <shader.hpp>
#include <window.hpp>

#include <glm/glm.hpp>

int
main(int argc, char* argv[])
{
  std::cerr << "Starting..." << std::endl;

  std::cerr << "MAIN::Reading shaders" << std::endl;
  std::string vertshader = read_file_to_string("shaders/vertex.glsl");
  std::string fragshader = read_file_to_string("shaders/fragment.glsl");

  Window window = Window();

  // Define a triangle
  Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0)),
                        Vertex(glm::vec3(0, 0.5, 0)),
                        Vertex(glm::vec3(0.5, -0.5, 0)) };

  SimpleMesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

  std::cerr << "MAIN::Compiling shaders" << std::endl;
  GLuint vertex_shader = create_shader(vertshader, GL_VERTEX_SHADER).value();
  GLuint frag_shader = create_shader(fragshader, GL_FRAGMENT_SHADER).value();
  ShaderPipeline pipeline =
    ShaderPipeline::make_shader(vertex_shader, frag_shader).value();

  std::cerr << "MAIN::Binding shaders" << std::endl;
  pipeline.bind();

  // Draw it
  mesh.draw();

  window.swap_buffers();
  sleep(5);

  return 0;
}
