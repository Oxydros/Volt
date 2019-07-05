#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Volt::World
{
    class Camera
    {
    public:
        Camera();
        ~Camera();

    public:
        //Camera logic
        void Update();

        void SetPosition(glm::vec3 const &pos);
        void Move(glm::vec3 const &move_vec);

        void SetOrientation(glm::vec3 const &angle_vector);
        void Rotate(glm::vec3 const &axis, float radian_angle);
        void Rotate(float angle_x, float angle_y, float angle_z = 0);
        void Rotate(glm::vec3 const &angle_vector);

        inline glm::vec3 &GetPosition() { return m_position; }
        inline glm::vec3 const &GetPosition() const { return m_position; }

        inline glm::mat4 GetOrientation() const { return glm::mat4_cast(glm::normalize(glm::quat(m_rotation))); }
        inline glm::quat GetQuatOrientation() const { return glm::normalize(glm::quat(m_rotation)); }

        glm::vec3 const &GetForward() const;
        glm::vec3 const &GetRightSide() const;
        glm::mat4 const &GetViewMatrix() const;

        //Mouse utils
        void SetMouseSensitivity(glm::vec3 const &);
        void SetMouseXSensitivity(float x);
        void SetMouseYSensitivity(float y);
        void SetMouseZSensitivity(float z);

        inline glm::vec3 const &GetMouseSensitivity() const {return m_sensitivity; }

        void FeedMouseInput(float xPos, float yPos);

    private:
        glm::vec3   m_position, m_rotation, m_direction, m_right;
        glm::vec3   m_sensitivity;
        glm::mat4   m_view;
        glm::vec2   m_prevMousePosition;
    };
}