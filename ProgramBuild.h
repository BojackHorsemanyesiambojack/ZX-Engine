// ProgramBuild.h
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "OpenGlResources.h"
#include "TdContext.h"
#include "Sphere.h"

namespace PB {
    void getMainLoop(GLuint program, GLFWwindow* window);

    bool BuildProgram(GLuint program, GLFWwindow* window);

    template <typename... Shapes>
    static bool loadVerticesForAll() {
        try {
            std::cout << "Loading vertices for all shapes..." << std::endl;
            (loadSingle<Shapes>(), ...);
            return true;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        }
    }

    template <typename Shape>
    static void loadSingle() {
        Shape figure;
        figure.loadVertices();
    }
}
