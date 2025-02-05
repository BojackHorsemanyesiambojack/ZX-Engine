#pragma once
#include <GL/glew.h>
#include "ProgramKit.h"
#include <memory>

class OpenGlResources
{
public:
	GLuint* vertexArrayObject;
	GLuint* vertexBufferObject;
	std::unique_ptr<ProgramKit> program;

	int indexVAO;
	int indexVBO;
	OpenGlResources();
	~OpenGlResources();
	std::unique_ptr<ProgramKit> initGlfw();
	std::unique_ptr<ProgramKit> getProgram();
	void createVertexArrayObject();
	void createVertexBufferObject();
	void bindVertexArrayObject();
	void bindVertexBufferObject();
	void unbindVertexArrayObject();
	void unbindVertexBufferObject();
	void deleteVertexArrayObject();
	void deleteVertexBufferObject();
	void pushToVBO(const void* data, float size, GLenum usage = GL_STATIC_DRAW);
	void pushToVAO(GLuint indexVBO, GLint numComponents, GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE, GLsizei stride = 0, const void* offset = nullptr);
	void deleteAll();
};

extern OpenGlResources resources;