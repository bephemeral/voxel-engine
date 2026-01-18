#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    enum class Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 20.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH);

    // constructor with scalar values
    Camera(float posX, float posY, float posZ,
           float upX, float upY, float upZ,
           float yaw, float pitch);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 getViewMatrix();

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void processKeyboard(Movement direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

private:
    static inline constexpr float YAW = -90.0f;
    static inline constexpr float PITCH = 0.0f;
    static inline constexpr float SPEED = 5.0f;
    static inline constexpr float SENSITIVITY = 0.2f;
    static inline constexpr float ZOOM = 45.0f;

    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};