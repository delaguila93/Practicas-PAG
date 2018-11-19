#include "PagRevolutionObject.h"
#include <fstream>



PagRevolutionObject::PagRevolutionObject()
{
}

PagRevolutionObject::PagRevolutionObject(std::vector<glm::vec2> points, unsigned int _subdivisions, unsigned int _slices) :subdivisions(_subdivisions), slices(_slices)
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

void PagRevolutionObject::revolution(PagRevObjParts part) {
	struct PagPosNorm objeto;
	glm::vec3 punto;
	glm::vec3 normal; //Mismo calculo que posiciones
	double a = 0;
	double delta = glm::radians(360.0  / slices);
	if ( has(part) ) {
		switch ( part )
		{
		case PAG_BODY:

			double x, z;
			for ( int i = 0; i < pointsBody.size(); i++ ) {
				for ( int j = 0; j <= slices; j++ ) {

					a = j*delta;
					x = pointsBody [i].x * cos(a);
					z = pointsBody [i].x * -sin(a);

					punto.x = x;
					punto.y = pointsBody [i].y;
					punto.z = z;

					x = normales [i].x * cos(a);
					z = -normales [i].x * sin(a);
					normal.x = x;
					normal.y = normales [i].y;
					normal.z = z;

					objeto.position = punto;
					objeto.normal = normal;
					glm::normalize(normal);
					posNormBody.push_back(objeto);
				}
			}
			break;
		case PAG_TOP_FAN: //Tapa Arria

			normal.x = 0;
			normal.y = 1;
			normal.z = 0;

			for ( int i = 0; i <= slices; i++ ) {
				a = i*delta;
				x = pointsTopFan [0].x * cos(a);
				z = pointsTopFan [0].x * -sin(a);
				punto.x = x;
				punto.y = pointsTopFan [0].y;
				punto.z = z;
				glm::normalize(normal);
				objeto.position = punto;
				objeto.normal = normal;
				posNormTopFan.push_back(objeto);
			}

			punto.x = 0;
			punto.y = pointsTopFan [1].y;
			punto.z = 0;


			objeto.position = punto;
			objeto.normal = normal;
			posNormTopFan.push_back(objeto);
			break;
		case PAG_BOTTOM_FAN: //Tapa Abajo

			normal.x = 0;
			normal.y = -1;
			normal.z = 0;

			punto.x = 0;
			punto.y = pointsBottomFan [0].y;
			punto.z = 0;

			glm::normalize(normal);

			objeto.position = punto;
			objeto.normal = normal;
			posNormBottomFan.push_back(objeto);

			for ( int i = 0; i <= slices; i++ ) {
				a = i*delta;
				x = pointsBottomFan [1].x * cos(a);
				z = pointsBottomFan [1].x * -sin(a);
				punto.x = x;
				punto.y = pointsBottomFan [1].y;
				punto.z = z;
				glm::normalize(normal);
				objeto.position = punto;
				objeto.normal = normal;
				posNormBottomFan.push_back(objeto);

			}

			break;
		}

	}
}

