#include <mesh.hpp>

SimpleMesh::SimpleMesh(Vertex* vertices, size_t num_vertices)
  : draw_count(num_vertices)
{
  // Generate one vertex array, and store its name in vertex_array_object
  glGenVertexArrays(1, &vertex_array_object);

  // Work on the vertex array vertex_array_object
  glBindVertexArray(vertex_array_object);

  glGenBuffers(1, &vertex_array_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_array_buffer);
  glBufferData(GL_ARRAY_BUFFER,
               num_vertices * sizeof(vertices[0]),
               vertices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(GLfloat) * 5,
                        (GLvoid*)(sizeof(GLfloat) * 3));

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
  glDrawArrays(GL_TRIANGLES, 0, draw_count);
  glBindVertexArray(0);
}
