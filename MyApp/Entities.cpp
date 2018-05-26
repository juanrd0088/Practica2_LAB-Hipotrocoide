#include "Entities.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::render(dmat4 const& modelViewMat) 
{ 
	setMvM(modelViewMat); 
	draw(); 
}
//-------------------------------------------------------------------------

void Entity::draw() 
{ 
  if (mesh != nullptr) 
    mesh -> draw(); 
}
//-------------------------------------------------------------------------

void Entity::setMvM(dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::generateAxesRGB(l);
}
//-------------------------------------------------------------------------

void EjesRGB::draw()
{
  glLineWidth(2);
  mesh->draw();
  glLineWidth(1);
}
//-------------------------------------------------------------------------
Triangulo::Triangulo(GLdouble r) : Entity()
{
	mesh = Mesh::generateTriangle(r);
}
//-------------------------------------------------------------------------

void Triangulo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	//glcolor falta
	glColor3f(1.0, 0.0, 1.0);
	mesh->draw();
	//glLineWidth(1);
}
//-------------------------------------------------------------------------
TrianguloRGB::TrianguloRGB(GLdouble r) : Entity()
{
	mesh = Mesh::generateTriangleRGB(r);
}
//-------------------------------------------------------------------------

void TrianguloRGB::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//Esto es necesario si genero el triangulo a lineas y este a la vez
	glLineWidth(2);
	//glcolor falta
	//glColor3f(1.0, 0.0, 1.0);
	mesh->draw();
	//glLineWidth(1);
}
//-------------------------------------------------------------------------
TriPyramid::TriPyramid(GLdouble r, GLdouble h) : Entity()
{
	mesh = Mesh::generateTriPyramid(r, h);
}
//-------------------------------------------------------------------------

void TriPyramid::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	//glcolor falta
	glColor3f(1.0, 0.0, 0.0);
	mesh->draw();
	//glLineWidth(1);
}
//-------------------------------------------------------------------------
ContCubo::ContCubo(GLdouble l) : Entity()
{
	mesh = Mesh::generateContCubo(l);
}
//-------------------------------------------------------------------------

void ContCubo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	//glcolor falta
	glColor3f(0.0, 0.0, 0.0);
	mesh->draw();
	//glLineWidth(1);
}
//-------------------------------------------------------------------------
Diabolo::Diabolo(GLdouble r, GLdouble h) : Entity()
{
	this->r = r;
	this->h = h;
	mesh = Mesh::generateTriPyramid(this->r, this->h);
}
//-------------------------------------------------------------------------
void Diabolo::render(glm::dmat4 const& modelViewMat)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);

	glColor3f(1.0, 0.0, 1.0);//rosa
	glTranslatef(0, 0, -h);//-200);
	glRotatef(angulo, 0, 0, 1); 
	mesh->draw();
	glColor3f(1.0, 0.5, 0.5);//naranja
	glRotatef(45, 0, 0, 1);
	glRotatef(angulo, 0, 0, 1);
	mesh->draw();

	glColor3f(0.0, 0.0, 0.0);//negro
	glScalef(1, 1, -1);
	glTranslatef(0, 0, -2 * h);//-400);
	glRotatef(angulo, 0, 0, 1);
	mesh->draw();
	glColor3f(0.5, 1.0, 1.0);//azul
	glRotatef(45, 0, 0, 1);
	glRotatef(angulo, 0, 0, 1);
	mesh->draw();
	//glLineWidth(1);
}
//-------------------------------------------------------------------------
void Diabolo::rota(){
	angulo += 3;
	//Rota pulsando a en el teclado como se indica en el main
}
//-------------------------------------------------------------------------
Rectangulo::Rectangulo(GLdouble w, GLdouble h) : Entity()
{
	mesh = Mesh::generateRectangle(w, h);
}
//-------------------------------------------------------------------------
void Rectangulo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	//glcolor falta
	glColor3f(0.0, 0.0, 0.0);
	mesh->draw();
	//glLineWidth(1);
}
//-------------------------------------------------------------------------
Cubo::Cubo(GLdouble l) : Entity()
{
	this->l = l;
	mesh1 = Mesh::generateCuboTex(l);//Mesh::generateContCubo(l);
	mesh2 = Mesh::generateRectangleTex(l, l, 0, 0);//Mesh::generateRectangle(l,l);
	mesh3 = Mesh::generateRectangleTex(l, l, 0, 0);
}
//-------------------------------------------------------------------------

