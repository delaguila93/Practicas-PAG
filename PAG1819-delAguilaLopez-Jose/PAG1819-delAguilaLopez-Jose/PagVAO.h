#include "PagStructures.h"
#include "PagEnumerations.h"
#include <iostream>
#include <vector>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
class PagVAO
{
public:
	PagVAO();
	~PagVAO();

	void rellenarVBO(std::vector<PagPosNorm> posAndNorms, ElementoObjeto elem);
	void rellenarIBO(std::vector<GLuint> indices4points, TipoVisualizacion tipo);

	void dibujar(std::vector<GLuint> indices4Points, TipoVisualizacion tipo);

	void dibujarTapa(std::vector<GLuint> indices4Points);

private:
	GLuint vao = 0;
	GLuint vbo [3] = {0, 0, 0}; // PosNorm , Texturas , Tangentes
	GLuint ibo [4] = {0, 0, 0,0}; // Puntos , Lineas , Malla , TapaMalla

};

