#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "TdFigure.h"

class Sphere : public TdFigure
{
private:
	int numVertices;
	int numIndices;

	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> positions;
	std::vector<float> pvalues;
	std::vector<float> tvalues;
	std::vector<float> nvalues;

	void init(int);
	float toRadians(float degrees);

public:
	Sphere(int prec = 48);

	int getNumVertices();
	int getNumIndices();
	std::vector<int> getIndices();
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec2> getTexCoords();
	void spawn();
	bool loadVertices();
};

