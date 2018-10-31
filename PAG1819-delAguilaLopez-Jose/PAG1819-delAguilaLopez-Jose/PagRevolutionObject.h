#pragma once
#include <vector>
#include <glm.hpp>
#include "PagEnumerations.h"
#include "PagSubdivisionProfile.h"
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

	
	void uso();//Funcion para comprobar el calculo de la subdivision de polilineas
	void revolution(PagRevObjParts part);
	void calculoTangentes(PagRevObjParts part);
	void calculoTexturas(PagRevObjParts part);

	void indicesMallaTriangulos(PagRevObjParts part);
	void indicesNubePuntos(PagRevObjParts part);
	void separate();
private:
	unsigned int subdivisions;
	unsigned int slices;
	std::vector<glm::vec2> points;
	std::vector<glm::vec2> normales;

	std::vector<glm::vec2> pointsTopFan;
	std::vector<glm::vec2> pointsBottomFan;
	std::vector<glm::vec2> pointsBody;

	std::vector<PagPosNorm> posNorm;
	std::vector<PagPosNorm> posNormBody;
	std::vector<PagPosNorm> posNormTopFan;
	std::vector<PagPosNorm> posNormBottomFan;
	std::vector<glm::vec3> tangentes;
	std::vector<glm::vec2> texturas;

	std::vector<GLuint> indicesMalla;
	std::vector<GLuint> indicesNube;

	PagSubdivisionProfile *perfilOriginal;
	PagSubdivisionProfile perfilSubdividido;

};

