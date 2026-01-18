#include "shader.h"
#include "camera.h"
#include "window.h"
#include "cube.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

inline constexpr glm::mat4 IDENTITY_MATRIX{1.0f};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};
    glfwSetWindowUserPointer(window, &camera);

    Shader shaderProgram{
        std::filesystem::path{"assets/shaders/shader.vs"},
        std::filesystem::path{"assets/shaders/shader.fs"}};

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    shaderProgram.use();
    glm::mat4 projection{glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f)};
    shaderProgram.setMat4("projection", projection);

    int index{0};
    for (int x{0}; x < 10; ++x)
    {
        for (int z{0}; z < 10; ++z)
        {
            glm::vec3 translation;
            translation.x = x;
            translation.y = 0;
            translation.z = z;

            shaderProgram.setVec3("offsets[" + std::to_string(x * z) + "]", translation);
        }
    }

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.setMat4("model", IDENTITY_MATRIX);
        shaderProgram.setMat4("view", camera.getViewMatrix());

        glBindVertexArray(VAO);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
