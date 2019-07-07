#include <mesh.hpp>

SimpleMesh::SimpleMesh(const Vertex* const vertices,
                       size_t num_vertices,
                       const unsigned int* const indices,
                       size_t num_indices)
  : draw_count(num_indices)
{
  static const size_t VERTEX_LENGTH = 8;
  static const size_t TEXTURE_OFFSET = 3;
  static const size_t NORMAL_OFFSET = 5;

  // Generate one vertex array, and store its name in vertex_array_object
  glGenVertexArrays(1, &vertex_array_object);

  // Work on the vertex array vertex_array_object
  glBindVertexArray(vertex_array_object);

  glGenBuffers(1, &vertex_array_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_array_buffer);

  // Setup vertex position data
  glBufferData(GL_ARRAY_BUFFER,
               num_vertices * sizeof(vertices[0]),
               vertices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
    0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_LENGTH, 0);

  // Setup vertex texture data
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(GLfloat) * VERTEX_LENGTH,
                        (GLvoid*)(sizeof(GLfloat) * TEXTURE_OFFSET));

  // Setup vertex normal data
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(GLfloat) * VERTEX_LENGTH,
                        (GLvoid*)(sizeof(GLfloat) * NORMAL_OFFSET));

  // Generate a buffer for vertex elements
  glGenBuffers(1, &vertex_element_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_element_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               num_indices * sizeof(indices[0]),
               &indices[0],
               GL_STATIC_DRAW);

  // Stop working on vertex_array_object
  glBindVertexArray(0);
}

SimpleMesh::~SimpleMesh()
{
  // Cleanup the vertex arrays
  glDeleteVertexArrays(1, &vertex_array_object);
}

void
SimpleMesh::draw()
{
  glBindVertexArray(vertex_array_object);
  glDrawElements(GL_TRIANGLES, draw_count, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
