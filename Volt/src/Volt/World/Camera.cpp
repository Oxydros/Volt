#include "vpch.h"

#include "Volt/World/Camera.hpp"

namespace Volt::World
{
    Camera::Camera()
    {
        m_position = glm::vec3(0.0f, 0.0f, 5.0f);
        m_rotation = glm::vec3(0);
        m_sensitivity = glm::vec3(0.002f, 0.002f, 0.0f);
        m_prevMousePosition = glm::vec3(0);
        Update();
    }

    Camera::~Camera()
    {

    }

    void Camera::Update()
    {
        auto quat = glm::normalize(glm::quat(m_rotation));
        glm::mat4 rotation = glm::mat4_cast(quat);
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), -m_position);
        m_view = rotation * translation;

        m_right = glm::vec3(m_view[0][0], m_view[1][0], m_view[2][0]);
        m_direction = -glm::vec3(m_view[0][2], m_view[1][2], m_view[2][2]);
    }

    void Camera::SetPosition(glm::vec3 const &pos)
    {
        m_position = pos;
    }

    void Camera::Move(glm::vec3 const &move_vec)
    {
        m_position += move_vec;
    }

    void Camera::SetOrientation(glm::vec3 const &angle_vector)
    {
        m_rotation = angle_vector;
    }

    void Camera::Rotate(glm::vec3 const &axis, float radian_angle)
    {
        m_rotation += (axis * radian_angle);
    }

    void Camera::Rotate(float angle_x, float angle_y, float angle_z)
    {
        m_rotation += glm::vec3(angle_x, angle_y, angle_z);
    }
    void Camera::Rotate(glm::vec3 const &angle_vector)
    {
        m_rotation += angle_vector;
    }

    glm::vec3 const &Camera::GetForward() const
    {
        return m_direction;
    }

    glm::vec3 const &Camera::GetRightSide() const
    {
        return m_right;
    }

    glm::mat4 const &Camera::GetViewMatrix() const
    {
        return m_view;
    }


    void Camera::SetMouseSensitivity(glm::vec3 const &new_sens)
    {
        m_sensitivity = new_sens;
    }

    void Camera::SetMouseXSensitivity(float x)
    {
        m_sensitivity.x = x;
    }

    void Camera::SetMouseYSensitivity(float y)
    {
        m_sensitivity.y = y;
    }

    void Camera::SetMouseZSensitivity(float z)
    {
        m_sensitivity.z = z;
    }

    void Camera::FeedMouseInput(float xPos, float yPos)
    {
        static bool firstCam = true;
        glm::vec2 currentPos = glm::vec2(xPos, yPos);

        if (firstCam)
        {
            m_prevMousePosition = currentPos;
            firstCam = false;
            return;
        }
        glm::vec2 mouse_delta = currentPos - m_prevMousePosition;
        
        float yaw = GetMouseSensitivity().x * mouse_delta.x;
        float pitch = GetMouseSensitivity().y * mouse_delta.y;

        if (pitch >= 89.0f)
            pitch = 89.0f;
        else if (pitch <= -89.0f)
            pitch = -89.0f;

        Rotate(pitch, yaw);
        m_prevMousePosition = currentPos;
    }
}