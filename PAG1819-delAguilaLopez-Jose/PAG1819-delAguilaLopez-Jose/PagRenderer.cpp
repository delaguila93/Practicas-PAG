#include "PagRenderer.h"
#include <iostream>
#include <GL\glew.h>

// - Aqu� se inicializa el singleton. Todav�a no se construye
// el objeto de la clase PagRenderer porque se usa inicializaci�n
// perezosa (lazy initialization).
// - La primera vez que se consulte el singleton se inicializar�.
PagRenderer *PagRenderer::instance = nullptr;

PagRenderer::PagRenderer() {
}
PagRenderer::~PagRenderer() {
}
// - M�todo que se encarga de redibujar el �rea OpenGL. Ser� llamado desde el callback
// void window_refresh_callback(GLFWwindow *window). Por ahora lo �nico que hace es
// borrar el �rea de dibujo OpenGL con la orden glClear. En pr�ximas pr�cticas se
// ir� completando.
void PagRenderer::refreshCallback() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	std::cout << "Refresh callback called" << std::endl;
}

void PagRenderer::framebuffersizeCallback(int width,int height) {
	glViewport(0, 0, width, height);
	std::cout << "Resize callback called" << std::endl;
}

void PagRenderer::keyCallback(int key, int scancode, int action, int mods) {
	std::cout << "Pulsada tecla " << key << std::endl;
}
// - Esta funci�n callback ser� llamada cada vez que se pulse alg�n bot�n
// del rat�n sobre el �rea de dibujo OpenGL.
void PagRenderer::mouseButtonCallback(int button, bool presion) {
	if ( presion ) {
		std::cout << "Pulsado el boton: " << button << std::endl;
	}
	else  {
		std::cout << "Soltado el boton: " << button << std::endl;
	}
}
// - Esta funci�n callback ser� llamada cada vez que se mueva la rueda
// del rat�n sobre el �rea de dibujo OpenGL.
void PagRenderer::scrollCallback(double xoffset, double yoffset) {
	std::cout << "Movida la rueda del raton " << xoffset <<
		" Unidades en horizontal y " << yoffset << " unidades en vertical" << std::endl;
}

/*
	La respuesta es no ya que OpenGl tarda mas en prepararse y se necesita que este preparado ya que si no se produciran fallos
*/




// - Acceder al singleton.
// Si es la primera vez que se llama a este m�todo de clase
// instance es nullptr y se construye. Es lo que se llama inicializaci�n
// perezosa. S�lo se inicializa cuando se necesita.
PagRenderer *PagRenderer::getInstancia() {
	if ( !instance ) {
		instance = new PagRenderer();
	}
	return instance;
}