void Cubo::render(glm::dmat4 const& modelViewMat)
{
	GLdouble l = this->l;
	//glPolygonMode(GL_FRONT, GL_LINE);
	//glPolygonMode(GL_BACK, GL_POINT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(2);
	//glcolor falta
	/*glColor3f(0.0, 0.0, 0.0);
	mesh1->draw();
	glTranslatef(0, 85, -15);//
	glRotatef(45, 1, 0, 0);
	//glRotatef(90, 0, 0, 1);
	mesh2->draw();
	//glLineWidth(1);*/

	//Experimento de pintado distinto externo/interno
	glEnable(GL_CULL_FACE);
	texture.load("..\\Bmps\\emopng.bmp");
	glPushMatrix();
	glCullFace(GL_FRONT);
	glLineWidth(2);
	texture.bind();
	//glcolor falta
	glColor3f(0.0, 0.0, 0.0);
	//glTranslatef(0, 50, 0);//Esta es buena
	glTranslatef(0, 0.5*l, 0);//-l era 0
	mesh1->draw();
	texture.unbind();
	//glDisable(GL_CULL_FACE);

	texture.load("..\\Bmps\\Zelda.bmp");
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glLineWidth(2);
	texture.bind();
	//glcolor falta
	glColor3f(0.0, 0.0, 0.0);
	mesh1->draw();
	//texture.unbind();
	glDisable(GL_CULL_FACE);
	
	//glTranslatef(0, 85, -15);//Esta es buena
	glTranslatef(0, 0.85*l, -0.15*l);//-l era 0
	//glTranslatef(0, 300*0.85, -300*0.15);// Esto es para 300 a pelo, se transalado un 85 y un 15 % respectivamente, pensar en 
	//conseguir meter l aqui.
	glRotatef(45, 1, 0, 0);
	//glRotatef(90, 0, 0, 1);
	mesh2->draw();
	//texture.unbind();

	//Mesh3, el culo del cubo
	//Muevo de nuevo estos valores van perfectos para lado 100 a partir del anterior movimiento
	glRotatef(45, 1, 0, 0); //Se tumba sobre z
	//glTranslatef(0, 15, +135);//Se traslada abajo l. pongo 100 porque aun no he pasado l como parametro.//ESTA ES BUENA
	glTranslatef(0, 0.15*l, +1.35*l);//-l era 0

	//Otra forma
	//glPopMatrix();
	//glPopMatrix();
	//glTranslatef(0, 15, +135);

	glColor3f(0.0, 0.0, 0.0);
	mesh3->draw();
	texture.unbind();
	glPopMatrix();
}
//-------------------------------------------------------------------------
RectanguloTex::RectanguloTex(GLdouble w, GLdouble h, GLdouble n, GLdouble l) : Entity()
{
	mesh = Mesh::generateRectangleTex(w, h, n, l);
	texture.load("..\\Bmps\\Zelda.bmp");
}
//-------------------------------------------------------------------------
void RectanguloTex::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(2);
	texture.bind();
	//glcolor falta
	glColor3f(0.0, 0.0, 0.0);
	mesh->draw();
	texture.unbind();
	//glLineWidth(1);
}
//-------------------------------------------------------------------------
CuboTex::CuboTex(GLdouble l) : Entity()
{
	mesh = Mesh::generateCuboTex(l);
	texture.load("..\\Bmps\\Zelda.bmp");
}
//-------------------------------------------------------------------------
void CuboTex::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(2);
	texture.bind();
	//De la parte 1.3
	//glTranslatef(250.0,50.0,-250.0);//Todo esto deberia estar en la nueva entidad no aqui
	//glcolor falta
	glColor3f(0.0, 0.0, 0.0);
	mesh->draw();
	texture.unbind();
	//glLineWidth(1);
}
//-------------------------------------------------------------------------
PyramidTex::PyramidTex(GLdouble r, GLdouble h) : Entity()
{
	mesh = Mesh::generateTriPyramidTex(r, h);
	texture.load("..\\Bmps\\Zelda.bmp");
}
//-------------------------------------------------------------------------

