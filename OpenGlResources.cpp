#pragma once

#include "OpenGlResources.h"
#include "Glfw.hpp"
#include "ProgramKit.h"
#include <memory>
#include <iostream>
#include "ProgramBuild.h";

std::unique_ptr<ProgramKit> OpenGlResources::initGlfw() {
	try {
		if (!glfwInit()) throw std::runtime_error("GLFW initialization failed.");

		GLFWwindow* window = GlfwUtils::createWindow("Quantic Simulator", 800, 600);
		if (!window) throw std::runtime_error("Failed to create GLFW window.");

		GlfwUtils::putOpenGlContext(window);

		GLuint shaderProgram = GlfwUtils::buildProgramShader();
		glUseProgram(shaderProgram);

		return std::make_unique<ProgramKit>(window, shaderProgram);
	}
	catch (std::runtime_error er) {
		std::cerr << "[ERROR]: " << er.what() << std::endl;
	}
	catch (std::invalid_argument er) {
		std::cerr << "[ERROR]: " << er.what() << std::endl;
	}
}

std::unique_ptr<ProgramKit> OpenGlResources::getProgram() {
	return std::make_unique<ProgramKit>(program->getWindow(), program->getProgram());
}

OpenGlResources::OpenGlResources(){
	std::cout << "Initing Vertex Arrays and Buffers" << std::endl;
	vertexArrayObject = new GLuint[12];
	std::cout << "Vertex Array Object - Ok" << std::endl;
	vertexBufferObject = new GLuint[12];
	std::cout << "Vertex Buffer Object - Ok" << std::endl;
	indexVAO = 0;
	indexVBO = 0;

	program = initGlfw();
	glGenVertexArrays(12, vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[0]);
	glGenBuffers(12, vertexBufferObject);
	glBindVertexArray(vertexArrayObject[0]);

	std::cout << "Program - Ok" << std::endl;
	std::cout << "Loading Figures Vertices" << std::endl;
	PB::loadVerticesForAll<Sphere>();
	std::cout << "Figures loaded - Ok" << std::endl;
	std::cout << "Buffers and Arrays - Ok" << std::endl;
}

OpenGlResources::~OpenGlResources() {
	glDeleteVertexArrays(12, vertexArrayObject);
	glDeleteBuffers(12, vertexBufferObject);
	delete[] vertexArrayObject;
	delete[] vertexBufferObject;
}

void OpenGlResources::pushToVBO(const void* data, float size, GLenum usage) {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[indexVBO]);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	indexVBO++;
} 

void OpenGlResources::pushToVAO(GLuint indexVBO, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) {
	glBindVertexArray(vertexArrayObject[indexVAO]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[indexVBO]);
	glVertexAttribPointer(indexVAO, numComponents, type, normalized, stride, offset);
	glEnableVertexAttribArray(indexVAO);
	glBindVertexArray(0);
	indexVAO++;
}


OpenGlResources resources;