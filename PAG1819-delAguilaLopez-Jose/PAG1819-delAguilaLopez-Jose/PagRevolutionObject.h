#pragma once
#include <vector>
#include <glm.hpp>
#include "PagEnumerations.h"
#include "PagStructures.h"
#include <GL\glew.h>

class PagRevolutionObject
{
public:
	PagRevolutionObject();
	PagRevolutionObject(std::vector<glm::vec2> points, unsigned int subdivisions, unsigned int slices);
	~PagRevolutionObject();

	bool isValid();
	bool has(PagRevObjParts part);
	std::vector<PagPosNorm> getPositionsAndNormals(PagRevObjParts part);
	unsigned int getNPoints(PagRevObjParts part);
	std::vector<glm::vec3> getTangents(PagRevObjParts part);
	std::vector<glm::vec2> getTextureCoords(PagRevObjParts part);
	std::vector<GLuint> getIndices4PointCloud(PagRevObjParts part);
	std::vector<GLuint> getIndices4TriangleMesh(PagRevObjParts part);
private:
	unsigned int subdivisions;
	unsigned int slices;
	std::vector<glm::vec2> points;
};

