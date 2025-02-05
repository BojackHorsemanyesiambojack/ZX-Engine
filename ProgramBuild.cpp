#include "ProgramBuild.h"
#include "TdContext.h"
#include <iostream>

using namespace std;

namespace PB {

    void getMainLoop(GLuint program, GLFWwindow* window) {
        TDC tdc = TDC();
        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(program);
            tdc.tdcEvents(window, program);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    bool BuildProgram(GLuint program, GLFWwindow* window) {
        cout << "[INFO]:Building program..." << endl;
        cout << "[INFO]:Program and window loaded..." << endl;
        cout << "[INFO]:Initng Main Loop..." << endl;
        getMainLoop(program, window);
        return true;
    }
}