void PyramidTex::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(2);
	texture.bind();
	//glcolor falta
	glColor3f(1.0, 0.0, 0.0);
	mesh->draw();
	texture.unbind();
	//glLineWidth(1);
}
//-------------------------------------------------------------------------
SueloTex::SueloTex(GLdouble w, GLdouble h, GLdouble n, GLdouble l) : Entity()
{
	mesh = Mesh::generateRectangleTex(w, h, n, l);
	texture.load("..\\Bmps\\baldosaC.bmp");
}
//-------------------------------------------------------------------------
void SueloTex::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(2);
	texture.bind();
	//glcolor falta
	glColor3f(0.0, 0.0, 0.0);
	glRotatef(90, 1, 0, 0); 
	mesh->draw();
	texture.unbind();
	//glLineWidth(1);
}
//-------------------------------------------------------------------------
GlassPot::GlassPot(GLdouble l) : Entity()
{
	mesh = Mesh::generateCuboTex(l);
	texture.load("..\\Bmps\\Window.bmp",100);
}
//-------------------------------------------------------------------------
void GlassPot::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//
	glDepthMask(GL_FALSE);//
	glLineWidth(2);
	texture.bind();
	glPushMatrix();
	glTranslatef(250.0, 50.0, -250.0);//suelo/2 - lado/2, lado/2, -(suelo/2 - lado/2)
	//Hacer un translate con la variable lado del suelo y el ladosuelo que la variable global, para colocar el suelo automaticamente
	glColor3f(0.0, 0.0, 0.0);
	mesh->draw();
	texture.unbind();
	glDepthMask(GL_TRUE);//
	glPopMatrix();
	//glLineWidth(1);
}
//-------------------------------------------------------------------------
Grass::Grass(GLdouble w, GLdouble h, GLdouble n, GLdouble l) : Entity()
{
	mesh = Mesh::generateRectangleTex(w, h, n, l);
	mesh2 = Mesh::generateRectangleTex(w, h, n, l);
	texture.load("..\\Bmps\\Grass.bmp",glm::ivec3(0,0,0),0);
}
//-------------------------------------------------------------------------
void Grass::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(2);
	glPushMatrix();
	texture.bind();
	//glcolor falta
	//glColor3f(0.0, 0.0, 0.0);
	glTranslatef(250.0, 25.0, -250.0);
	glRotatef(45, 0, 1, 0);
	mesh->draw();
	glRotatef(90, 0, 1, 0);
	mesh2->draw();
	texture.unbind();
	glPopMatrix();
	//glLineWidth(1);
}
//-------------------------------------------------------------------------
DiaboloTex::DiaboloTex(GLdouble r, GLdouble h) : Entity()
{
	this->r = r;
	this->h = h;
	texture.load("..\\Bmps\\container2.bmp");
	mesh = Mesh::generateTriPyramidTex(this->r, this->h);
}
//-------------------------------------------------------------------------
void DiaboloTex::render(glm::dmat4 const& modelViewMat)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(2);
	glPushMatrix();
	glColor3f(1.0, 0.0, 1.0);//rosa
	//glTranslatef(0, 0, -h);//-200);
	glTranslatef(2*h, h/2, -h);
	texture.bind();
	glRotatef(angulo, 0, 0, 1);
	mesh->draw();
	glColor3f(1.0, 0.5, 0.5);//naranja
	glRotatef(45, 0, 0, 1);
	glRotatef(angulo, 0, 0, 1);
	mesh->draw();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);//negro
	glScalef(1, 1, -1);
	//glTranslatef(0, 0, -2 * h);//-400);	
	glTranslatef(2 * h, h/2, -h);
	glRotatef(angulo, 0, 0, 1);
	mesh->draw();
	glColor3f(0.5, 1.0, 1.0);//azul
	glRotatef(45, 0, 0, 1);
	glRotatef(angulo, 0, 0, 1);
	mesh->draw();
	texture.unbind();
	glPopMatrix();
	//glLineWidth(1);
}
//-------------------------------------------------------------------------
MPR::MPR(int n) : Entity()
{
	int mm = 3;
	this->m = mm; //número de puntos del perfil
	this->n = n;
	dvec3* perfil = new dvec3[mm];
	perfil[0] = dvec3(0,0,0);
	perfil[1] = dvec3(100, 0, 0);
	perfil[2] = dvec3(0, 200, 0);
	this->mesh = Mesh::generaMallaPorRevolucion(m, n, perfil);
}
//-------------------------------------------------------------------------
void MPR::draw()
{
	glPolygonMode(GL_FRONT, GL_FILL);
	glColor3f(0.0, 0.0, 1.0);
	dvec3* vertices = mesh->getVertices();
	dvec3* normales = mesh->getNormals();//No se si es necesario
	//mesh->normalize(m, n);//ESTO PETA, NO ESTOY INVOCANDO A NORMALIZE PERO ME SALE
	//dvec4* colors = mesh->getColors();
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vertices);
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_DOUBLE, 0, vertices);
	}
		/*if (colors != nullptr) {
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_DOUBLE, 0, colors);
		}*/
		// Después del dibujo de los elementos por índices,
		// se deshabilitan los vertex arrays, como es habitual
		//gldisableClientState ....
		// Definición de las caras
		for (int i = 0; i<n; i++) { // Unir el perfil i-ésimo con el (i+1)%n-ésimo
			for (int j = 0; j<m - 1; j++) { // Esquina inferior-izquierda de una cara
				int indice = i * m + j;
				unsigned int stripIndices[] =
				{ indice, (indice + m) % (n*m),
					(indice + m + 1) % (n*m), indice + 1 };
				glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, stripIndices);
				// o GL_POLYGON, si se quiere las caras con relleno, de serie esta GL_LINE_LOOP
			}
		}
}
//-------------------------------------------------------------------------
Cono::Cono(GLdouble alto, GLdouble ancho) : Entity()
{
	mesh = Mesh::generateRectangle(alto, ancho);
}
//-------------------------------------------------------------------------
void Cono::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	//glcolor falta
	glColor3f(0.0, 0.0, 0.0);
	mesh->draw();
	//glLineWidth(1);
}
//-------------------------------------------------------------------------
Hipotrocoide::Hipotrocoide(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c) : Entity()
{
	/*int mm = 3;
	this->m = mm; //número de puntos del perfil
	this->n = n;
	dvec3* perfil = new dvec3[mm];
	perfil[0] = dvec3(0, 0, 0);
	perfil[1] = dvec3(100, 0, 0);
	perfil[2] = dvec3(0, 200, 0);
	this->mesh = Mesh::generaMallaPorRevolucion(m, n, perfil);*/
	this->nP = nP;
	this->nQ = nQ;
	this->a = a;
	this->b = b;
	this->c = c;
	this->mesh = new HipoMesh(nP, nQ, a, b, c);
	//this->mesh->draw();
}
//-------------------------------------------------------------------------
void Hipotrocoide::draw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glLineWidth(2);
	//glcolor falta
	//glColor3f(0.0, 0.0, 1.0);
	mesh->draw();
	//glLineWidth(1);
}
//-------------------------------------------------------------------------