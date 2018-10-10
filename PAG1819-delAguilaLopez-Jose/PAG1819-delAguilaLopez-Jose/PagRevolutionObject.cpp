#include "PagRevolutionObject.h"



PagRevolutionObject::PagRevolutionObject()
{
}

PagRevolutionObject::PagRevolutionObject(std::vector<glm::vec2> points, unsigned int subdivisions, unsigned int slices)
{
}


PagRevolutionObject::~PagRevolutionObject()
{
}

bool PagRevolutionObject::isValid()
{
	return false;
}

bool PagRevolutionObject::has(PagRevObjParts part)
{
	return false;
}

std::vector<PagPosNorm> PagRevolutionObject::getPositionsAndNormals(PagRevObjParts part)
{
	return std::vector<PagPosNorm>();
}

unsigned int PagRevolutionObject::getNPoints(PagRevObjParts part)
{
	return 0;
}

std::vector<glm::vec3> PagRevolutionObject::getTangents(PagRevObjParts part)
{
	return std::vector<glm::vec3>();
}

std::vector<glm::vec2> PagRevolutionObject::getTextureCoords(PagRevObjParts part)
{
	return std::vector<glm::vec2>();
}

std::vector<GLuint> PagRevolutionObject::getIndices4PointCloud(PagRevObjParts part)
{
	return std::vector<GLuint>();
}

std::vector<GLuint> PagRevolutionObject::getIndices4TriangleMesh(PagRevObjParts part)
{
	return std::vector<GLuint>();
}
