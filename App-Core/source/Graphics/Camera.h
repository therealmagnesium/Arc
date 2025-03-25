#pragma once
#include <glm/glm.hpp>

namespace Arc
{
    namespace Graphics
    {
        struct Camera
        {
            glm::vec3 position;
            glm::vec3 target;
            glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
            glm::mat4 view = glm::mat4(1.f);
        };

        void UpdateCamera(Camera& camera);
    }
}
