//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

//-------------------------------------------------------------------------

class Mesh 
{
public:
  static Mesh* generateAxesRGB(GLdouble l);
  static Mesh* generateTriangle(GLdouble r);
  static Mesh* generateTriangleRGB(GLdouble r);
  static Mesh* generateTriPyramid(GLdouble r,GLdouble h);
  static Mesh* generateContCubo(GLdouble l);
  static Mesh* generateRectangle(GLdouble w, GLdouble h);
  static Mesh* generateRectangleTex(GLdouble w, GLdouble h, GLdouble n, GLdouble l);
  static Mesh *generateCuboTex(GLdouble l);
  static Mesh* generateTriPyramidTex(GLdouble r, GLdouble h);
  static Mesh* generateSueloTex(GLdouble w, GLdouble h, GLdouble n, GLdouble l);

  //Practica 2
  static Mesh* generaMallaPorRevolucion(int m, int n, glm::dvec3* perfil);
  void normalize(int mm, int nn);
  glm::dvec3* normals;
  glm::dvec3* getNormals() { return normals; };
 
  Mesh(void) { };
  ~Mesh(void);
  virtual void draw();
  glm::dvec3* getVertices() { return vertices; };
  glm::dvec4* getColours() { return colors; };
  glm::dvec2 * getTexCoords() { return texCoords; };
   
protected:
   GLuint numVertices = 0;
   GLuint type = GL_POINTS;
   glm::dvec3* vertices = nullptr;
   glm::dvec4* colors = nullptr;
   glm::dvec2 * texCoords = nullptr;
};

//-------------------------------------------------------------------------
//Hipotrocoide
/*int nP; // Número de lados del polígono que aproxima la circunferencia que define el tubo
int nQ; // Número de rodajas que forman la hipotrocoide
GLfloat a, b, c; // Valores de los parámetros de la ecuación de la hipotrocoide
dmat4 m; // Matriz de paso de coordenadas locales a globales
dvec3* base; // Perfil del nP-ágono que aproxima la circunferencia que define el tubo
static Mesh* hipoMesh(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c, glm::dmat4 m, glm::dvec3* base);*/

class HipoMesh : public Mesh
{
public:
	int nP; // Número de lados del polígono que aproxima la circunferencia que define el tubo
	int nQ; // Número de rodajas que forman la hipotrocoide
	GLfloat a, b, c; // Valores de los parámetros de la ecuación de la hipotrocoide
	glm::dmat4 m; // Matriz de paso de coordenadas locales a globales
	//glm::dvec3* base_old; // Perfil del nP-ágono que aproxima la circunferencia que define el tubo
	glm::dvec3* base;

	HipoMesh(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c);//Constructora
	void creaBase(); // Guarda en base el polígono que aproxima la circunferencia del tubo
	void creaVerticesIniciales(); // Añade los primeros nP vértices
	void creaRodaja(int v); // Añade nP nuevos vértices, a partir de la componente v
	void cargaMatriz(GLdouble t); // Define la matriz m para t
	//Reescribir normalize
	void normalize();

	//Funciones extra
	glm::dvec3 curva(GLdouble t);//Me da la curva segun la ecuacion
	glm::dvec3 derivada(GLdouble t);//La derivada primera de la curva. Vector T
	glm::dvec3 segundaDerivada(GLdouble t);//La segunda derivada. Vector N
	//Variables extra
	int nVertices;
	glm::dvec3* vertices;
	glm::dvec3* getVertices() { return vertices; };
	virtual void draw();

	glm::dvec3* normals;
	glm::dvec3* getNormals() { return normals; };

};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_