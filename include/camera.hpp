#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace Camera {

inline glm::mat4
make_view_matrix(const glm::vec3&& position,
                 const glm::vec3&& forward,
                 const glm::vec3&& up)
{
  return glm::lookAt(position, position + forward, up);
}

inline glm::mat4
make_perspective_matrix(const float fov,
                        const float aspect,
                        const float z_near,
                        const float z_far)
{
  return glm::perspective(fov, aspect, z_near, z_far);
}

inline float
aspect_ratio(const uint16_t width, const uint16_t height)
{
  return (float)width / (float)height;
}

}
