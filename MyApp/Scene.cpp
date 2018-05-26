#include "Scene.h"
//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST); 
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);//De la 1.3
  
  camera->setAZ();
    
  // lights
  // textures  

  // objets
  objetos.push_back(new EjesRGB(200.0));
  //objetos.push_back(new Triangulo(100.0));
  //objetos.push_back(new TrianguloRGB(100.0));
  //objetos.push_back(new TriPyramid(100.0,100.0));
  //objetos.push_back(new ContCubo(100.0));
  //El diabolo usa la funcion render en el display() del main que esta comentada, hay que descomentar para que renderice
	//el diabolo declarado como variable local tambien en el main
  //objetos.push_back(new Diabolo(100.0,200.0));
  //objetos.push_back(new Rectangulo(200.0, 100.0));
  //objetos.push_back(new Cubo(100.0));//OJO este es el cubo con tapa, el cubo normal es contcubo
  //objetos.push_back(new RectanguloTex(200.0, 100.0, 1.0, 1.0));
  //objetos.push_back(new CuboTex(300.0));
  //objetos.push_back(new PyramidTex(200.0,200.0));
  //objetos.push_back(new DiaboloTex(50.0, 100.0));
  //objetos.push_back(new SueloTex(600.0, 600.0, 1.0, 1.0));
  //objetos.push_back(new GlassPot(100.0));
  //objetos.push_back(new Grass(50.0, 50.0, 0.0, 0.0));
  
  //PRACTICA 2
  glClearColor(0.6f, 0.7f, 0.8f, 1.0); // Fondo azul (o el que prefieras)
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0); // Light0
  GLfloat d[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
  GLfloat a[] = { 0.3f, 0.3f, 0.3f, 1.0f };
  glLightfv(GL_LIGHT0, GL_AMBIENT, a);
  GLfloat s[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glLightfv(GL_LIGHT0, GL_SPECULAR, s);
 // GLfloat p[] = { 50.0f, 50.0f, 50.0f, 1.0f };
  //glLightfv(GL_LIGHT0, GL_POSITION, p);
  camera->set3D();

  //objetos.push_back(new MPR(40));
  objetos.push_back(new Hipotrocoide(6,200,7.0,4.0,2.0));
  
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources 
  
  for each (Entity* it in objetos)
  {
	  delete it;
  }
}
//-------------------------------------------------------------------------

void Scene::render()
{
	glMatrixMode(GL_MODELVIEW);

	for each (Entity* it in objetos)
	{
		it->render(camera->getViewMat());

	}
  //Descomentar para la parte de los puertos de vista
  /*Viewport* puertoVista = camera->getVP();
  GLsizei oldw = puertoVista->getW();
  GLsizei oldh = puertoVista->getH();
  GLsizei oldx = puertoVista->getX();
  GLsizei oldy = puertoVista->getY();

  puertoVista->setSize(oldw/2, oldh/2);
  puertoVista->setPos(oldx, oldy);
  objetos[1]->render(camera->getViewMat());
  objetos[0]->render(camera->getViewMat());

  puertoVista->setSize(oldw / 2, oldh / 2);
  puertoVista->setPos(oldw/2, 0);
  objetos[2]->render(camera->getViewMat());
  objetos[0]->render(camera->getViewMat());

  puertoVista->setSize(oldw / 2, oldh / 2);
  puertoVista->setPos(0, oldh/2);
  objetos[3]->render(camera->getViewMat());
  objetos[0]->render(camera->getViewMat());

  puertoVista->setSize(oldw / 2, oldh / 2);
  puertoVista->setPos(oldw / 2, oldh / 2);
  objetos[4]->render(camera->getViewMat());
  objetos[0]->render(camera->getViewMat());

  //Restauro valores originales
  puertoVista->setSize(oldw, oldh);
  puertoVista->setPos(oldx, oldy);*/
	
}
//-------------------------------------------------------------------------
