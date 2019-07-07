#include <cstdint>
#include <iostream>
#include <unistd.h>

#include <camera.hpp>
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
  const uint16_t width = 800;
  const uint16_t height = 600;

  if (argc < 2) {
    std::cerr << "Expected a texture filename as input" << std::endl;
    return 1;
  }

  const char* const texture_file = argv[1];

  std::cerr << "Starting..." << std::endl;

  std::cerr << "MAIN::Reading shaders" << std::endl;
  std::string vertshader = read_file_to_string("shaders/vertex.glsl");
  std::string fragshader = read_file_to_string("shaders/fragment.glsl");

  Window window = Window(width, height);

  // Define a simple tetrahedron
  /* clang-format off */
  Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec2(0.0, 0.0)),
                        Vertex(glm::vec3(-0.5, 0.5, -0.5), glm::vec2(0.0, 1.0)),
                        Vertex(glm::vec3(0.5, -0.5, -0.5), glm::vec2(1.0, 0.0)),
                        Vertex(glm::vec3(0.5, 0.5, -0.5), glm::vec2(1.0, 1.0)),
                        Vertex(glm::vec3(0.0, 0.0, 0.0), glm::vec2(0.5, 0.5)) };

  unsigned int indices[] = { 0, 1, 2, 1, 2, 3,
                             0, 1, 4,
                             0, 2, 4,
                             1, 3, 4,
                             2, 3, 4
  };
  /* clang-format on */

  SimpleMesh mesh(vertices,
                  sizeof(vertices) / sizeof(vertices[0]),
                  indices,
                  sizeof(indices) / sizeof(indices[0]));

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

    const auto perspective = Camera::make_perspective_matrix(
      70.0f, Camera::aspect_ratio(width, height), 0.01f, 500.0f);
    const auto view = Camera::make_view_matrix(
      glm::vec3(0, 0, -2), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
    const auto matrix = perspective * view * rotate(std::move(angle));

    pipeline.set_transform(std::move(matrix));
    mesh.draw();
    window.swap_buffers();
  }

  return 0;
}
