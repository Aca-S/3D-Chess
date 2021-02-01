#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../classes/Shader.h"
#include "../classes/Texture2D.h"
#include "../classes/Camera.h"

void framebuffer_size_cb(GLFWwindow *window, int width, int height);
void key_cb(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void update(GLFWwindow *window);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
    glfwInit();

    // OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Vezba", nullptr, nullptr);
    if(window == nullptr)
    {
        std::cerr << "Window creation failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_cb);
    glfwSetKeyCallback(window, key_cb);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Window creation failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    float boardVertices[] = {
            // Coords           Texture     Normals
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0, 0.0, 1.0, // bottom-left
            0.5f, -0.5f, 0.0f,  4.0f, 0.0f, 0.0, 0.0, 1.0, // bottom-right
            -0.5f, 0.5f, 0.0f,  0.0f, 4.0f, 0.0, 0.0, 1.0, // top-left
            0.5f, 0.5f, 0.0f,   4.0f, 4.0f, 0.0, 0.0, 1.0  // top-right
    };

    unsigned boardIndices[] = {
            0, 1, 2,
            1, 2, 3
    };

    float cubeVertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    unsigned int boardVBO, boardVAO, boardEBO;

    glGenVertexArrays(1, &boardVAO);
    glBindVertexArray(boardVAO);

    glGenBuffers(1, &boardVBO);
    glGenBuffers(1, &boardEBO);

    glBindBuffer(GL_ARRAY_BUFFER, boardVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boardVertices), boardVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boardEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boardIndices), boardIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int cubeVBO, cubeVAO;

    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    glGenBuffers(1, &cubeVBO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader boardShader("../resources/shaders/board_vertex_shader.vs", "../resources/shaders/board_fragment_shader.fs");
    Shader lightcubeShader("../resources/shaders/lightcube_vertex_shader.vs", "../resources/shaders/lightcube_fragment_shader.fs");

    Texture2D checkerDifTex("../resources/textures/chess_board_diffuse.jpg", GL_REPEAT, GL_LINEAR);
    Texture2D checkerSpecTex("../resources/textures/chess_board_specular.jpg", GL_REPEAT, GL_LINEAR);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        glClearColor(0.2, 0.2, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0);
        glm::mat4 view = glm::mat4(1.0);
        glm::mat4 projection = glm::mat4(1.0);

        view = glm::lookAt(camera.Position, camera.Position + camera.Front, camera.Up);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);

        boardShader.use();
        model = glm::mat4(1.0);
        boardShader.setUniformMatrix4fv("model", model);
        boardShader.setUniformMatrix4fv("view", view);
        boardShader.setUniformMatrix4fv("projection", projection);
        checkerDifTex.active(GL_TEXTURE0);
        boardShader.setUniform1i("material.diffuse", 0);
        checkerSpecTex.active(GL_TEXTURE1);
        boardShader.setUniform1i("material.specular", 1);
        boardShader.setUniform3f("light.ambient", 0.2f, 0.2f, 0.2f);
        boardShader.setUniform3f("light.diffuse", 0.5f, 0.5f, 0.5f);
        boardShader.setUniform3f("light.specular", 1.0f, 1.0f, 1.0f);
        boardShader.setUniform3f("light.position", 0.5f, 0.0f, 3.0f);
        boardShader.setUniform3f("viewPosition", camera.Position.x, camera.Position.y, camera.Position.z);
        glBindVertexArray(boardVAO);
        glDrawElements(GL_TRIANGLES, sizeof(boardIndices) / sizeof(unsigned), GL_UNSIGNED_INT, 0);

        lightcubeShader.use();
        model = glm::translate(model, glm::vec3(0.5f, 0.0f, 3.0f)); // m * T
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); // m * T * R
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // m * T * R * S
        lightcubeShader.setUniformMatrix4fv("model", model);
        lightcubeShader.setUniformMatrix4fv("view", view);
        lightcubeShader.setUniformMatrix4fv("projection", projection);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &boardVAO);
    glDeleteBuffers(1, &boardVBO);
    glDeleteBuffers(1, &boardEBO);

    checkerDifTex.del();
    checkerSpecTex.del();

    boardShader.del();
    lightcubeShader.del();

    glfwTerminate();

    return 0;
}

void framebuffer_size_cb(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void key_cb(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_G && action == GLFW_PRESS)
        std::cout << "G" << std::endl;
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(key == GLFW_KEY_R && action == GLFW_PRESS)
        glClearColor(1.0, 0.0, 0.0, 1.0);
    if(key == GLFW_KEY_G && action == GLFW_PRESS)
        glClearColor(0.0, 1.0, 0.0, 1.0);
    if(key == GLFW_KEY_B && action == GLFW_PRESS)
        glClearColor(0.0, 0.0, 1.0, 1.0);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
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

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void update(GLFWwindow *window) {

}