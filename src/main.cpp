#include <cstdint>
#include <iostream>
#include <unistd.h>

#include <files.hpp>
#include <mesh.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <transform.hpp>
#include <window.hpp>

#include <glm/glm.hpp>

int
main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cerr << "Expected a texture filename as input" << std::endl;
    return 1;
  }

  const char* const texture_file = argv[1];

  std::cerr << "Starting..." << std::endl;

  std::cerr << "MAIN::Reading shaders" << std::endl;
  std::string vertshader = read_file_to_string("shaders/vertex.glsl");
  std::string fragshader = read_file_to_string("shaders/fragment.glsl");

  Window window = Window();

  // Define a triangle
  Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
                        Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
                        Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

  SimpleMesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

  std::cerr << "MAIN::Compiling shaders" << std::endl;
  GLuint vertex_shader = create_shader(vertshader, GL_VERTEX_SHADER).value();
  GLuint frag_shader = create_shader(fragshader, GL_FRAGMENT_SHADER).value();
  ShaderPipeline pipeline =
    ShaderPipeline::make_shader(vertex_shader, frag_shader).value();

  auto texture = Texture::from_file(texture_file).value();

  std::cerr << "MAIN::Binding shaders" << std::endl;
  pipeline.bind();
  texture.bind(0);

  for (float angle = 0.0; angle < 20; angle += 0.1) {
    // Draw it
    window.clear(0.0f, 0.15f, 0.3f, 1.0f);
    mesh.draw();
    pipeline.set_transform(rotate(std::move(angle)));
    window.swap_buffers();
  }

  return 0;
}
