#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ErrorMessages.hpp"
#include <fstream>

class GlfwUtils {
public:
	static GLFWwindow* createWindow(const char* title, int width = 1200, int heigth = 800) {
		if (!glfwInit()) {
			throw std::runtime_error(ErrorMessages::GLFWINITFAILED);
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow* window = glfwCreateWindow(width, heigth, title, nullptr, nullptr);
		if (!window) {
			throw std::runtime_error(ErrorMessages::WINDOWCREATIONFAILED);
		}
		std::cout << "Window created - Ok" << std::endl;
		return window;
	}

	static void putOpenGlContext(GLFWwindow* window) {
		glfwMakeContextCurrent(window);
		if (glewInit() != GLEW_OK) {
			glfwDestroyWindow(window);
			glfwTerminate();
			throw std::runtime_error(ErrorMessages::OPENGLFAILEDTOINIT);
		}
		std::cout << "OpenGlContext - Ok" << std::endl;
	}

	static void putViewport(GLFWwindow* window, int width, int heigth) {
		glfwGetFramebufferSize(window, &width, &heigth);
		glViewport(0, 0, width, heigth);
		std::cout << "ViewPort - Ok" << std::endl;
	}

	static GLuint buildProgramShader() {
		GLint success;
		const std::string vertSrc = getGhlFileGlChar("vertex_core.ghl");
		const std::string fragSrc = getGhlFileGlChar("fragment_core.ghl");
		try {
			GLuint vertexShader = buildShader(GL_VERTEX_SHADER, vertSrc.c_str());
			GLuint fragmentShader = buildShader(GL_FRAGMENT_SHADER, fragSrc.c_str());

			GLuint program = glCreateProgram();
			glAttachShader(program, vertexShader);
			glAttachShader(program, fragmentShader);
			glLinkProgram(program);
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success) {
				std::cout << "Link success: " << success << std::endl;
				manageGlProgramLog(program);
				glDeleteShader(vertexShader);
				glDeleteShader(fragmentShader);
			}

			std::cout << "Shaders Loaded - Ok" << std::endl;
			return program;
		}
		catch (std::runtime_error ex) {
			throw;
		}
	}

	static GLuint buildShader(GLenum shaderType, const GLchar* shaderSource) {
		try {
			GLint success;
			GLuint shader = glCreateShader(shaderType);
			glShaderSource(shader, 1, &shaderSource, nullptr);
			glCompileShader(shader);
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				manageGlShaderLog(shader);
			}
			std::cout << "Shaders builded - Ok" << std::endl;
			return shader;
		}
		catch (std::runtime_error ex) {
			throw;
		}

	}

	static void manageGlShaderLog(GLuint shader) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		throw std::runtime_error(ErrorMessages::SHADERSCOMPILEERROR);
	}

	static void manageGlProgramLog(GLuint program) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		throw std::runtime_error(ErrorMessages::PROGRAMCOMPILEERROR);
	}

	static void setDefaultOptions() {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	static void initVertexArrays(GLuint* VAOs, int numVAOs) {
		glGenVertexArrays(numVAOs, VAOs);
		glBindVertexArray(VAOs[0]);
	}

private:
	static std::string getGhlFileGlChar(std::string fileName) {
		std::string temp = "";
		std::string src = "";

		std::ifstream inFile;

		inFile.open(fileName);
		if (!inFile.is_open()) {
			inFile.close();
			throw std::invalid_argument(fileName + " source not found");
		}
		while (std::getline(inFile, temp)) {
			src += temp + "\n";
		}
		inFile.close();
		return src;
	}
};