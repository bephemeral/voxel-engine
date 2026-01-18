#include "shader.h"
#include "camera.h"
#include "window.h"
#include "chunk.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "context.h"

inline constexpr glm::mat4 IDENTITY_MATRIX{1.0f};

inline constexpr unsigned int CHUNKS_ROOT{32};

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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Camera camera{};
    bool paused{false};
    AppContext appContext{&camera, &paused};
    glfwSetWindowUserPointer(window, &appContext);

    Shader shaderProgram{
        std::filesystem::path{"assets/shaders/shader.vs"},
        std::filesystem::path{"assets/shaders/shader.fs"}};

    std::vector<Chunk> chunks;
    for (int x = 0; x < CHUNKS_ROOT; ++x)
    {
        for (int z = 0; z < CHUNKS_ROOT; ++z)
        {
            chunks.emplace_back(glm::vec3(x * Chunk::CHUNK_SIZE, 0, z * Chunk::CHUNK_SIZE));
        }
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    shaderProgram.use();
    glm::mat4 projection{glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f)};
    shaderProgram.setMat4("projection", projection);

    bool wireframeMode{false};

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (*(appContext.paused))
        {
            ImGui::Begin("Settings");
            ImGui::SliderFloat("Camera Speed", &camera.movementSpeed, 0.1f, 20.0f);
            ImGui::SliderFloat("Mouse Sensitivity", &camera.mouseSensitivity, 0.01f, 1.0f);
            if (ImGui::Checkbox("Wireframe Mode", &wireframeMode))
            {
                if (wireframeMode)
                {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                }
                else
                {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
            }
            ImGui::End();
        }

        shaderProgram.setMat4("view", camera.getViewMatrix());

        for (const auto &chunk : chunks)
        {
            shaderProgram.setMat4("model", glm::translate(IDENTITY_MATRIX, chunk.position));
            chunk.renderMesh();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
