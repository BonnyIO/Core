#include "../h/Camera.hpp"
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>

namespace Core {

    Camera::Camera(const glm::vec3& position, const glm::vec3& rotation, const ProjectionMode projection_mode)
        : m_position(position), m_rotation(rotation), m_projection_mode(projection_mode) {

        updateView();
        updateProjection();
    }

    void Camera::updateView() {

        float rotateRadians_x = glm::radians(-m_rotation.x);

        glm::mat4 roMat_x(1, 0, 0, 0,
            0, cos(rotateRadians_x), sin(rotateRadians_x), 0,
            0, -sin(rotateRadians_x), cos(rotateRadians_x), 0,
            0, 0, 0, 1);

        float rotateRadians_y = glm::radians(-m_rotation.y);

        glm::mat4 roMat_y(cos(rotateRadians_y), 0, -sin(rotateRadians_y), 0,
            0, 1, 0, 0,
            sin(rotateRadians_y), 0, cos(rotateRadians_y), 0,
            0, 0, 0, 1);

        float rotateRadians_z = glm::radians(-m_rotation.z);

        glm::mat4 roMat_z(cos(rotateRadians_z), sin(rotateRadians_z), 0, 0,
            -sin(rotateRadians_z), cos(rotateRadians_z), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);

        glm::mat4 TransMat(1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            -m_position[0], -m_position[1], -m_position[2], 1);

        m_View = roMat_z * roMat_y * roMat_x * TransMat;
    }

    void Camera::updateProjection() {

        if (m_projection_mode == ProjectionMode::Perspective) {

            float r = 0.1f;
            float t = 0.1f;
            float f = 10;
            float n = 0.1f;

            m_Projection = glm::mat4(n / r, 0, 0, 0,
                0, n / t, 0, 0,
                0, 0, (-f - n) / (f - n), -1,
                0, 0, -2 * f * n / (f - n), 0);
        }

        else {

            float r = 2;
            float t = 2;
            float f = 100;
            float n = 0.1f;

            m_Projection = glm::mat4(1 / r, 0, 0, 0,
                0, 1 / t, 0, 0,
                0, 0, -2 / (f - n), 0,
                0, 0, (-f - n) / (f - n), 1);
        }
    }

    void Camera::set_position(const glm::vec3& position) {

        m_position = position;
        updateView();
    }

    void Camera::set_rotation(const glm::vec3& rotation) {

        m_rotation = rotation;
        updateView();
    }

    void Camera::set_position_rotation(const glm::vec3& position, const glm::vec3& rotation) {

        m_position = position;
        m_rotation = rotation;
        updateView();
    }

    void Camera::set_projection_mode(const ProjectionMode projection_mode) {

        m_projection_mode = projection_mode;
        updateProjection();
    }
}