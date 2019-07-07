#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Vertex
{
public:
  Vertex(const glm::vec3& pos,
         const glm::vec2& text_coord,
         const glm::vec3& normal = glm::vec3(0, 0, 0))
    : pos(pos)
    , text_coord(text_coord)
    , normal(normal)
  {}

private:
  glm::vec3 pos;
  glm::vec2 text_coord;
  glm::vec3 normal;
};

class SimpleMesh
{
public:
  SimpleMesh(const Vertex* const vertices,
             size_t num_vertices,
             const unsigned int* const indices,
             size_t num_indices);
  virtual ~SimpleMesh();

  void draw();

private:
  SimpleMesh(SimpleMesh&);
  SimpleMesh(SimpleMesh&&);
  void operator=(SimpleMesh&);

  GLuint vertex_array_object;
  GLuint vertex_array_buffer;
  GLuint vertex_element_buffer;
  size_t draw_count;
};
