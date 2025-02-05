#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Sphere.h"
#include <glm/gtc/type_ptr.hpp>

class TDC {
private:
    float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 5.0f;
    float pyrLocX, pyrLocY, pyrLocZ;
    GLuint mvLoc, projLoc, vLoc, tfLoc;
    glm::mat4 pMat, vMat, mMat, mvMat, tMat, rMat;
    int windowHeight, windowWidth;
    float aspect;
    Sphere sphere = Sphere(46);
	int bucleIndex = 0;

    void getActualFrameSize(GLFWwindow* window) {
        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
        aspect = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

        pMat = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
        mMat = glm::mat4(1.0f);  // Sin traslación ni rotación
        vMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
        mvMat = vMat * mMat;
    }

    void updateUniformVariables(GLuint program) {
        mvLoc = glGetUniformLocation(program, "mv_matrix");
        projLoc = glGetUniformLocation(program, "proj_matrix");
        vLoc = glGetUniformLocation(program, "v_matrix");
        tfLoc = glGetUniformLocation(program, "tf");

        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    }

public:

    TDC() {};
    ~TDC() {};

    void tdcEvents(GLFWwindow* window, GLuint program) {
        getActualFrameSize(window);
        updateUniformVariables(program);
        glBindVertexArray(resources.vertexArrayObject[0]);

        glBindBuffer(GL_ARRAY_BUFFER, resources.vertexBufferObject[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, resources.vertexBufferObject[1]);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        sphere.spawn();
		glDrawArrays(GL_TRIANGLES, 0, 16);
        bucleIndex++;
    }
};