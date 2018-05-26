#define _USE_MATH_DEFINES
#include "Mesh.h"
#include <stdio.h>

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
  delete[] vertices;
  delete[] colors;
}
//-------------------------------------------------------------------------

void Mesh::draw() 
{
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate 
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate 
    }
	if (texCoords != nullptr){
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
	}
	
    glDrawArrays(type, 0, numVertices);   // kind of primitives, first, count

	  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::generateAxesRGB(GLdouble l)
{
  Mesh* m = new Mesh();
  m->type = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m; 
}
//-------------------------------------------------------------------------
Mesh *Mesh::generateTriangle(GLdouble r)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLES;
	m->numVertices = 3;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(r*cos(radians(0.0)), r*sin(radians(0.0)), 0.0);
	m->vertices[1] = dvec3(r*cos(radians(120.0)), r*sin(radians(120.0)), 0);
	m->vertices[2] = dvec3(r*cos(radians(240.0)), r*sin(radians(240.0)), 0.0);

	//Los colores van en triangulorgb no en este
	/*m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);*/

	return m;
}
//-------------------------------------------------------------------------
Mesh *Mesh::generateTriangleRGB(GLdouble r)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLES;
	m->numVertices = 3;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(r*cos(radians(90.0)), r*sin(radians(90.0)), 0.0);
	m->vertices[1] = dvec3(r*cos(radians(210.0)), r*sin(radians(210.0)), 0);
	m->vertices[2] = dvec3(r*cos(radians(330.0)), r*sin(radians(330.0)), 0.0);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}
