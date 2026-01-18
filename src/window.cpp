#include "camera.h"
#include "window.h"
#include "context.h"

AppContext *getAppContext(GLFWwindow *window)
{
    return static_cast<AppContext *>(glfwGetWindowUserPointer(window));
}

void processInput(GLFWwindow *window)
{
    float currentFrame{static_cast<float>(glfwGetTime())};
    static float lastFrame{currentFrame};

    float deltaTime{currentFrame - lastFrame};
    lastFrame = currentFrame;

    AppContext *context{getAppContext(window)};

    bool pauseKeyPressed{glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS};
    static bool pauseKeyWasPressed{false};

    if (!pauseKeyWasPressed && glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        bool *paused{context->paused};
        *paused = !*paused;

        glfwSetInputMode(
            window,
            GLFW_CURSOR,
            *paused ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    }
    pauseKeyWasPressed = pauseKeyPressed;

    Camera *camera{context->camera};
    if (!camera)
        return;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->processKeyboard(Camera::Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->processKeyboard(Camera::Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->processKeyboard(Camera::Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->processKeyboard(Camera::Movement::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    static bool firstMouse{true};
    static float lastX{SCR_WIDTH / 2.0f};
    static float lastY{SCR_HEIGHT / 2.0f};

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    AppContext *context{getAppContext(window)};
    if (*(context->paused))
    {
        firstMouse = true;
        return;
    }

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    Camera *camera{context->camera};
    if (!camera)
        return;

    camera->processMouseMovement(xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}