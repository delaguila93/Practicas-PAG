#pragma once

#include <vector>
#include <glm.hpp>

class PagSubdivisionProfile
{
public:
	PagSubdivisionProfile();
	PagSubdivisionProfile(std::vector<glm::vec2> points);
	~PagSubdivisionProfile();

	PagSubdivisionProfile subdivide(unsigned int times);

private:
	std::vector<glm::vec2> points;

};

