#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Vertex
{
public:
  Vertex(const glm::vec3& pos, const glm::vec2& text_coord)
    : pos(pos)
    , text_coord(text_coord)
  {}

private:
  glm::vec3 pos;
  glm::vec2 text_coord;
};

class SimpleMesh
{
public:
  SimpleMesh(Vertex* vertices, size_t num_vertices);
  virtual ~SimpleMesh();

  void draw();

private:
  SimpleMesh(SimpleMesh&);
  SimpleMesh(SimpleMesh&&);
  void operator=(SimpleMesh&);

  GLuint vertex_array_object;
  GLuint vertex_array_buffer;
  size_t draw_count;
};
