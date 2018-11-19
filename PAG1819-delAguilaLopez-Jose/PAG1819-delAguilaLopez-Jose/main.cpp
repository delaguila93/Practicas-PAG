#include <iostream>
#include <cstdlib>
// - IMPORTANTE: El include de Glew debe llamarse siempre ANTES de llamar al de GLFW.
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <Windows.h>
#include "PagRenderer.h"
/*
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}*/


// - Esta función callback será llamada cada vez que el área de dibujo
// OpenGL deba ser redibujada.
void window_refresh_callback(GLFWwindow *window) {
	// - Para llamar al método que refresca el área de dibujo OpenGL
	// primero hay que acceder al singleton. Esto se hace a través del método de clase
	// getInstance() que devuelve un puntero al singleton.
	PagRenderer::getInstancia()->refreshCallback();
	// - GLFW usa un doble buffer para que no haya parpadeo. Esta orden
	// intercambia el buffer back (que se ha estado dibujando) por el
	// que se mostraba hasta ahora front.
	glfwSwapBuffers(window);
}

// - Esta función callback será llamada cada vez que se cambie el tamaño
// del área de dibujo OpenGL.
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	PagRenderer::getInstancia()->framebuffersizeCallback(width, height);
}
// - Esta función callback será llamada cada vez que se pulse una tecla
// dirigida al área de dibujo OpenGL.
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	//En este condicional se comprueba si se ha pulsado la tecla "ESC" y en ese caso aqui es donde se tiene que realizar la gestion de cerrar la ventana
	// y no en PagRenderer ya que en este archivo se encarga de la gestion de la creacion de la ventana y de tambien cuando se cierra 
	if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS ) {		
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else {
		//80 p minuscula
		if ( key == 80 && action == GLFW_PRESS ) {
			PagRenderer::getInstancia()->cambioVisualizacion(PUNTOS);			
		}
		//84 t minuscula
		if ( key == 84 && action == GLFW_PRESS ) {
			PagRenderer::getInstancia()->cambioVisualizacion(MALLA);			
		}
		//76 l minuscula
		if ( key == 76 && action == GLFW_PRESS ) {
			PagRenderer::getInstancia()->cambioVisualizacion(LINEAS);			
		}
		//65 a minuscula
		if ( key == 65 && action == GLFW_PRESS ) {
			PagRenderer::getInstancia()->cambioVisualizacion(ALL);		
		}
		if ( key == 321 && action == GLFW_PRESS ) {
			PagRenderer::getInstancia()->cambioCamara(true);			
		}
		if ( key == 322 && action == GLFW_PRESS ) {
			PagRenderer::getInstancia()->cambioCamara(false);			
		}
		//Si se pulsa otra tecla distinta a "ESC" se llama al metodo de PagRenderer relativo a las teclas que se pulsan sin la necesidad del objeto GLFWwindow
		PagRenderer::getInstancia()->keyCallback(key, scancode, action, mods);
		window_refresh_callback(window);
	}
}
// - Esta función callback será llamada cada vez que se pulse algún botón
// del ratón sobre el área de dibujo OpenGL.
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {

	if ( action == GLFW_PRESS ) {
		PagRenderer::getInstancia()->mouseButtonCallback(button, true);
	}
	else if ( action == GLFW_RELEASE ) {
		PagRenderer::getInstancia()->mouseButtonCallback(button, false);
	}
}
// - Esta función callback será llamada cada vez que se mueva la rueda
// del ratón sobre el área de dibujo OpenGL.
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	PagRenderer::getInstancia()->scrollCallback(xoffset, yoffset);
}

int main() {
	std::cout << "Starting application PAG" << std::endl;
	// - Inicializar GLFW. Es un proceso que sólo debe realizarse una vez.
	if ( glfwInit() != GLFW_TRUE ) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	// - Definimos las características que queremos que tenga nuestro contexto gráfico
	// OpenGL. Por ejemplo, el número de muestras o modo Core Profile.
	glfwWindowHint(GLFW_SAMPLES, 4); // - Activa antialiasing con 4 muestras.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // - Esta y las
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // siguientes activan un contexto
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // OpenGL Core Profile 4.1.
												   // - Definimos la ventana de la aplicación y la creamos
	GLFWwindow *window;
	// - Tamaño, título de la ventana, en ventana y no en pantalla completa,
	// sin compartir recursos con otras ventanas.
	window = glfwCreateWindow(1024, 576, "Pag practice", NULL, NULL);
	// - Comprobamos si la creación de la ventana ha tenido éxito.
	if ( window == NULL ) {
		std::cout << "Failed to open GLFW window" << std::endl;
		glfwTerminate(); // - Liberamos los recursos que ocupaba GLFW.
		return -2;
	}
	// - Hace que la ventana que se pasa como argumento use el contexto
	// de GLFW cuyas características se han definido previamente.
	glfwMakeContextCurrent(window);
	// - Ahora inicializamos GLEW.
	// IMPORTANTE: Glew debe inicializarse siempre DESPUÉS de que se haya
	// inicializado y creado GLFW.
	glewExperimental = true;
	if ( glewInit() != GLEW_OK ) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate(); // - Liberamos los recursos que ocupaba GLFW.
		return -3;
	}
	// - Interrogamos a OpenGL para que nos informe de las propiedades del contexto
	// 3D construido.
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VENDOR) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	// - Registramos los callbacks que responderán a los eventos principales

	PagRenderer::getInstancia()->prepareOpenGL(1024,576);
	
	glfwSetWindowRefreshCallback(window, window_refresh_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	
	// - Establecemos un gris medio como color con el que se borrará el frame buffer.
	// No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
	glClearColor(0.6, 0.6, 0.6, 1.0);
	// - Ciclo de eventos de la aplicación. La condición de parada es que la
	// ventana principal deba cerrarse, por ejemplo, si el usuario pulsa el
	// botón de cerrar la ventana (la X).
	while ( !glfwWindowShouldClose(window) ) {
		// - Obtiene y organiza los eventos pendientes, tales como pulsaciones de
		// teclas o de ratón, etc. Siempre al final de cada iteración del ciclo de
		// eventos y después de glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// - Una vez terminado el ciclo de eventos, liberar recursos, etc.
	std::cout << "Finishing application PAG" << std::endl;
	glfwDestroyWindow(window); // - Cerramos y destruimos la ventana de la aplicación.
	glfwTerminate(); // - Liberamos los recursos que ocupaba GLFW.
					 // - Esta llamada es para impedir que la consola se cierre inmediatamente tras la
					 // ejecución y poder leer los mensajes. Se puede usar también getChar();
	system("pause");
}