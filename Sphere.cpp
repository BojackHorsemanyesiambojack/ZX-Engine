#include "Sphere.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "OpenGlResources.h"
#include <iostream>

Sphere::Sphere(int prec) {
	init(prec);
}

float Sphere::toRadians(float degrees) {
	return glm::radians(degrees);
}

void Sphere::init(int prec) {
	numVertices = (prec + 1) * (prec + 1);
	numIndices = prec * prec * 6;
	float theta, phi;
	float thetaFac = glm::two_pi<float>() / prec;
	float phiFac = glm::pi<float>() / prec;
	float x, y, z;

	for (int i = 0; i <= prec; i++) {
		for (int j = 0; j <= prec; j++) {
			theta = i * thetaFac;
			phi = i * phiFac;
			x = sin(phi) * cos(theta);
			y = cos(phi);
			z = sin(phi) * sin(theta);
			normals.push_back(glm::vec3(x, y, z));
			positions.push_back(glm::vec3(x, y, z) * 0.5f);
			texCoords.push_back(glm::vec2(static_cast<float>(j) / prec, static_cast<float>(i) / prec));
		}
	}

	for (int i = 0; i < prec; i++) {
		for (int j = 0; j < prec; j++) {
			indices.push_back(i * (prec + 1) + j);
			indices.push_back((i + 1) * (prec + 1) + j);
			indices.push_back((i + 1) * (prec + 1) + (j + 1));
			indices.push_back(i * (prec + 1) + j);
			indices.push_back((i + 1) * (prec + 1) + (j + 1));
			indices.push_back(i * (prec + 1) + (j + 1));
		}
	}

	this->vertices = positions;
	this->normals = normals;
	this->texCoords = texCoords;
	this->indices = indices;
}

bool Sphere::loadVertices() {
	if (vertices.empty() || normals.empty() || texCoords.empty() || indices.empty()) {
		std::cerr << "Error: Datos de la esfera no inicializados correctamente." << std::endl;
		return false;
	}

	for (int i = 0; i < numIndices; i++) {
		if (indices[i] < 0 || indices[i] >= vertices.size() ||
			indices[i] >= normals.size() || indices[i] >= texCoords.size()) {
			std::cerr << "Error: Índice fuera de rango en la posición " << i << std::endl;
			return false;
		}

		pvalues.push_back(vertices[indices[i]].x);
		pvalues.push_back(vertices[indices[i]].y);
		pvalues.push_back(vertices[indices[i]].z);
		tvalues.push_back(texCoords[indices[i]].s);
		tvalues.push_back(texCoords[indices[i]].t);
		nvalues.push_back(normals[indices[i]].x);
		nvalues.push_back(normals[indices[i]].y);
		nvalues.push_back(normals[indices[i]].z);
	}

	glBindVertexArray(resources.vertexArrayObject[0]);

	resources.pushToVBO(&pvalues[0], pvalues.size() * sizeof(float), GL_STATIC_DRAW);
	resources.pushToVAO(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // Atributo de posición (3 componentes)

	resources.pushToVBO(&tvalues[0], tvalues.size() * sizeof(float), GL_STATIC_DRAW);
	resources.pushToVAO(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0); // Atributo de textura (2 componentes)

	resources.pushToVBO(&nvalues[0], nvalues.size() * sizeof(float), GL_STATIC_DRAW);
	resources.pushToVAO(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // Atributo de normales (3 componentes)

	glBindVertexArray(0); // Desvincula el VAO

	return true;
}

void Sphere::spawn() {
	std::cout << "Sphere Spawning..." << std::endl;
	std::cout << "Sphere Spawned!" << std::endl;
}

int Sphere::getNumVertices() {
	return numVertices;
}

int Sphere::getNumIndices() {
	return numIndices;
}