#include "PagRevolutionObject.h"



PagRevolutionObject::PagRevolutionObject()
{
}

PagRevolutionObject::PagRevolutionObject(std::vector<glm::vec2> points, unsigned int subdivisions, unsigned int slices):subdivisions(subdivisions),slices(slices)
{
	perfilOriginal = new PagSubdivisionProfile(points);
}


PagRevolutionObject::~PagRevolutionObject()
{
}

bool PagRevolutionObject::isValid()
{
	if ( !perfilSubdividido.valid() ) {
		return false;
	}
	return true;

}

bool PagRevolutionObject::has(PagRevObjParts part)
{
	if ( perfilSubdividido.has(part) ) {
		return true;
	}
	return false;
}

std::vector<PagPosNorm> PagRevolutionObject::getPositionsAndNormals(PagRevObjParts part)
{
	return posNorm;
}

unsigned int PagRevolutionObject::getNPoints(PagRevObjParts part)
{
	return posNorm.size();
}

std::vector<glm::vec3> PagRevolutionObject::getTangents(PagRevObjParts part)
{
	return tangentes;
}

std::vector<glm::vec2> PagRevolutionObject::getTextureCoords(PagRevObjParts part)
{
	return texturas;
}

std::vector<GLuint> PagRevolutionObject::getIndices4PointCloud(PagRevObjParts part)
{
	return indicesNube;
}

std::vector<GLuint> PagRevolutionObject::getIndices4TriangleMesh(PagRevObjParts part)
{
	return indicesMalla;
}

void PagRevolutionObject::revolution(PagRevObjParts part){
	struct PagPosNorm objeto ;
	glm::vec3 punto;
	glm::vec3 normal; //Mismo calculo que posiciones
	int a = 0;
	int tam = points.size() - 1;
	if ( has(part) ) {
		switch ( part )
		{
		case PAG_BODY:

			double x, z;
			for ( int i = 0; i < pointsBody.size(); ++i ) {
				for ( int j = 0; j < slices; ++j ) {

					a = j*((2 * glm::radians(180.0)) / slices);
					x = pointsBody [i].x * cos(a);
					z = pointsBody [i].x * -sin(a);

					punto.x = x;
					punto.y = pointsBody [i].y;
					punto.z = z;

					x = normales [i].x * cos(a);
					z = normales [i].x * -sin(a);
					normal.x = x;
					normal.y = normales [i].y;
					normal.z = z;

					objeto.position = punto;
					objeto.normal = normal;
					posNormBody.push_back(objeto);
					posNorm.push_back(objeto);
				}
			}
			break;
		case PAG_TOP_FAN: //Tapa Arria

			normal.x = 0;
			normal.y = 1;
			normal.z = 0;

			for ( int i = 0; i < slices; ++i ) {
				a = i*((2 * glm::radians(180.0)) / slices);
				x = pointsTopFan [0].x * cos(a);
				z = pointsTopFan [0].x * -sin(a);
				punto.x = x;
				punto.y = pointsTopFan [0].y;
				punto.z = z;

				objeto.position = punto;
				objeto.normal = normal;
				posNormTopFan.push_back(objeto);
				posNorm.push_back(objeto);
			}

			punto.x = points [1].x;
			punto.y = points [1].y;
			punto.z = 0;

			objeto.position = punto;
			objeto.normal = normal;
			posNormTopFan.push_back(objeto);
			posNorm.push_back(objeto);

			break;
		case PAG_BOTTOM_FAN: //Tapa Abajo

			normal.x = 0;
			normal.y = -1;
			normal.z = 0;

			punto.x = pointsBottomFan [0].x;
			punto.y = pointsBottomFan [0].y;
			punto.z = 0;

			objeto.position = punto;
			objeto.normal = normal;
			posNormBottomFan.push_back(objeto);
			posNorm.push_back(objeto);
			for ( int i = 0; i < slices; ++i ) {
				a = i*((2 * glm::radians(180.0)) / slices);
				x = pointsBottomFan [1].x * cos(a);
				z = pointsBottomFan [1].x * -sin(a);
				punto.x = x;
				punto.y = pointsBottomFan [1].y;
				punto.z = z;

				objeto.position = punto;
				objeto.normal = normal;
				posNormBottomFan.push_back(objeto);
				posNorm.push_back(objeto);
			}

			break;
		}

	}
}

void PagRevolutionObject::uso(){
	perfilOriginal->clean();
	perfilSubdividido = perfilOriginal->subdivide(subdivisions);

	perfilSubdividido.clean();
	perfilSubdividido.mostrarPerfil();
	perfilSubdividido.calculoNormales();

	normales = perfilSubdividido.getNormales();
	points= perfilSubdividido.getPuntos();

}

