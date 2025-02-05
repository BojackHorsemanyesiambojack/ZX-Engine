#pragma once

#include <GlfW/glfw3.h>
#include <Gl/glew.h>

class ProgramKit {
    GLFWwindow* programWindow;
    GLuint program;

public:
    ProgramKit();
    ProgramKit(GLFWwindow* window, GLuint programInt)
        : programWindow(window), program(programInt) {
    }

    ~ProgramKit() {
        if (programWindow) {
            glfwDestroyWindow(programWindow);
        }
    }

    GLFWwindow* getWindow() const { return programWindow; }
    GLuint getProgram() const { return program; }
};