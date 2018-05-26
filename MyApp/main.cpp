//#include <Windows.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
//#include <GL/glut.h>

#include <GL/freeglut.h>

#include "Camera.h"
#include "Scene.h"

#include "stdio.h"

#include <iostream>
using namespace std;

//---------- Global variables -------------------------------------------------------------

// Viewport position and size
Viewport viewPort(800, 600);   

// Camera position, view volume and projection
Camera camera(&viewPort);    

// Scene entities
Scene scene(&camera);  

//Diabolo
//Diabolo diabolo = Diabolo(100.0, 200.0);

//Raton
glm::dvec2 mCoord;

//Textura para save
Texture textura;

//Lado del suelo (suponiendo que es cuadrado)
//GLdouble ladoSuelo = 600;

//----------- Callbacks ----------------------------------------------------

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);

//-------------------------------------------------------------------------
void mouse(int button, int state, int x, int y) {
	mCoord = mCoord = glm::dvec2(x, (glutGet(GLUT_WINDOW_HEIGHT) - y));
}
//-------------------------------------------------------------------------
void motion(int x, int y) {
	glm::dvec2 mOffset = mCoord; // var. global
	mCoord = glm::dvec2(x, (glutGet(GLUT_WINDOW_HEIGHT) - y));
	mOffset = (mCoord - mOffset) * 0.05; // sensitivity = 0.05
	camera.rotatePY(mOffset.y, mOffset.x);
	glutPostRedisplay();
}
//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  cout << "Starting console..." << '\n';

  // Initialization
  glutInit(&argc, argv);

  glutInitContextVersion(3, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);   
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS); 
  glutInitWindowSize(800, 600);   // window size
  //glutInitWindowPosition (140, 140);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);   // | GLUT_STENCIL  
  
  int win = glutCreateWindow( "Freeglut-project" );  // window's identifier
  
  // Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutSpecialFunc(specialKey);
  glutDisplayFunc(display);
  //Practica1.2
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
 
  cout << glGetString(GL_VERSION) << '\n';
  cout << glGetString(GL_VENDOR) << '\n';
 
  scene.init();    // after creating the context
   
  glutMainLoop(); 
    
  //cin.sync();   cin.get();
  glutDestroyWindow(win);  // Destroy the context 

  return 0;
}
//-------------------------------------------------------------------------

void display()   // double buffer
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	GLfloat p[] = { 500.0f, 500.0f, 500.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, p);
  
  scene.render();
  //diabolo.render(camera.getViewMat());
    
  glutSwapBuffers();  
}
//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight)
{
  // Resize Viewport 
  viewPort.setSize(newWidth, newHeight);  
  // Resize Scene Visible Area 
  camera.setSize(viewPort.getW(), viewPort.getH());    // scale unchanged
}
//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case 27:  // Escape key 
    glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop 
    break;
  case '+': 
    camera.scale(+0.03);   // zoom in  
    break;
  case '-':
    camera.scale(-0.03);   // zoom out
    break;
  case 'l':
	  camera.set3D();
	  break;
  case 'o':
	  camera.setAZ();
	  break;
  /*case 'a':
	  diabolo.rota();
	  //camera.roll(0.2);
	  break;*/
  case 'a':
	 camera.moveLR(-3.0);
	 //glutPostRedisplay();
	  break;
  case 'd':
	  camera.moveLR(3.0);
	  //glutPostRedisplay();
	  break;
  case 'w':
	  camera.moveFB(3.0);
	  //glutPostRedisplay();
	  break;
  case 's':
	  camera.moveFB(-3.0);
	  //glutPostRedisplay();
	  break;
  case 'p':
	  //camera.setPrj();
	  //glutPostRedisplay();
	  camera.set3D2();
	  break;
  case 'k':
	  camera.moveUD(3.0);
	  glutPostRedisplay();
	  break;
  case 'm':
	  camera.moveUD(-3.0);
	  glutPostRedisplay();
	  break;
  case 'f':
	  textura.loadColorBuffer(800,600);
	  textura.save("..\\Bmps\\juan.bmp");
	  break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

void specialKey(int key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case GLUT_KEY_RIGHT:
    camera.pitch(5);   // rotate 1 on the X axis
    break;
  case GLUT_KEY_LEFT:
    camera.yaw(5);     // rotate 1 on the Y axis 
    break;
  case GLUT_KEY_UP:
    camera.roll(5);    // rotate 1 on the Z axis
    break;
  case GLUT_KEY_DOWN:
    camera.roll(-5);   // rotate -1 on the Z axis
    break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

