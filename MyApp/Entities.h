//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"
#include <stdio.h>
#include "Texture.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
  Entity() : modelMat(1.0) { };
  virtual ~Entity() { delete mesh; };

  Texture texture;

  virtual void render(glm::dmat4 const& modelViewMat);
  
protected:
  Mesh* mesh = nullptr;
  glm::dmat4 modelMat;
  virtual void draw();
  virtual void setMvM(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
  EjesRGB(GLdouble l);
  ~EjesRGB() { };
  virtual void draw();
};

//-------------------------------------------------------------------------
class Triangulo : public Entity
{
public:
	Triangulo(GLdouble r);
	~Triangulo(){ };
	virtual void draw();

};
//-------------------------------------------------------------------------
class TrianguloRGB : public Entity
{
public:
	TrianguloRGB(GLdouble r);
	~TrianguloRGB(){ };
	virtual void draw();

};
//-------------------------------------------------------------------------
class TriPyramid : public Entity
{
public:
	TriPyramid(GLdouble r, GLdouble h);
	~TriPyramid(){ };
	virtual void draw();

};
//-------------------------------------------------------------------------
class ContCubo : public Entity
{
public:
	ContCubo(GLdouble l);
	~ContCubo(){ };
	virtual void draw();

};
//-------------------------------------------------------------------------

//Ahora para el diabolo, tiene que tener una constructora, que crea una malla con una trypiramid y luego en el render hago 4
class Diabolo : public Entity
{
public:
	GLdouble r;
	GLdouble h;
	GLfloat angulo = 0;
	Diabolo(GLdouble r, GLdouble h);
	~Diabolo(){ };
	//virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void rota();
	GLdouble getR(){ return r; }
	GLdouble getH(){ return h; }

};
//-------------------------------------------------------------------------
class Rectangulo : public Entity
{
public:
	Rectangulo(GLdouble w, GLdouble h);
	~Rectangulo(){ };
	virtual void draw();

};
//-------------------------------------------------------------------------
class Cubo : public Entity
{
public:
	GLdouble l;
	Mesh* mesh1;
	Mesh* mesh2;
	Mesh* mesh3;
	Cubo(GLdouble l);
	~Cubo(){ };
	virtual void render(glm::dmat4 const& modelViewMat);

};
//-------------------------------------------------------------------------
class RectanguloTex : public Entity
{
public:
	Mesh* mesh;
	//Mesh* mesh2;
	RectanguloTex(GLdouble w, GLdouble h, GLdouble n, GLdouble l);
	~RectanguloTex(){ };
	//virtual void render(glm::dmat4 const& modelViewMat);
	virtual void draw();

};
//-------------------------------------------------------------------------
class CuboTex : public Entity
{
public:
	Mesh* mesh;
	//Mesh* mesh2;
	CuboTex(GLdouble l);
	~CuboTex(){ };
	//virtual void render(glm::dmat4 const& modelViewMat);
	virtual void draw();

};
//-------------------------------------------------------------------------
class PyramidTex : public Entity
{
public:
	PyramidTex(GLdouble r, GLdouble h);
	~PyramidTex() { };
	virtual void draw();

};
//-------------------------------------------------------------------------
class SueloTex : public Entity
{
public:
	GLdouble l;
	SueloTex(GLdouble w, GLdouble h, GLdouble n, GLdouble l);
	~SueloTex() { };
	virtual void draw();

};
//-------------------------------------------------------------------------
class GlassPot : public Entity
{
public:
	Mesh * mesh;
	//Mesh* mesh2;
	GlassPot(GLdouble l);
	~GlassPot() { };
	//virtual void render(glm::dmat4 const& modelViewMat);
	virtual void draw();

};
//-------------------------------------------------------------------------
class Grass : public Entity
{
public:
	Grass(GLdouble w, GLdouble h, GLdouble n, GLdouble l);
	Mesh * mesh;
	Mesh* mesh2;
	~Grass() { };
	virtual void draw();

};
//-------------------------------------------------------------------------
class DiaboloTex : public Entity
{
public:
	GLdouble r;
	GLdouble h;
	GLfloat angulo = 0;
	DiaboloTex(GLdouble r, GLdouble h);
	~DiaboloTex() { };
	//virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	//virtual void rota();
	GLdouble getR() { return r; }
	GLdouble getH() { return h; }

};
//-------------------------------------------------------------------------
class MPR : public Entity
{
public:
	MPR(int n);
	Mesh * mesh;//Esta será la malla por revolución
	~MPR() { };
	virtual void draw();

	int m;
	int n;
	glm::dvec3* perfil;

};
//-------------------------------------------------------------------------
class Cono : public Entity
{
public:
	Cono(GLdouble alto, GLdouble ancho);
	Mesh * mesh;//Esta será la malla por revolución
	~Cono() { };
	virtual void draw();

};
//-------------------------------------------------------------------------
class Hipotrocoide : public Entity
{
public:
	int nP;
	int nQ;
	GLfloat a, b, c;

	HipoMesh * mesh;
	Hipotrocoide(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c);
	~Hipotrocoide() {};
    virtual void draw();
	//virtual void draw() { this->draw(); };

	/*MPR(int n);
	Mesh * mesh;//Esta será la malla por revolución
	~MPR() { };
	virtual void draw();

	int m;
	int n;
	glm::dvec3* perfil;*/

};
//-------------------------------------------------------------------------


#endif //_H_Entities_H_