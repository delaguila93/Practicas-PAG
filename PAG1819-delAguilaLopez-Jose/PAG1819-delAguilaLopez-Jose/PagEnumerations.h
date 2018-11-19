#pragma once

enum PagRevObjParts : int {
	PAG_BODY = 0,
	PAG_TOP_FAN = 1,
	PAG_BOTTOM_FAN = 2
};

// IBO
enum TipoVisualizacion : int {
	PUNTOS = 0,
	LINEAS = 1,
	MALLA = 2,
	TAPAMALLA = 3,
	ALL = 4
};

// VBO
enum ElementoObjeto : int {
	POSNORM = 0,
	TEXTURAS = 1,
	TANGENTES = 2
};
