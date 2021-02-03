#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../classes/Shader.h"
#include "../classes/Texture2D.h"
#include "../classes/Camera.h"
#include "../classes/Model.h"
#include "../classes/ChessFigure.h"
#include "../classes/DirectionalLight.h"
#include "../classes/PointLight.h"
#include "../classes/SpotLight.h"
#include "../classes/Material.h"

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
            // Coords           Normals        Texture
            -0.5f, -0.5f, 0.0f, 0.0, 0.0, 1.0, 0.0f, 0.0f, // bottom-left
            0.5f, -0.5f, 0.0f,  0.0, 0.0, 1.0, 4.0f, 0.0f, // bottom-right
            -0.5f, 0.5f, 0.0f,  0.0, 0.0, 1.0, 0.0f, 4.0f, // top-left
            0.5f, 0.5f, 0.0f,   0.0, 0.0, 1.0, 4.0f, 4.0f  // top-right
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
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));

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
    Shader modelShader("../resources/shaders/chess_piece_vertex_shader.vs", "../resources/shaders/chess_piece_fragment_shader.fs");

    Texture2D checkerDifTex("../resources/textures/chess_board_diffuse.jpg", DIFFUSE, GL_REPEAT, GL_LINEAR);
    Texture2D checkerSpecTex("../resources/textures/chess_board_specular.jpg", SPECULAR, GL_REPEAT, GL_LINEAR);

    Material boardMaterial(&checkerDifTex, &checkerSpecTex, 32.0f);

    // TODO: Apply textures to models
    Model pawn("../resources/models/chess/pawn/pawn.obj");
    Model rook("../resources/models/chess/rook/rook.obj");
    Model knight("../resources/models/chess/knight/knight.obj");
    Model bishop("../resources/models/chess/bishop/bishop.obj");
    Model queen("../resources/models/chess/queen/queen.obj");
    Model king("../resources/models/chess/king/king.obj");

    // TODO: Position the figures correctly along the y axis in the ChessFigure class
    ChessFigure pawnBlack_1(&pawn, std::make_pair(0, 1), PAWN, BLACK);
    ChessFigure pawnBlack_2(&pawn, std::make_pair(1, 1), PAWN, BLACK);
    ChessFigure pawnBlack_3(&pawn, std::make_pair(2, 1), PAWN, BLACK);
    ChessFigure pawnBlack_4(&pawn, std::make_pair(3, 1), PAWN, BLACK);
    ChessFigure pawnBlack_5(&pawn, std::make_pair(4, 1), PAWN, BLACK);
    ChessFigure pawnBlack_6(&pawn, std::make_pair(5, 1), PAWN, BLACK);
    ChessFigure pawnBlack_7(&pawn, std::make_pair(6, 1), PAWN, BLACK);
    ChessFigure pawnBlack_8(&pawn, std::make_pair(7, 1), PAWN, BLACK);
    ChessFigure rookBlack_1(&rook, std::make_pair(0, 0), ROOK, BLACK);
    ChessFigure rookBlack_2(&rook, std::make_pair(7, 0), ROOK, BLACK);
    ChessFigure knightBlack_1(&knight, std::make_pair(1, 0), KNIGHT, BLACK);
    ChessFigure knightBlack_2(&knight, std::make_pair(6, 0), KNIGHT, BLACK);
    ChessFigure bishopBlack_1(&bishop, std::make_pair(2, 0), BISHOP, BLACK);
    ChessFigure bishopBlack_2(&bishop, std::make_pair(5, 0), BISHOP, BLACK);
    ChessFigure queenBlack(&queen, std::make_pair(3, 0), QUEEN, BLACK);
    ChessFigure kingBlack(&king, std::make_pair(4, 0), KING, BLACK);

    ChessFigure pawnWhite_1(&pawn, std::make_pair(0, 6), PAWN, WHITE);
    ChessFigure pawnWhite_2(&pawn, std::make_pair(1, 6), PAWN, WHITE);
    ChessFigure pawnWhite_3(&pawn, std::make_pair(2, 6), PAWN, WHITE);
    ChessFigure pawnWhite_4(&pawn, std::make_pair(3, 6), PAWN, WHITE);
    ChessFigure pawnWhite_5(&pawn, std::make_pair(4, 6), PAWN, WHITE);
    ChessFigure pawnWhite_6(&pawn, std::make_pair(5, 6), PAWN, WHITE);
    ChessFigure pawnWhite_7(&pawn, std::make_pair(6, 6), PAWN, WHITE);
    ChessFigure pawnWhite_8(&pawn, std::make_pair(7, 6), PAWN, WHITE);
    ChessFigure rookWhite_1(&rook, std::make_pair(0, 7), ROOK, WHITE);
    ChessFigure rookWhite_2(&rook, std::make_pair(7, 7), ROOK, WHITE);
    ChessFigure knightWhite_1(&knight, std::make_pair(1, 7), KNIGHT, WHITE);
    ChessFigure knightWhite_2(&knight, std::make_pair(6, 7), KNIGHT, WHITE);
    ChessFigure bishopWhite_1(&bishop, std::make_pair(2, 7), BISHOP, WHITE);
    ChessFigure bishopWhite_2(&bishop, std::make_pair(5, 7), BISHOP, WHITE);
    ChessFigure queenWhite(&queen, std::make_pair(3, 7), QUEEN, WHITE);
    ChessFigure kingWhite(&king, std::make_pair(4, 7), KING, WHITE);

    DirectionalLight directionalLight(glm::vec3(0.0f, 3.0f, 0.0f),
                                      glm::vec3(0.1, 0.1, 0.1),
                                      glm::vec3(0.3f, 0.3f, 0.3f),
                                      glm::vec3(1.0f, 1.0f, 1.0f));

    PointLight pointLight(glm::vec3(0.0f, 3.0f, 0.0f),
                          glm::vec3(0.3, 0.3, 0.3),
                          glm::vec3(0.6f, 0.6f, 0.6f),
                          glm::vec3(1.0f, 1.0f, 1.0f),
                          1.0f, 0.09f, 0.032f);

    SpotLight spotLight(glm::vec3(0.0f, 3.0f, 0.0f),
                        glm::vec3(0.0f, -1.0f, 0.0f),
                        glm::vec3(0.0, 0.0, 0.1),
                        glm::vec3(0.0f, 0.0f, 1.0f),
                        glm::vec3(0.0f, 0.0f, 1.0f),
                        20.0f,1.0f, 0.09f, 0.032f);

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
        model = glm::translate(model, glm::vec3(1.75f, 0.0f, 1.75f));
        model = glm::rotate(model, (float)glm::radians(90.0), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
        boardShader.setUniformMatrix4fv("model", model);
        boardShader.setUniformMatrix4fv("view", view);
        boardShader.setUniformMatrix4fv("projection", projection);
        boardMaterial.activate(boardShader);
        pointLight.activate(boardShader);
        directionalLight.activate(boardShader);
        spotLight.activate(boardShader);
        boardShader.setUniform3fv("viewPosition", camera.Position);
        glBindVertexArray(boardVAO);
        glDrawElements(GL_TRIANGLES, sizeof(boardIndices) / sizeof(unsigned), GL_UNSIGNED_INT, 0);

        lightcubeShader.use();
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f)); // m * T
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); // m * T * R
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // m * T * R * S
        lightcubeShader.setUniformMatrix4fv("model", model);
        lightcubeShader.setUniformMatrix4fv("view", view);
        lightcubeShader.setUniformMatrix4fv("projection", projection);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // TODO: Move model to dedicated function
        modelShader.use();
        modelShader.setUniformMatrix4fv("view", view);
        modelShader.setUniformMatrix4fv("projection", projection);
        modelShader.setUniform3fv("viewPosition", camera.Position);

        pawnBlack_1.draw(modelShader);
        pawnBlack_2.draw(modelShader);
        pawnBlack_3.draw(modelShader);
        pawnBlack_4.draw(modelShader);
        pawnBlack_5.draw(modelShader);
        pawnBlack_6.draw(modelShader);
        pawnBlack_7.draw(modelShader);
        pawnBlack_8.draw(modelShader);
        rookBlack_1.draw(modelShader);
        rookBlack_2.draw(modelShader);
        knightBlack_1.draw(modelShader);
        knightBlack_2.draw(modelShader);
        bishopBlack_1.draw(modelShader);
        bishopBlack_2.draw(modelShader);
        queenBlack.draw(modelShader);
        kingBlack.draw(modelShader);

        pawnWhite_1.draw(modelShader);
        pawnWhite_2.draw(modelShader);
        pawnWhite_3.draw(modelShader);
        pawnWhite_4.draw(modelShader);
        pawnWhite_5.draw(modelShader);
        pawnWhite_6.draw(modelShader);
        pawnWhite_7.draw(modelShader);
        pawnWhite_8.draw(modelShader);
        rookWhite_1.draw(modelShader);
        rookWhite_2.draw(modelShader);
        knightWhite_1.draw(modelShader);
        knightWhite_2.draw(modelShader);
        bishopWhite_1.draw(modelShader);
        bishopWhite_2.draw(modelShader);
        queenWhite.draw(modelShader);
        kingWhite.draw(modelShader);

        pointLight.activate(modelShader);
        directionalLight.activate(modelShader);
        spotLight.activate(modelShader);

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

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}

void update(GLFWwindow *window) {

}