void PagRevolutionObject::calculoTangentes(PagRevObjParts part) {

	int a = 0;
	glm::vec3 tangente;
	tangente.y = 0;
	int tam = points.size();
	switch ( part )
	{
	case PAG_BODY:

		for ( int j = 0; j <= slices; ++j ) {
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
		glm::vec3 zPos(0, 0, 1);
		for ( int j = 0; j <= slices; ++j ) {
			tangentes.push_back(glm::normalize(posNormTopFan [0].normal * zPos));
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

void PagRevolutionObject::calculoTexturas(PagRevObjParts part) {
	int tam = points.size();
	std::vector<float> v;
	glm::vec2 pTexture;
	float sum = 0;
	float sum2 = 0;
	int a = -1;
	switch ( part )
	{
	case PAG_BODY:

		v = perfilSubdividido.getCoordVTexturas();
		for ( int i = 0; i < v.size(); ++i ) {
			sum += v [i];
		}
		for ( int s = 0; s <= slices; s++ ) {
			sum2 = 0;
			for ( int i = 0; i < pointsBody.size(); ++i ) {
				sum2 += v [i + 2];
				pTexture.x = s / slices;
				pTexture.y = sum2 / sum;
				texturas.push_back(pTexture);
			}
		}
		break;
	case PAG_TOP_FAN:
		for ( int i = 0; i <= slices; ++i ) {
			a = i*((2 * glm::radians(180.0)) / slices);
			pTexture.x = (cos(a) / 2) + 0.5;
			pTexture.y = (sin(a) / 2) + 0.5;
			texturas.push_back(pTexture);
		}
		pTexture.x = 0.5;
		pTexture.y = 0.5;
		texturas.push_back(pTexture);
		break;
	case PAG_BOTTOM_FAN:
		pTexture.x = 0.5;
		pTexture.y = 0.5;
		texturas.push_back(pTexture);
		for ( int i = 0; i <= slices; ++i ) {
			a = i*((2 * glm::radians(180.0)) / slices);
			pTexture.x = (cos(a) / 2) + 0.5;
			pTexture.y = (sin(a) / 2) + 0.5;
			texturas.push_back(pTexture);
		}
		break;
	}
}

void PagRevolutionObject::indicesMallaTriangulos(PagRevObjParts part)
{

	switch ( part )
	{
	case PAG_BODY:

		for ( int s = 0; s < slices; s++ ) {
			for ( int i = 0; i < posNormBody.size(); i++ ) {
				indicesMallaBody.push_back((i*(slices + 1)) + s);
				indicesMallaBody.push_back((i*(slices + 1)) + (s + 1));
			}
			indicesMallaBody.push_back(0xFFFFFFFF);
		}

		break;
	case PAG_TOP_FAN: //Tapa arriba
		indicesMallaTopFan.push_back(slices + 1);

		for ( int s = 0; s <= slices; ++s ) {
			indicesMallaTopFan.push_back(s);
		}
		
		break;
	case PAG_BOTTOM_FAN: //Tapa abajo
		indicesMallaBottomFan.push_back(0);
		for ( int s = 0; s <= slices; ++s ) {
			indicesMallaBottomFan.push_back(s+1);
		}
		
		break;
	}
}

void PagRevolutionObject::indicesNubePuntos(PagRevObjParts part)
{

	switch ( part )
	{
	case PAG_BODY:

		for ( int i = 0; i < posNormBody.size(); i++ ) {
			indicesNubeBody.push_back(i);
		}
		//indicesNubeBody.push_back(0xFFFFFFFF);

		break;
	case PAG_TOP_FAN:

		for ( int i = 0; i < posNormTopFan.size(); i++ ) {
			indicesNubeTopFan.push_back(i);
		}
		//indicesNubeTopFan.push_back(0xFFFFFFFF);

		break;
	case PAG_BOTTOM_FAN:

		for ( int i = 0; i < posNormBottomFan.size(); i++ ) {
			indicesNubeBottomFan.push_back(i);
		}
		//indicesNubeBottomFan.push_back(0xFFFFFFFF);

		break;
	}
}

void PagRevolutionObject::indicesLineas(PagRevObjParts part)
{
	switch ( part )
	{
	case PAG_BODY:

		for ( int i = 0; i < posNormBody.size(); i++ ) {
			for ( int s = 0; s <= slices; s++ ) {
				indicesLineBody.push_back((i*(slices + 1)) + s);
				//indicesLineBody.push_back((i*(slices + 1)) + (s + 1));
				
			}
			indicesLineBody.push_back(0xFFFFFFFF);
		}

		for ( int s = 0; s < slices; s++ ) {
			for ( int i = 0; i <= posNormBody.size(); i++ ) {
				indicesLineBody.push_back((i*(slices + 1)) + s);
				//indicesLineBody.push_back((i*(slices + 1)) + (s + 1));
			}
			indicesLineBody.push_back(0xFFFFFFFF);
		}
		break;
	case PAG_TOP_FAN:
		for ( int s = 0; s < slices; s++ ) {
			for ( int i = 0; i < posNormTopFan.size(); i++ ) {
				indicesLineTopFan.push_back((i*(slices + 1)) + s);
			}
			indicesLineTopFan.push_back(0xFFFFFFFF);
		}
		for ( int i = 0; i < posNormTopFan.size(); i++ ) {
			for ( int s = 0; s <= slices; s++ ) {
				indicesLineTopFan.push_back((i*(slices + 1)) + s);
			}
			indicesLineTopFan.push_back(0xFFFFFFFF);
		}
		break;
	case PAG_BOTTOM_FAN:

		for ( int i = 0; i < posNormBottomFan.size(); i++ ) {
			for ( int s = 0; s <= slices; s++ ) {
				indicesLineBottomFan.push_back((i*(slices + 1)) + s);
			}
			indicesLineBottomFan.push_back(0xFFFFFFFF);
		}

		for ( int s = 0; s <= slices; s++ ) {
			for ( int i = 0; i < posNormBottomFan.size(); i++ ) {
				indicesLineBottomFan.push_back((i*(slices + 1)) + s);
			}
			indicesLineBottomFan.push_back(0xFFFFFFFF);
		}
		break;
	}
}

void PagRevolutionObject::separate() {
	if ( perfilSubdividido.has(PAG_BOTTOM_FAN) ) {
		pointsBottomFan.push_back(points [0]);
		pointsBottomFan.push_back(points [1]);
	}
	if ( perfilSubdividido.has(PAG_TOP_FAN) ) {
		pointsTopFan.push_back(points [points.size() - 2]);
		pointsTopFan.push_back(points [points.size() - 1 ]);
	}
	if ( perfilSubdividido.has(PAG_BODY) ) {
		for ( int i = 1; i <= points.size() - 2; i++ ) {
			pointsBody.push_back(points [i]);
		}
	}
}

void PagRevolutionObject::drawAsPoints(PagRevObjParts part) {

	switch ( part )
	{
	case PAG_BODY:
		vaoCuerpo.dibujar(indicesNubeBody, PUNTOS);
		break;
	case PAG_BOTTOM_FAN:
		vaoTapaAbajo.dibujar(indicesNubeBottomFan, PUNTOS);
		break;
	case PAG_TOP_FAN:
		vaoTapaArriba.dibujar(indicesNubeTopFan, PUNTOS);
		break;

	}
}

void PagRevolutionObject::drawAsTriangles(PagRevObjParts part)
{
	switch ( part )
	{
	case PAG_BODY:
		vaoCuerpo.dibujar(indicesMallaBody, MALLA);
		break;
	case PAG_BOTTOM_FAN:
		vaoTapaAbajo.dibujarTapa(indicesMallaBottomFan);
		break;
	case PAG_TOP_FAN:
		vaoTapaArriba.dibujarTapa(indicesMallaTopFan);
		break;

	}
}

void PagRevolutionObject::drawAsLines(PagRevObjParts part)
{
	switch ( part )
	{
	case PAG_BODY:
		vaoCuerpo.dibujar(indicesLineBody, LINEAS);
		break;
	case PAG_TOP_FAN:
		vaoTapaArriba.dibujar(indicesLineTopFan, LINEAS);
		break;
	case PAG_BOTTOM_FAN:
		vaoTapaAbajo.dibujar(indicesLineBottomFan, LINEAS);
		break;
	}
}

void PagRevolutionObject::escribirFichero(PagRevObjParts part)
{
	std::ofstream file("myfile.txt");
	switch ( part )
	{
	case PAG_BODY:
		for ( PagPosNorm vert : posNormBody )
		{
			file << vert.position.x << " " << vert.position.y << " " << vert.position.z << " "
				<< vert.normal.x << " " << vert.normal.y << " " << vert.normal.z << std::endl;
		}
		break;
	case PAG_TOP_FAN:
		break;
	case PAG_BOTTOM_FAN:
		break;
	}

}

void PagRevolutionObject::rellenarVBO(PagRevObjParts part) {
	switch ( part )
	{
	case PAG_BODY:
		vaoCuerpo.rellenarVBO(posNormBody,POSNORM);
		break;
	case PAG_BOTTOM_FAN:
		vaoTapaAbajo.rellenarVBO(posNormBottomFan, POSNORM);
		break;
	case PAG_TOP_FAN:
		vaoTapaArriba.rellenarVBO(posNormTopFan, POSNORM);
		break;
	}

}

void PagRevolutionObject::rellenarIBO(PagRevObjParts part) {

	switch ( part )
	{
	case PAG_BODY:
		vaoCuerpo.rellenarIBO(indicesNubeBody, PUNTOS);
		vaoCuerpo.rellenarIBO(indicesMallaBody, MALLA);
		vaoCuerpo.rellenarIBO(indicesLineBody, LINEAS);
		break;
	case PAG_TOP_FAN:
		vaoTapaArriba.rellenarIBO(indicesNubeTopFan, PUNTOS);
		vaoTapaArriba.rellenarIBO(indicesLineTopFan, LINEAS);
		vaoTapaArriba.rellenarIBO(indicesMallaTopFan, TAPAMALLA);
		break;
	case PAG_BOTTOM_FAN:
		vaoTapaAbajo.rellenarIBO(indicesNubeBottomFan, PUNTOS);
		vaoTapaAbajo.rellenarIBO(indicesLineBottomFan, LINEAS);
		vaoTapaAbajo.rellenarIBO(indicesMallaBottomFan, TAPAMALLA);
		break;
	}
}

void PagRevolutionObject::uso() {
	perfilOriginal->clean();
	perfilSubdividido = perfilOriginal->subdivide(subdivisions);

	perfilSubdividido.clean();
	perfilSubdividido.calculoNormales();

	normales = perfilSubdividido.getNormales();
	points = perfilSubdividido.getPuntos();

}
