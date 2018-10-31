#include "PagSubdivisionProfile.h"



PagSubdivisionProfile::PagSubdivisionProfile()
{
}

PagSubdivisionProfile::PagSubdivisionProfile(std::vector<glm::vec2> _points)
{

	for ( int i = 0; i < _points.size(); ++i ) {
		points.push_back(_points [i]);
	}

	for ( int i = 0; i < 3; i++ ) {
		object [i] = false;
	}
}


PagSubdivisionProfile::~PagSubdivisionProfile()
{
}
bool PagSubdivisionProfile::valid()
{
	if ( points.size() == 1 ) {
		return false;
	}
	else if ( points.size() == 2 ) {
		if ( points [1].x == 0 || points [0].x == 0 ) {
			return false;
		}
	}

	return true;
}

void PagSubdivisionProfile::clean() {
	std::vector<glm::vec2>::iterator it;
	it = points.begin();
	if ( it->x < DBL_EPSILON ) { //Tapa de abajo
		object [PAG_BOTTOM_FAN] = true;
	}
	++it;
	if ( points.size() > 2 )
		object [PAG_BODY] = true; //Cuerpo

	while ( it != points.end() - 1 ) {
		if ( it->x < DBL_EPSILON ) {
			points.erase(it);
		}
		++it;
	}

	if ( it->x < DBL_EPSILON ) { //Tapa de arriba
		object [PAG_TOP_FAN] = true;
	}


}

bool PagSubdivisionProfile::has(PagRevObjParts part) {

	if ( object [part] == false ) {
		return false;
	}
	return true;
}

void PagSubdivisionProfile::calculoNormales() {
	int tamano = points.size() - 1;
	float aux = 0, mod = 0, valor = 0;
	glm::vec2 v1, v2, v, punto0;
	punto0 = points [points.size() - 1] - points [0];
	glm::mod(points [points.size() - 1], points [0]);
	texturasV.push_back(0);

	for ( int i = 1; i < tamano - 1; ++i ) { // Texturas
		v1 = points [i] - points [i - 1];
		aux += sqrt(pow(v1.x, 2) + pow(v1.y, 2));
	}

	v2 = points [1] - points [0];
	glm::normalize(v2);
	aux = v2.x;
	v2.x = v2.y;
	v2.y = -aux;
	normales.push_back(v2);

	for ( int i = 1; i <= tamano - 1; ++i ) {

		v1 = points [i] - points [i - 1];
		v2 = points [i + 1] - points [i];

		//Calculos de textura
		mod += sqrt(pow(v1.x, 2) + pow(v1.y, 2));
		valor = mod / aux;
		texturasV.push_back(valor);

		glm::normalize(v1);
		aux = v1.x;
		v1.x = v1.y;
		v1.y = -aux;

		glm::normalize(v2);
		aux = v2.x;
		v2.x = v2.y;
		v2.y = -aux;

		v.x = (v1.x + v2.x) / 2;
		v.y = (v2.y + v2.y) / 2;
		normales.push_back(v);
	}

	v1 = points [points.size() - 1] - points [points.size() - 2];
	texturasV.push_back(glm::mod(v1.x,v1.y));
	glm::normalize(v1);
	aux = v1.x;
	v1.x = v1.y;
	v1.y = -aux;
	normales.push_back(v1);
}

std::vector<glm::vec2> PagSubdivisionProfile::getPuntos() {
	return points;
}

std::vector<glm::vec2> PagSubdivisionProfile::getNormales()
{
	return normales;
}

PagSubdivisionProfile PagSubdivisionProfile::subdividePrivate(PagSubdivisionProfile &profile, unsigned int times) {
	std::vector<glm::vec2> puntosFinales(profile.points);

	glm::vec2 puntoAnterior;
	glm::vec2 punto;

	int tamano = 0;
	profile.points.clear();
	profile.points.push_back(puntosFinales[0]);
	tamano = puntosFinales.size();

	for ( int i = 1; i < tamano - 1; ++i ) {

		puntoAnterior.x = (puntosFinales [i - 1].x + puntosFinales [i].x) / 2;
		puntoAnterior.y = (puntosFinales [i - 1].y + puntosFinales [i].y) / 2;

		punto.x = (((3 * puntosFinales [i].x) / 4) + (puntosFinales [i - 1].x / 8) + (puntosFinales [i + 1].x / 8));
		punto.y = (((3 * puntosFinales [i].y) / 4) + (puntosFinales [i - 1].y / 8) + (puntosFinales [i + 1].y / 8));

		profile.points.push_back(puntoAnterior);
		profile.points.push_back(punto);

	}

	puntoAnterior.x = (puntosFinales [puntosFinales.size() - 2].x + puntosFinales [puntosFinales.size() - 1].x) / 2;
	puntoAnterior.y = (puntosFinales [puntosFinales.size() - 2].y + puntosFinales [puntosFinales.size() - 1].y) / 2;

	profile.points.push_back(puntoAnterior);
	profile.points.push_back(puntosFinales [puntosFinales.size() - 1]);

	if ( --times > 0 ) {		
		subdividePrivate(profile, times);
	}

	return profile;
}


void PagSubdivisionProfile::mostrarPerfil() {
	int tam = points.size();
	for ( int i = 0; i < tam; ++i ) {
		std::cout <<"Punto "<< i + 1 << std::endl;
		std::cout << "X : " << points [i].x << std::endl;
		std::cout << "Y : " << points [i].y << std::endl;
	}
}

void PagSubdivisionProfile::setPoints(std::vector<glm::vec2> _points)
{
	points.clear();
	for ( int i = 0; i < _points.size(); ++i ) {
		points.push_back(_points [i]);
	}
}


PagSubdivisionProfile PagSubdivisionProfile::subdivide(unsigned int times) {

	PagSubdivisionProfile division(points);
	division = subdividePrivate(division, times);

	return division ;
}

