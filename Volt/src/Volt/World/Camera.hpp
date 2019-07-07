#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Volt::World
{
    class Camera
    {
    public:
        virtual ~Camera();

    protected:
        Camera();

    public:
        //Camera logic
        virtual void Update();

        void SetPosition(glm::vec3 const &pos);
        void Move(glm::vec3 const &move_vec);

        void SetOrientation(glm::vec3 const &angle_vector);
        void Rotate(glm::vec3 const &axis, float radian_angle);
        void Rotate(float angle_x, float angle_y, float angle_z = 0.0f);
        void Rotate(glm::vec3 const &angle_vector);

        inline glm::vec3 &GetPosition() { return m_position; }
        inline glm::vec3 const &GetPosition() const { return m_position; }

        inline glm::mat4 GetOrientation() const { return glm::mat4_cast(glm::normalize(glm::quat(m_rotation))); }
        inline glm::quat GetQuatOrientation() const { return glm::normalize(glm::quat(m_rotation)); }

        glm::vec3 const &GetForward() const { return m_direction; }
        glm::vec3 const &GetRightSide() const { return m_right; }
        glm::mat4 const &GetViewMatrix() const { return m_view; }
        glm::mat4 const &GetProjectionMatrix() const { return m_projection; }
        glm::mat4 const &GetViewProjectionMatrix() const { return m_viewProjection; }

        //Mouse utils
        void SetMouseSensitivity(glm::vec3 const &);
        void SetMouseXSensitivity(float x);
        void SetMouseYSensitivity(float y);
        void SetMouseZSensitivity(float z);

        inline glm::vec3 const &GetMouseSensitivity() const {return m_sensitivity; }

        void FeedMouseInput(float xPos, float yPos);

    protected:
        glm::vec3   m_position, m_rotation, m_direction, m_right;
        glm::vec3   m_sensitivity;
        glm::vec2   m_prevMousePosition;        
        glm::mat4   m_view;
        glm::mat4   m_projection;
        glm::mat4   m_viewProjection;
    };

    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(float fov, float aspect, float near, float far);
        virtual ~PerspectiveCamera() = default;
    };

    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);
        virtual ~OrthographicCamera() = default;
    };
}