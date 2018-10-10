#pragma once
#include <cstdlib>
#include "PagSubdivisionProfile.h"

// - La clase PagRenderer encapsula toda la gestión del área de dibujo
// OpenGL, eventos, etc.
// Se implementa como un singleton para que pueda ser llamada desde las
// funciones callback del main.cpp

class PagRenderer
{
public:
	~PagRenderer();
	// - Aquí se definen los métodos que gestionarán los eventos que se produzcan
	// OpenGL. 
	void refreshCallback();
	void framebuffersizeCallback(int witdth,int height);
	void keyCallback(int key, int scancode, int action, int mods);
	void mouseButtonCallback(int button, bool presion);
	void scrollCallback(double xoffset, double yoffset);
	// - Este método de clase permite acceder al singleton. Cada vez
	// que se necesite llamar al renderer se hará a través de este
	// método.
	static PagRenderer *getInstancia();
private:
	// - En un singleton el constructor es privado. Esto impide que
	// se puedan construir nuevos renderers aparte del singleton
	PagRenderer();
	// - Este es el singleton, la única instancia de la clase PagRenderer
	// que se tiene en la aplicación.
	static PagRenderer *instance;
};