//-------------------------------------------------------------------------
Mesh *Mesh::generateTriPyramid(GLdouble r, GLdouble h)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_FAN;
	m->numVertices = 5;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(0.0,0.0, h);
	m->vertices[1] = dvec3(r*cos(radians(0.0)), r*sin(radians(0.0)), 0.0);
	m->vertices[2] = dvec3(r*cos(radians(120.0)), r*sin(radians(120.0)), 0.0);
	m->vertices[3] = dvec3(r*cos(radians(240.0)), r*sin(radians(240.0)), 0.0);
	m->vertices[4] = m->vertices[1];
	//m->vertices[5] = dvec3(, 0.0, 0.0);
	//m->vertices[6] = dvec3(, 0.0, 0.0);

	/*m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);*/

	return m;
}
//-------------------------------------------------------------------------
Mesh *Mesh::generateContCubo(GLdouble l)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	m->numVertices = 10;

	m->vertices = new dvec3[m->numVertices];

	/*m->vertices[0] = dvec3(-l/2, -l/2, l/2);
	m->vertices[1] = dvec3(-l/2, l/2, l/2);
	m->vertices[2] = dvec3(l / 2, -l / 2, l / 2);
	m->vertices[3] = dvec3(l / 2, l / 2, l / 2);
	m->vertices[4] = dvec3(l / 2, -l / 2, -l / 2);
	m->vertices[5] = dvec3(l / 2, l / 2, -l / 2);
	m->vertices[6] = dvec3(-l / 2, -l / 2, -l / 2);
	m->vertices[7] = dvec3(-l / 2, l / 2, -l / 2);
	m->vertices[8] = dvec3(-l / 2, -l / 2, l / 2);
	m->vertices[9] = dvec3(-l / 2, l / 2, l / 2);*/

	m->vertices[0] = dvec3(-l / 2, l / 2, l / 2);
	m->vertices[1] = dvec3(-l / 2, -l / 2, l / 2);
	m->vertices[2] = dvec3(l / 2, l / 2, l / 2);
	m->vertices[3] = dvec3(l / 2, -l / 2, l / 2);
	m->vertices[4] = dvec3(l / 2, l / 2, -l / 2);
	m->vertices[5] = dvec3(l / 2, -l / 2, -l / 2);
	m->vertices[6] = dvec3(-l / 2, l / 2, -l / 2);
	m->vertices[7] = dvec3(-l / 2, -l / 2, -l / 2);
	m->vertices[8] = dvec3(-l / 2, l / 2, l / 2);
	m->vertices[9] = dvec3(-l / 2, -l / 2, l / 2);

	return m;
}
//-------------------------------------------------------------------------
Mesh *Mesh::generateRectangle(GLdouble w,GLdouble h)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	m->numVertices = 4;

	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(-w/2, h/2, 0);
	m->vertices[1] = dvec3(-w/2, -h/2, 0);
	m->vertices[2] = dvec3(w/2, h/2 , 0);
	m->vertices[3] = dvec3(w/2, -h/2, 0);

	return m;
}
//-------------------------------------------------------------------------
Mesh *Mesh::generateRectangleTex(GLdouble w, GLdouble h, GLdouble n, GLdouble l)
{
	//Lo que pone de las variables en el enunciado, es para que la textura se repita en base a ese numero, que se sustituyen los 1s de texcoords por ese numero (a lo mejor es algo mas complejo)
	
	Mesh *m = generateRectangle(w, h);
	m->texCoords = new dvec2[m->numVertices];
	/*m->texCoords[0] = dvec2(0, n);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(l, n);
	m->texCoords[3] = dvec2(l, 0);*/

	//OJO ahora mismo con n=l=0, no aparece toda la textura cubriendo el triangulo, eso es con n=l=1. Preguntarlo
	m->texCoords[0] = dvec2(0, n+1);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(l+1, n+1);
	m->texCoords[3] = dvec2(l+1, 0);

	return m;

}
//-------------------------------------------------------------------------
Mesh *Mesh::generateCuboTex(GLdouble l)
{
	//Hay que cambiar el contcubo, que tiene los vertices al reves, y me pone la textura boca abajo. Hecho.

	Mesh *m = generateContCubo(l);
	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(0, 1);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(1, 1);
	m->texCoords[3] = dvec2(1, 0);

	m->texCoords[4] = dvec2(2, 1);
	m->texCoords[5] = dvec2(2, 0);
	m->texCoords[6] = dvec2(3, 1);
	m->texCoords[7] = dvec2(3, 0);
	m->texCoords[8] = dvec2(4, 1);
	m->texCoords[9] = dvec2(4, 0);
	return m;

}
//-------------------------------------------------------------------------
Mesh *Mesh::generateTriPyramidTex(GLdouble r, GLdouble h)
{
	//Hay que cambiar el contcubo, que tiene los vertices al reves, y me pone la textura boca abajo. Hecho.

	Mesh *m = generateTriPyramid(r,h);

	/*m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(0.0,0.0, h);
	m->vertices[1] = dvec3(r*cos(radians(0.0)), r*sin(radians(0.0)), 0.0);
	m->vertices[2] = dvec3(r*cos(radians(120.0)), r*sin(radians(120.0)), 0.0);
	m->vertices[3] = dvec3(r*cos(radians(240.0)), r*sin(radians(240.0)), 0.0);
	m->vertices[4] = m->vertices[1];*/
	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(0, 1);
	m->texCoords[1] = dvec2(1, 0);
	m->texCoords[2] = dvec2(1, 1.0/3.0);
	m->texCoords[3] = dvec2(1, 2.0/3.0);
	m->texCoords[4] = dvec2(1, 1);
	return m;

}
//-------------------------------------------------------------------------
Mesh *Mesh::generateSueloTex(GLdouble w, GLdouble h, GLdouble n, GLdouble l)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	m->numVertices = 4;

	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(-w / 2,0, h / 2);
	m->vertices[1] = dvec3(-w / 2,0, -h / 2);
	m->vertices[2] = dvec3(w / 2,0, h / 2);
	m->vertices[3] = dvec3(w / 2,0, -h / 2);

	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(0, n + 1);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(l + 1, n + 1);
	m->texCoords[3] = dvec2(l + 1, 0);

	return m;
}
//-------------------------------------------------------------------------
//PRAC 2
Mesh* Mesh::generaMallaPorRevolucion(int m, int n, dvec3* perfil) {
	Mesh* mesh = new Mesh();
	mesh->numVertices = n * m;
	mesh->vertices = new dvec3[mesh->numVertices];
	GLdouble PI = 3.141592;

	// Vertices de la malla
	for (int i = 0; i < n; i++) { // Generar el perfil i-ésimo
		double theta = i * 2 * PI / n;
		double c = cos(theta);
		double s = sin(theta);
		// R_y es la matriz de rotación sobre el eje Y
		for (int j = 0; j < m; j++) {
			int indice = i * m + j;
			// Transformar el punto j-ésimo del perfil original
			double x = c * perfil[j][0] + s * perfil[j][2];
			double z = -s * perfil[j][0] + c * perfil[j][2];
			//dvec3 p = dvec3(x, perfil[j]->y, z, 1);//Linea de los apuntes que da error
			dvec3 p = dvec3(x, perfil[j].y, z);
			//vertice[indice] = p;//Linea de los apuntes que da error
			mesh->vertices[indice] = p;
		}
	}
	//mesh->normalize(3,40);
	return mesh;
}
//-------------------------------------------------------------------------
void Mesh::normalize(int mm, int nn)
{
	int numVertices = mm;//Puntos del perfil
	//nn es el numero de copias (revoluciones)
	//glm::dvec3* normals = new dvec3[numVertices];
	this->normals = new dvec3[numVertices];
	// Se ponen al vector nulo todas las componentes de normals
	/*normals[0] = dvec3(0.0, 0.0, 0.0);
	normals[1] = dvec3(0.0, 0.0, 0.0);
	normals[2] = dvec3(0.0, 0.0, 0.0);*/
	/*for (int i = 0; i < nn; i++)
		for (int j = 0; j < mm - 1; j++) {
			int indice = i * mm + j;
			int i0 = i * mm + j;
			int i1 = (indice + mm) % (nn*mm);
			int i2 = (indice + mm + 1) % (nn*mm);
			//int i3 = indice + 1;
			normals[i0]= dvec3(0.0, 0.0, 0.0);
			normals[i1]= dvec3(0.0, 0.0, 0.0);
			normals[i2]= dvec3(0.0, 0.0, 0.0);
		}*/
	for (int i = 0; i < nn; i++)
		for (int j = 0; j < mm - 1; j++) {
			int indice = i * mm + j;
			int i0 = indice;//i * mm + j;
			int i1 = (indice + mm) % (nn*mm);
			int i2 = (indice + mm + 1) % (nn*mm);
			//int i3 = indice + 1;
			// Por cada cara a la que pertenece el vértice índice,
			// se determinan 3 índices i0, i1, i2 de 3 vértices consecutivos de esa cara
			dvec3 aux0 = dvec3(0, 0, 0); //vértice de i0; dvec3 aux1 = ...; dvec3 aux2 = ...;
			dvec3 aux1 = dvec3(100, 0, 0);
			dvec3 aux2 = dvec3(0, 200, 0);
			glm::dvec3 norm = glm::cross(aux1 - aux0, aux2 - aux0);
			//normals[i0] += norm; normals[i1] += norm;
			//normals[i2] += norm; normals[...] += norm;
			/*normals[indice] += norm;
			normals[indice+1] += norm;
			normals[indice+2] += norm;*/
			normals[i0] += norm;
			normals[i1] += norm;
			normals[i2] += norm;
		}
	//Se normalizan todos los vectores normales
	normals[0] = glm::normalize(normals[0]);
	normals[1] = glm::normalize(normals[1]);
	normals[2] = glm::normalize(normals[2]);
}
//-------------------------------------------------------------------------
HipoMesh::HipoMesh(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c) {
	this->nP = nP;
	this->nQ = nQ;
	this->a = a;
	this->b = b;
	this->c = c;
    m = dmat4();
	this->nVertices = (nP * nQ) + (2*nP);
	vertices = new dvec3[nVertices];
	creaBase();
	GLdouble t = 0.0;
	cargaMatriz(t);
	creaVerticesIniciales();
	GLdouble saltoEntreRodajas = (8*M_PI)/nQ;
	for (int i = 0; i < nQ; i++) {
		t += saltoEntreRodajas;
		cargaMatriz(t);
		creaRodaja(i*nP);
	}
}
//-------------------------------------------------------------------------
dvec3 HipoMesh::curva(GLdouble t) {
	//printf("curva queda: %.10f,%.10f,%.10f\n", ((a - b)*cos(t)) + (c*cos(((a - b) / b)*t)), 0, ((a - b)*sin(t)) - (c*sin(((a - b) / b)*t)));
	return dvec3(((a - b)*cos(t)) + (c*cos(((a - b) / b)*t)), 0, ((a - b)*sin(t)) - (c*sin(((a - b) / b)*t)));
}
//-------------------------------------------------------------------------
dvec3 HipoMesh::derivada(GLdouble t) {
	/*printf("derivo y queda: %f,%f,%f\n", -(a - b)*sin(t) - c * ((a - b) / b) * sin(t*((a - b) / b)),
		0,
		(a - b)*cos(t) - c * ((a - b) / b)*cos(t*((a - b) / b)));
	printf("cos de t (%f): %f\n",t, cos(t));
	printf("sin de t (%f): %f\n", t, sin(t));*/
	//return dvec3(((b - a)*sin(t)) - (c*((a - b) / b)*sin(((a - b) / b)*t)),0,((a - b)*cos(t)) - (c*((a - b) / b)*cos(((a - b) / b)*t)));
	return dvec3(-(a - b)*sin(t) - c * ((a - b) / b) * sin(t*((a - b) / b)),
		0,
		(a - b)*cos(t) - c * ((a - b) / b)*cos(t*((a - b) / b)));
}
//-------------------------------------------------------------------------
dvec3 HipoMesh::segundaDerivada(GLdouble t) {
	/*return dvec3(((b - a)*cos(t)) - (c*((a - b) / b)*((a - b) / b)*(cos(((a - b) / b)*t))),
		0,
		((b - a)*sin(t)) + (c*((a - b) / b)*((a - b) / b)*(sin(((a - b) / b)*t))));*/
	return dvec3(-(a-b)*cos(t)-c*((a-b)/b)*((a-b)/b)*cos(t*((a-b)/b)),
		0,
		-(a-b)*sin(t)+c*((a-b)/b)*((a-b)/b)*sin(t*((a-b)/b)));
}
//-------------------------------------------------------------------------
void HipoMesh::creaBase() {
	//Creacion del perfil
	double r = 0.5;
	//dvec3 ** perfil = new dvec3*[6];
	base = new dvec3[nP];
	double inc = (2 * (M_PI) / nP);
	for (int i = 0; i < 6; i++) {
		//perfil[i] = new dvec3(r*cos(((double)i)*inc), r*sin(((double)i)*inc), 0);
		base[i] = dvec3(r*cos(((double)i)*inc), r*sin(((double)i)*inc), 0);
		printf("punto %d de la base en: %.10f,%.10f,%.10f\n", i, base[i].x, base[i].y, base[i].z);
	}
	
}
//-------------------------------------------------------------------------
void HipoMesh::cargaMatriz(GLdouble t) {
	dvec3 T = glm::normalize(derivada(t));
	//B = C'xC'' normalizado
	dvec3 B = glm::normalize(glm::cross(derivada(t), segundaDerivada(t)));
	//N = BxT
	dvec3 N = glm::cross(B, T);
	//C = curva
	dvec3 C = curva(t);
	//Meterlos en m que es dvec4(N,B,T,C) con la ultima fila a 0,0,0,1. Matriz de 4x4
	//...
	//m = (N, B, T, C);//opengl accede a la columna en [col][fila]
	//m = dmat4(N.x, N.y, N.z, 0, B.x,B.y,B.z,0,T.x,T.y,T.z, 0, C.x, C.y, C.z,1);
	/*m = dmat4(N[0], N[1], N[2], 0,  // 1. column
		B[0], B[1], B[2], 0,  // 2. column
		T[0], T[1], T[2], 0,  // 3. column
		C[0], C[1], C[2], 1); // 4. column*/
	m[0][0] = N.x; m[1][0] = B.x ; m[2][0] = T.x ; m[3][0] = C.x;
	m[0][1] = N.y; m[1][1] = B.y;  m[2][1] = T.y;  m[3][1] = C.y;
	m[0][2] = N.z; m[1][2] = B.z;  m[2][2] = T.z;  m[3][2] = C.z;
	m[0][3] = 0.0;   m[1][3] =0.0 ;    m[2][3] = 0.0;    m[3][3] = 1.0;
	
}
//-------------------------------------------------------------------------
void HipoMesh::creaVerticesIniciales() {
	//Multiplico la base por la matriz de t=0
	//convierto la base en vec4, para multiplicar bien matriz por vector segun: https://stackoverflow.com/questions/7574125/multiplying-a-matrix-and-a-vector-in-glm-opengl
	//glm:dvec4 aux = (base[i][0])
	/*for (int i = 0; i < 6; i++) {
		GLdouble newX = base[i].x;
		GLdouble newY = base[i].y;
		GLdouble newZ = base[i].z;
		//Multiplico vector por matriz y me da los vertices
		glm::dvec4 aux = dvec4(newX, newY, newZ, 1.0) * m;
		//glm::dvec4 aux = dvec4(newX, newY, newZ, 1.0);
		vertices[i] = dvec3(aux.x, aux.y, aux.z);
		printf("vertices %d: %.10f,%.10f,%.10f\n", i,vertices[i].x, vertices[i].y, vertices[i].z);
	}//*/
	for (int i = 0; i < nP; i++) {
		vertices[i] = dvec3((m[0][0] * base[i].x) + (m[1][0] * base[i].y) + (m[2][0] * base[i].z) + (m[3][0] * 1),
					 (m[0][1] * base[i].x) + (m[1][1] * base[i].y) + (m[2][1] * base[i].z) + (m[3][1] * 1),
					 (m[0][2] * base[i].x) + (m[1][2] * base[i].y) + (m[2][2] * base[i].z) + (m[3][2] * 1)
					 //,(m[0][3] * base[i].x) + (m[1][3] * base[i].y) + (m[2][3] * base[i].z) + (m[3][3] * 1)
				);
		printf("vertice %d: %.10f,%.10f,%.10f\n", i, vertices[i].x, vertices[i].y, vertices[i].z);
	}
}
//-------------------------------------------------------------------------
void HipoMesh::creaRodaja(int v) {//crea todos los vertices
	//Creamos vertices de la rodaja
	for (int i = 0; i < 6; i++) {
        vertices[i+v] = dvec3((m[0][0] * base[i].x) + (m[1][0] * base[i].y) + (m[2][0] * base[i].z) + (m[3][0] * 1),
            (m[0][1] * base[i].x) + (m[1][1] * base[i].y) + (m[2][1] * base[i].z) + (m[3][1] * 1),
            (m[0][2] * base[i].x) + (m[1][2] * base[i].y) + (m[2][2] * base[i].z) + (m[3][2] * 1)
            //,(m[0][3] * base[i].x) + (m[1][3] * base[i].y) + (m[2][3] * base[i].z) + (m[3][3] * 1)
            );
        //printf("vertice %d: %.10f,%.10f,%.10f\n", i, vertices[i].x, vertices[i].y, vertices[i].z);
	}

}
//-------------------------------------------------------------------------
void HipoMesh::draw() {
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3f(0.0, 0.0, 1.0);
	//dvec3* vertices = this->getVertices();
	vertices = this->getVertices();
	normalize();
	normals = this->getNormals();
	//dvec3* normales = this->getNormals();
    if (vertices != nullptr) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, vertices);
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_DOUBLE, 0, normals);

        for (int i = 0; i < nQ; i++){
            for (int j = 0; j < nP - 1; j++){
                int ind = i*nP + j;
                unsigned int stripIndices[] = { ind, ind + 1, ind + nP + 1, ind + nP };
                glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, stripIndices);
            }
            int ind = ((i*nP) + nP) - 1;
            unsigned int stripIndices[] = { ind, ind - (nP - 1), ind + 1, ind + nP };
            glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, stripIndices);
        }
    }
    glDisableClientState(GL_VERTEX_ARRAY);
}
//-------------------------------------------------------------------------
void HipoMesh::normalize() {
	normals = new dvec3[this->nVertices];
	
	for (int i = 0; i < nQ; i++) {
		for (int j = 0; j < nP - 1; j++) {
			int ind = i * nP + j;
			dvec3 aux0 = vertices[ind]; dvec3 aux1 = vertices[ind+1]; dvec3 aux2 = vertices[ind+nP+1];
			glm::dvec3 norm = glm::cross(aux2 - aux1, aux0 - aux1);
			normals[ind] += norm; normals[ind+1] += norm; normals[ind+nP+1] += norm; normals[ind+nP] += norm;
		}
		int ind = ((i*nP) + nP) - 1;
		dvec3 aux0 = vertices[ind]; dvec3 aux1 = vertices[ind - (nP - 1)]; dvec3 aux2 = vertices[ind + 1];
		glm::dvec3 norm = glm::cross(aux2 - aux1, aux0 - aux1);
		normals[ind] += norm; normals[ind - (nP - 1)] += norm; normals[ind + 1] += norm; normals[ind + nP] += norm;
	}
	for (int k = 0; k < nVertices; k++) {
		normals[k] = glm::normalize(normals[k]);
	}
}
//-------------------------------------------------------------------------