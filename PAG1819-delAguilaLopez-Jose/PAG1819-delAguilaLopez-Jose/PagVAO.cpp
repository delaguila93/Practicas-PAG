#include "PagVAO.h"



PagVAO::PagVAO()
{

	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glGenBuffers(3, vbo);


	glBindBuffer(GLenum(GL_ARRAY_BUFFER), vbo[POSNORM]);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
		GL_FLOAT, GL_FALSE, sizeof(PagPosNorm),
		((GLubyte *)NULL + (0)));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat),
		GL_FLOAT, GL_FALSE, sizeof(PagPosNorm),
		((GLubyte *)NULL + (sizeof(glm::vec3))));

	glGenBuffers(4, ibo);



}



PagVAO::~PagVAO()
{
}


void PagVAO::rellenarVBO(std::vector<PagPosNorm> posAndNorm, ElementoObjeto elem) {
	glBindVertexArray(vao);

	switch ( elem )
	{
	case POSNORM:
		
		glBindBuffer(GLenum(GL_ARRAY_BUFFER), vbo [POSNORM]);
		glBufferData(GL_ARRAY_BUFFER, posAndNorm.size() * sizeof(PagPosNorm),
			posAndNorm.data(), GL_STATIC_DRAW);
		break;
	case TEXTURAS:
		
		glBindBuffer(GLenum(GL_ARRAY_BUFFER), vbo [TEXTURAS]);
		glBufferData(GL_ARRAY_BUFFER, posAndNorm.size() * sizeof(glm::vec2),
			posAndNorm.data(), GL_STATIC_DRAW);
		break;
	case TANGENTES:
		
		glBindBuffer(GLenum(GL_ARRAY_BUFFER), vbo [TANGENTES]);
		glBufferData(GL_ARRAY_BUFFER, posAndNorm.size() * sizeof(glm::vec3),
			posAndNorm.data(), GL_STATIC_DRAW);
		break;
	}

}


void PagVAO::rellenarIBO(std::vector<GLuint> indices4points, TipoVisualizacion tipo) {
	glBindVertexArray(vao);

	switch ( tipo )
	{
	case PUNTOS:
		glBindBuffer(GLenum(GL_ELEMENT_ARRAY_BUFFER), ibo [PUNTOS]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices4points.size() * sizeof(GLuint),
			indices4points.data(), GL_STATIC_DRAW);
		break;
	case LINEAS:
		glBindBuffer(GLenum(GL_ELEMENT_ARRAY_BUFFER), ibo [LINEAS]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices4points.size() * sizeof(GLuint),
			indices4points.data(), GL_STATIC_DRAW);
		break;
	case MALLA:
		glBindBuffer(GLenum(GL_ELEMENT_ARRAY_BUFFER), ibo [MALLA]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices4points.size() * sizeof(GLuint),
			indices4points.data(), GL_STATIC_DRAW);
		break;
	case TAPAMALLA:
		glBindBuffer(GLenum(GL_ELEMENT_ARRAY_BUFFER), ibo [TAPAMALLA]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices4points.size() * sizeof(GLuint),
			indices4points.data(), GL_STATIC_DRAW);
		break;
	}

}

/*
Con este metodo se dibuja la tapa del objeto
*/

void PagVAO::dibujarTapa(std::vector<GLuint> indices4Points) {
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xFFFFFFFF);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[TAPAMALLA]);
	glDrawElements(GL_TRIANGLE_FAN, indices4Points.size(), GL_UNSIGNED_INT, NULL);
}



void PagVAO::dibujar(std::vector<GLuint> indices4Points, TipoVisualizacion tipo) {

	glBindVertexArray(vao);

	switch ( tipo )
	{
	case PUNTOS:
		glBindBuffer(GLenum(GL_ELEMENT_ARRAY_BUFFER), ibo [PUNTOS]);
		glDrawElements(GL_POINTS, indices4Points.size(), GL_UNSIGNED_INT, NULL);
		break;
	case LINEAS:
		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(0xFFFFFFFF);
		glBindBuffer(GLenum(GL_ELEMENT_ARRAY_BUFFER), ibo [LINEAS]);
		glDrawElements(GL_LINE_STRIP, indices4Points.size(), GL_UNSIGNED_INT, NULL);
		break;
	case MALLA:
		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(0xFFFFFFFF);
		glBindBuffer(GLenum(GL_ELEMENT_ARRAY_BUFFER), ibo [MALLA]);
		glDrawElements(GL_TRIANGLE_STRIP, indices4Points.size(), GL_UNSIGNED_INT, NULL);
		break;

	}

}