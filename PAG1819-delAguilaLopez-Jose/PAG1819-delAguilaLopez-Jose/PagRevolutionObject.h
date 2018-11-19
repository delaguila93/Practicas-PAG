#pragma once
#include <vector>
#include <glm.hpp>
#include "PagEnumerations.h"
#include "PagSubdivisionProfile.h"
#include "PagVAO.h"
#include <GL\glew.h>


class PagRevolutionObject
{
public:
	PagRevolutionObject();
	PagRevolutionObject(std::vector<glm::vec2> points, unsigned int subdivisions, unsigned int slices);
	~PagRevolutionObject();

	bool isValid();
	bool has(PagRevObjParts part);
	
	void uso();//Funcion para comprobar el calculo de la subdivision de polilineas
	void revolution(PagRevObjParts part);
	void calculoTangentes(PagRevObjParts part);
	void calculoTexturas(PagRevObjParts part);

	void indicesMallaTriangulos(PagRevObjParts part);
	void indicesNubePuntos(PagRevObjParts part);
	void indicesLineas(PagRevObjParts part);
	void separate();

	void rellenarVBO(PagRevObjParts part);
	void rellenarIBO(PagRevObjParts part);

	void drawAsPoints(PagRevObjParts part);
	void drawAsTriangles(PagRevObjParts part);
	void drawAsLines(PagRevObjParts part);
	void escribirFichero(PagRevObjParts part);
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

	std::vector<GLuint>indicesLineBody;
	std::vector<GLuint>indicesLineTopFan;
	std::vector<GLuint>indicesLineBottomFan;

	std::vector<GLuint> indicesMallaBody;
	std::vector<GLuint> indicesMallaTopFan;
	std::vector<GLuint> indicesMallaBottomFan;

	std::vector<GLuint> indicesNubeTopFan;
	std::vector<GLuint> indicesNubeBody;
	std::vector<GLuint> indicesNubeBottomFan;

	PagSubdivisionProfile *perfilOriginal;
	PagSubdivisionProfile perfilSubdividido;

	PagVAO vaoCuerpo;
	PagVAO vaoTapaArriba;
	PagVAO vaoTapaAbajo;

};

