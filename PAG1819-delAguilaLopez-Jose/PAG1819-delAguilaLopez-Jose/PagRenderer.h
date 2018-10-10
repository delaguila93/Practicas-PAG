#pragma once
#include <cstdlib>
#include "PagSubdivisionProfile.h"

// - La clase PagRenderer encapsula toda la gesti�n del �rea de dibujo
// OpenGL, eventos, etc.
// Se implementa como un singleton para que pueda ser llamada desde las
// funciones callback del main.cpp

class PagRenderer
{
public:
	~PagRenderer();
	// - Aqu� se definen los m�todos que gestionar�n los eventos que se produzcan
	// OpenGL. 
	void refreshCallback();
	void framebuffersizeCallback(int witdth,int height);
	void keyCallback(int key, int scancode, int action, int mods);
	void mouseButtonCallback(int button, bool presion);
	void scrollCallback(double xoffset, double yoffset);
	// - Este m�todo de clase permite acceder al singleton. Cada vez
	// que se necesite llamar al renderer se har� a trav�s de este
	// m�todo.
	static PagRenderer *getInstancia();
private:
	// - En un singleton el constructor es privado. Esto impide que
	// se puedan construir nuevos renderers aparte del singleton
	PagRenderer();
	// - Este es el singleton, la �nica instancia de la clase PagRenderer
	// que se tiene en la aplicaci�n.
	static PagRenderer *instance;
};