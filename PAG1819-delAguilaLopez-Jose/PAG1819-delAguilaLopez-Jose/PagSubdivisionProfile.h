#pragma once

#include <iostream>
#include <vector>
#include <glm.hpp>
#include "PagEnumerations.h"

class PagSubdivisionProfile
{
public:
	PagSubdivisionProfile();
	PagSubdivisionProfile(std::vector<glm::vec2> points);
	~PagSubdivisionProfile();

	PagSubdivisionProfile subdivide(unsigned int times);
	bool valid();
	void clean();
	bool has(PagRevObjParts part);
	void calculoNormales();

	std::vector<glm::vec2> getPuntos();
	std::vector<glm::vec2> getNormales();

	void mostrarPerfil();
	void setPoints(std::vector<glm::vec2> _points);
	std::vector<float> getCoordVTexturas() { return texturasV; }

private:
	PagSubdivisionProfile subdividePrivate(PagSubdivisionProfile &profile,unsigned int times);
	std::vector<glm::vec2> points;
	std::vector<glm::vec2> normales;
	std::vector<float> texturasV;
	bool object [3];

};