void PagRevolutionObject::calculoTangentes(PagRevObjParts part){

	int a = 0;
	glm::vec3 tangente;
	tangente.y = 0;
	int tam = points.size();
	switch ( part )
	{
	case PAG_BODY:

		for ( int j = 0; j < slices; ++j ) {
			for ( int i = 0; i < pointsBody.size(); ++i ) {
				a = j*((2 * glm::radians(180.0)) / slices);
				tangente.x = -sin(a);
				tangente.z = -cos(a);
				glm::normalize(tangente);
				tangentes.push_back(tangente);
			}
		}

		break;
	case PAG_TOP_FAN:
		glm::vec3 zPos (0, 0, 1);
		
		for ( int j = 0; j < slices;++j ) {
			tangentes.push_back(glm::normalize(posNormTopFan[0].normal * zPos));
		}
		tangentes.push_back(glm::normalize(posNormTopFan [1].normal * zPos));
		break;
	case PAG_BOTTOM_FAN:
		glm::vec3 zNeg(0, 0, -1);
		tangentes.push_back(glm::normalize(posNormTopFan [0].normal * zPos));
		for ( int i = 0; i < slices; ++i ) {
			tangentes.push_back(glm::normalize(posNormBottomFan [1].normal * zNeg));
		}

		break;
	}
}

void PagRevolutionObject::calculoTexturas(PagRevObjParts part){
	int tam = points.size();
	std::vector<float> v;
	glm::vec2 pTexture;
	float sum = 0;
	float sum2 = 0;
	switch ( part )
	{
	case PAG_BODY:
		
		v = perfilSubdividido.getCoordVTexturas();
		
		for ( int i = 0; i < v.size(); ++i ) {
			sum += v [i];
		}
		
		for ( int s = 0; s < slices; s++ ) {
			sum2 = 0;
			for ( int i = 0; i < pointsBody.size(); ++i ) {
				sum2 += v [i+2];
				pTexture.x = s / slices;
				pTexture.y = sum2 / sum;
				texturas.push_back(pTexture);
			}
		}
		break;
	case PAG_TOP_FAN:
		break;
	case PAG_BOTTOM_FAN:
		break;
	}
}

void PagRevolutionObject::indicesMallaTriangulos(PagRevObjParts part)
{

	int tam = points.size();
	switch ( part )
	{
	case PAG_BODY:

		for ( int s = 0; s < slices; ++s ) {
			for ( int i = 0; i < tam; ++i ) {
				indicesMalla.push_back((i*(slices + 1)) + s);
				indicesMalla.push_back((i*(slices + 1)) + (s + 1));
			}
			indicesMalla.push_back(0xFFFF);
		}

		break;
	case PAG_TOP_FAN: //Tapa arriba

		for ( int s = 0; s < slices; ++s ) {
			for ( int i = 0; i < tam; ++i ) {
				indicesMalla.push_back((i*(slices + 1)) + s);
				indicesMalla.push_back((i*(slices + 1)) + (s + 1));
			}
			indicesMalla.push_back(0xFFFF);
		}

		break;
	case PAG_BOTTOM_FAN: //Tapa abajo

		for ( int s = 0; s < slices; ++s ) {
			for ( int i = 0; i < tam; ++i ) {
				indicesMalla.push_back((i*(slices + 1)) + s);
				indicesMalla.push_back((i*(slices + 1)) + (s + 1));
			}
			indicesMalla.push_back(0xFFFF);
		}

		break;
	}
}

void PagRevolutionObject::indicesNubePuntos(PagRevObjParts part)
{

	int tam = points.size();
	switch ( part )
	{
	case PAG_BODY:

		for ( int i = 0; i < slices*tam; ++i ) {
			indicesNube.push_back(i);
		}
		indicesNube.push_back(0xFFFF);

		break;
	case PAG_TOP_FAN:

		for ( int i = 0; i < slices*tam; ++i ) {
			indicesNube.push_back(i);
		}
		indicesNube.push_back(0xFFFF);

		break;
	case PAG_BOTTOM_FAN:

		for ( int i = 0; i < slices*tam; ++i ) {
			indicesNube.push_back(i);
		}
		indicesNube.push_back(0xFFFF);

		break;
	}
}

void PagRevolutionObject::separate(){
	if(perfilSubdividido.has(PAG_BOTTOM_FAN) ){
		pointsBottomFan.push_back(points [0]);
		pointsBottomFan.push_back(points [1]);
	}
	if ( perfilSubdividido.has(PAG_TOP_FAN) ) {
		pointsTopFan.push_back(points [points.size() - 2]);
		pointsTopFan.push_back(points [points.size() - 1]);
	}
	if ( perfilSubdividido.has(PAG_BODY) ) {
		for ( int i = 2; i < points.size() - 2; i++ ) {
			pointsBody.push_back(points [i]);
		}
	}
}
