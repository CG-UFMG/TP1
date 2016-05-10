#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.h"
#include "resource_manager.h"

const GLuint SCR_WIDTH = 800;
const GLuint SCR_HEIGHT = 600;

Game game(SCR_WIDTH, SCR_HEIGHT);

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow* window, int button, int action, int mods);
void cursorEnterCallback(GLFWwindow* window, int entered);
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);

int main() {
    GLFWwindow* window;
    GLfloat delta = 0.0f;
    GLfloat lastFrame = 0.0f;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TP1 - Breakout", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
    if (glewInit() != GLEW_OK)
        return -1;
    glGetError();

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseCallback);
    glfwSetCursorEnterCallback(window, cursorEnterCallback);

    game.init();

    while (!glfwWindowShouldClose(window)) {
        double xpos, ypos;
        GLfloat currentFrame = glfwGetTime();
        delta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwGetCursorPos(window, &xpos, &ypos);

        game.processInput(delta);
        game.movePlayer(delta, xpos, ypos);
        game.update(delta);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game.render();

        glfwSwapBuffers(window);
    }

    ResourceManager::clear();
    glfwTerminate();

    return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_R && action == GLFW_PRESS)
        game.reset();
    else if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            game.keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
            game.keys[key] = GL_FALSE;
    }
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        game.pauseOrContinue();
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        game.printGameStatus();
}

void cursorEnterCallback(GLFWwindow* window, int entered) {
    if (entered)
        game.playerEnabled = GL_TRUE;
    else
        game.playerEnabled = GL_FALSE;
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
}
