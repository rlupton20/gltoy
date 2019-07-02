#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

inline glm::mat4
position(const glm::vec3&& pos)
{
  return glm::translate(pos);
}

inline glm::mat4
identity()
{
  return position(glm::vec3(0, 0, 0));
}

inline glm::mat4
rotate(const float&& angle)
{
  return glm::rotate(angle, glm::vec3(0, 1, 0));
}
