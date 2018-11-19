#include "PagRenderer.h"
#include <iostream>
#include <GL\glew.h>

// - Aquí se inicializa el singleton. Todavía no se construye
// el objeto de la clase PagRenderer porque se usa inicialización
// perezosa (lazy initialization).
// - La primera vez que se consulte el singleton se inicializará.
PagRenderer *PagRenderer::instance = nullptr;

PagRenderer::PagRenderer() :tipoVisualizacion(PUNTOS), camara(true) {

}
PagRenderer::~PagRenderer() {
}
// - Método que se encarga de redibujar el área OpenGL. Será llamado desde el callback
// void window_refresh_callback(GLFWwindow *window). Por ahora lo único que hace es
// borrar el área de dibujo OpenGL con la orden glClear. En próximas prácticas se
// irá completando.
void PagRenderer::refreshCallback() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glm::mat4 v, p;
	if ( camara ) {
		
		v = glm::lookAt(glm::vec3(20.0f, 48.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));// Posicion,  LookAt , Vector Arriba
		p = glm::perspective(glm::radians(42.0f), 1024.0f / 768.0f, 1.0f, 125.0f);
	}
	else {
		
		v = glm::lookAt(glm::vec3(80.0f, 10.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));// Posicion,  LookAt , Vector Arriba
		p = glm::perspective(glm::radians(42.0f), float(width / height), 1.0f, 125.0f);
	}

	switch ( tipoVisualizacion )
	{
	case PUNTOS:
		pointShader.use();
		pointShader.setUniform("pointSize", 7.0f);
		pointShader.setUniform("vColor", glm::vec3(0.0f, 0.0f, 1.0f));
		pointShader.setUniform("mModelViewProj", p*v);

		objeto.drawAsPoints(PAG_BOTTOM_FAN);
		objeto.drawAsPoints(PAG_BODY);
		objeto.drawAsPoints(PAG_TOP_FAN);
		break;
	case MALLA:
		triangleShader.use();
		triangleShader.setUniform("mModelViewProj", p*v);
		objeto.drawAsTriangles(PAG_BOTTOM_FAN);
		objeto.drawAsTriangles(PAG_BODY);
		objeto.drawAsTriangles(PAG_TOP_FAN);
		break;
	case LINEAS:
		lineShader.use();
		lineShader.setUniform("vColor", glm::vec3(0.0f, 0.0f, 1.0f));
		lineShader.setUniform("mModelViewProj", p*v);
		objeto.drawAsLines(PAG_BOTTOM_FAN);
		objeto.drawAsLines(PAG_BODY);
		objeto.drawAsLines(PAG_TOP_FAN);
		break;
	case ALL:
		pointShader.use();
		pointShader.setUniform("pointSize", 7.0f);
		pointShader.setUniform("vColor", glm::vec3(0.0f, 0.0f, 1.0f));
		pointShader.setUniform("mModelViewProj", p*v);

		objeto.drawAsPoints(PAG_BOTTOM_FAN);
		objeto.drawAsPoints(PAG_BODY);
		objeto.drawAsPoints(PAG_TOP_FAN);

		triangleShader.use();
		triangleShader.setUniform("mModelViewProj", p*v);
		objeto.drawAsTriangles(PAG_BOTTOM_FAN);
		objeto.drawAsTriangles(PAG_BODY);
		objeto.drawAsTriangles(PAG_TOP_FAN);

		lineShader.use();
		lineShader.setUniform("vColor", glm::vec3(0.0f, 0.0f, 1.0f));
		lineShader.setUniform("mModelViewProj", p*v);
		objeto.drawAsLines(PAG_BOTTOM_FAN);
		objeto.drawAsLines(PAG_BODY);
		objeto.drawAsLines(PAG_TOP_FAN);
		break;
	}

	std::cout << "Refresh callback called" << std::endl;
}

void PagRenderer::framebuffersizeCallback(int _width, int _height) {
	width = _width;
	height = _height;
	glViewport(0, 0, width, height);

	std::cout << "Resize callback called" << std::endl;
}

void PagRenderer::keyCallback(int key, int scancode, int action, int mods) {
	std::cout << "Pulsada tecla " << key << std::endl;
}
// - Esta función callback será llamada cada vez que se pulse algún botón
// del ratón sobre el área de dibujo OpenGL.
void PagRenderer::mouseButtonCallback(int button, bool presion) {
	if ( presion ) {
		std::cout << "Pulsado el boton: " << button << std::endl;
	}
	else {
		std::cout << "Soltado el boton: " << button << std::endl;
	}
}
// - Esta función callback será llamada cada vez que se mueva la rueda
// del ratón sobre el área de dibujo OpenGL.
void PagRenderer::scrollCallback(double xoffset, double yoffset) {
	std::cout << "Movida la rueda del raton " << xoffset <<
		" Unidades en horizontal y " << yoffset << " unidades en vertical" << std::endl;
}

void PagRenderer::cambioVisualizacion(TipoVisualizacion tipo)
{
	tipoVisualizacion = tipo;
}

void PagRenderer::cambioCamara(bool valor)
{
	camara = valor;
}

/*
	La respuesta es no ya que OpenGl tarda mas en prepararse y se necesita que este preparado ya que si no se produciran fallos
*/


// - Acceder al singleton.
// Si es la primera vez que se llama a este método de clase
// instance es nullptr y se construye. Es lo que se llama inicialización
// perezosa. Sólo se inicializa cuando se necesita.
PagRenderer *PagRenderer::getInstancia() {
	if ( !instance ) {
		instance = new PagRenderer();
	}
	return instance;
}

void PagRenderer::prepareOpenGL(int _width, int _height) {

	width = _width;
	height = _height;

	glEnable(GL_PROGRAM_POINT_SIZE);

	std::vector<glm::vec2> puntos;
	puntos = {
		glm::vec2(0.0,0.0),
		glm::vec2(16.0,0.0),
		glm::vec2(16.0,16.0),
		glm::vec2(0.0,16.0),
	};

	pointShader.createShaderProgram("pointShader");
	triangleShader.createShaderProgram("triangleShader");
	lineShader.createShaderProgram("lineShader");

	objeto = PagRevolutionObject(puntos, 5, 10); // puntos en 2D sin hacerle la subdivision, nº de subdivisiones y por ultimo numero de particiones que se desea
	objeto.uso();//Hace la subdivision de polilineas

	objeto.separate();
	objeto.revolution(PAG_BOTTOM_FAN);
	objeto.revolution(PAG_BODY);
	objeto.revolution(PAG_TOP_FAN);

	objeto.escribirFichero(PAG_BODY);

	objeto.indicesNubePuntos(PAG_BOTTOM_FAN);
	objeto.indicesNubePuntos(PAG_BODY);
	objeto.indicesNubePuntos(PAG_TOP_FAN);

	objeto.indicesMallaTriangulos(PAG_BOTTOM_FAN);
	objeto.indicesMallaTriangulos(PAG_BODY);
	objeto.indicesMallaTriangulos(PAG_TOP_FAN);

	objeto.indicesLineas(PAG_BOTTOM_FAN);
	objeto.indicesLineas(PAG_BODY);
	objeto.indicesLineas(PAG_TOP_FAN);

	objeto.rellenarVBO(PAG_BOTTOM_FAN);
	objeto.rellenarVBO(PAG_BODY);
	objeto.rellenarVBO(PAG_TOP_FAN);

	objeto.rellenarIBO(PAG_BOTTOM_FAN);
	objeto.rellenarIBO(PAG_BODY);
	objeto.rellenarIBO(PAG_TOP_FAN);

}
