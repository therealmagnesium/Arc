#include "Graphics/Camera.h"
#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Input.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

namespace Arc
{
    namespace Graphics
    {
        glm::vec3 Camera::GetViewDirection()
        {
            return -glm::transpose(view)[2];
        }

        glm::vec3 Camera::GetRightVector()
        {
            return glm::transpose(view)[0];
        }

        void UpdateCamera(Camera& camera)
        {
            const Core::ApplicationConfig& config = Core::GetApplicationInfo();

            if (Core::IsKeyDown(KEY_S))
                camera.position -= camera.moveSpeed * camera.GetViewDirection();

            if (Core::IsKeyDown(KEY_W))
                camera.position += camera.moveSpeed * camera.GetViewDirection();

            if (Core::IsKeyDown(KEY_A))
                camera.position -= camera.moveSpeed * camera.GetRightVector();

            if (Core::IsKeyDown(KEY_D))
                camera.position += camera.moveSpeed * camera.GetRightVector();

            if (Core::IsMouseDown(MOUSE_BUTTON_LEFT))
            {
                glm::vec4 position = glm::vec4(V3_OPEN(camera.position), 1.f);
                glm::vec4 pivot = glm::vec4(V3_OPEN(camera.target), 1.f);

                glm::vec2 deltaAngle;
                deltaAngle.x = 2.f * M_PI / config.windowWidth;
                deltaAngle.y = M_PI / config.windowHeight;

                glm::vec2 angle;
                angle.x = Core::GetMouseRelative().x * deltaAngle.x * camera.lookSensitivity;
                angle.y = Core::GetMouseRelative().y * deltaAngle.y * camera.lookSensitivity;

                float cosAngle = glm::dot(camera.GetViewDirection(), camera.up);
                if (cosAngle * glm::sign(deltaAngle.y) > 0.99f)
                    deltaAngle.y = 0.f;

                glm::mat4 rotationMatrixX = glm::mat4(1.f);
                rotationMatrixX = glm::rotate(rotationMatrixX, angle.x, camera.up);
                position = (rotationMatrixX * (position - pivot)) + pivot;

                glm::mat4 rotationMatrixY = glm::mat4(1.f);
                rotationMatrixY = glm::rotate(rotationMatrixY, angle.y, camera.GetRightVector());
                glm::vec3 finalPosition = (rotationMatrixY * (position - pivot)) + pivot;

                camera.position = finalPosition;
            }

            camera.view = glm::lookAt(camera.position, camera.target, camera.up);
        }
    }
}
