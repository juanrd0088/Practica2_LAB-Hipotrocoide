#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <stdio.h>

using namespace glm;

//-------------------------------------------------------------------------

 void Viewport::setSize(GLsizei aw, GLsizei ah) 
 { 
   w = aw; 
   h = ah; 
   set(); 
 }
 //-------------------------------------------------------------------------

 void Viewport::setPos(GLsizei ax, GLsizei ay)
 {
	 x = ax;
	 y = ay;
	 set();
 }
 //-------------------------------------------------------------------------

 void Viewport::set() 
 { 
   glViewport(x, y, w, h);
 }
//-------------------------------------------------------------------------

void Camera::setAZ() 
{
  eye= dvec3(0, 0, 500);//Distancia del ojo, 500 en el eje z
  look= dvec3(0, 0, 0);//Miras al origen
  up= dvec3(0, 1, 0);
  n = normalize(eye - look);
  u = normalize(cross(up, n));
  v = cross(n, u);
  e = eye;
  right = u;
  front = -n;
  //orto = true;
  viewMat = lookAt(eye, look, up);
  //projMat = frustum(xLeft, xRight, yBot, yTop, 2 * yTop, farVal);
  setVM();
  //setPM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
  eye= dvec3(100, 100, 100);
  look= dvec3(0, 10, 0);
  up= dvec3(0, 1, 0);
  n = normalize(eye - look);
  u = normalize(cross(up, n));
  v = cross(n, u);
  e = eye;
  right = u;
  front = -n;
  //orto = true;
  viewMat = lookAt(eye, look, up);
  //projMat = frustum(xLeft, xRight, yBot, yTop, 2 * yTop, farVal);
  setVM();
  //setPM();
}
//-------------------------------------------------------------------------
void Camera::set3D2()
{
	eye = dvec3(-500, 500, -500);
	look = dvec3(0, 10, 0);
	up = dvec3(0, 1, 0);
	n = normalize(eye - look);
	u = normalize(cross(up, n));
	v = cross(n, u);
	e = eye;
	right = u;
	front = -n;
	//orto = true;
	viewMat = lookAt(eye, look, up);
	//projMat = frustum(xLeft, xRight, yBot, yTop, 2 * yTop, farVal);
	setVM();
	//setPM();
}
//-------------------------------------------------------------------------

void Camera::setVM() 
{
  //projMat = frustum(xLeft, xRight, yBot, yTop, 2 * yTop, farVal);
  //glMatrixMode(GL_PROJECTION);
  //glLoadMatrixd(value_ptr(projMat));
  //Estas eran las lineas originales
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(viewMat));
	/*if (orto) {
		projMat = ortho(xLeft, xRight, yBot, yTop, nearVal, farVal);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixd(value_ptr(projMat));
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(value_ptr(viewMat));
		//setPM();
	}
	else {
		projMat = frustum(xLeft, xRight, yBot, yTop, 2*yTop, farVal);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixd(value_ptr(projMat));
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(value_ptr(viewMat));
	}*/
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a) 
{  
  viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
}
//-------------------------------------------------------------------------
void Camera::yaw(GLdouble a)
{
  viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
}
//-------------------------------------------------------------------------
void Camera::roll(GLdouble a)
{
  viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}
//-------------------------------------------------------------------------

void Camera::scale(GLdouble s)
{ 
  factScale -= s; 
  if (s < 0) s = 0.01;
  setPM(); 
}
//-------------------------------------------------------------------------

void Camera::setSize(GLdouble aw, GLdouble ah) 
{
  xRight = aw / 2.0;
  xLeft = -xRight;
  yTop = ah / 2.0;
  yBot = -yTop;
 
  setPM();
}
//-------------------------------------------------------------------------

void Camera::setPM() 
{
  /*projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixd(value_ptr(projMat));
  glMatrixMode(GL_MODELVIEW);*/
	if (orto) {
		projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixd(value_ptr(projMat));
		glMatrixMode(GL_MODELVIEW);
	}
	else {
		projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, yTop, farVal);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixd(value_ptr(projMat));
		glMatrixMode(GL_MODELVIEW);
	}
}
//-------------------------------------------------------------------------

void Camera::moveLR(GLdouble cs)
{
	/*n = normalize(eye - look);
	u = normalize(cross(up, n));
	v = cross(n, u);
	e = eye;
	right = u;
	front = -n;*/
	eye = eye + (right * cs);
	viewMat = lookAt(eye, eye + front, up);
	//setVM();
	//setPM();
}
//-------------------------------------------------------------------------
void Camera::moveFB(GLdouble cs)
{
	/*n = normalize(eye - look);
	u = normalize(cross(up, n));
	v = cross(n, u);
	e = eye;
	right = u;
	front = -n;*/
	eye = eye + (front*cs);
	viewMat = lookAt(eye, eye + front, up);
	//setVM();
	//setPM();
}
//-------------------------------------------------------------------------
void Camera::moveUD(GLdouble cs)
{
	/*n = normalize(eye - look);
	u = normalize(cross(up, n));
	v = cross(n, u);
	e = eye;
	right = u;
	front = -n;*/
	eye = eye + (up*cs);
	viewMat = lookAt(eye, eye + front, up);
	//setVM();
	//setPM();
}
//-------------------------------------------------------------------------
void Camera::rotatePY(GLdouble incrPitch, GLdouble incrYaw){
	
	//rotatePY(a,0) ==> viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
	//viewMat = rotate(viewMat, glm::radians(-incrPitch), glm::dvec3(1.0, 0, 0));

	//rotatePY(0,a) ==> viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
	//viewMat = rotate(viewMat, glm::radians(-incrYaw), glm::dvec3(0, 1.0, 0));

	//¿? ==> viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
	pitch2 += incrPitch;
	yaw2 += incrYaw;
	if (pitch2 > 89.0f)
		pitch2 = 89.0f;
	if (pitch2 < -89.0f)
		pitch2 = -89.0f;
	front.x = sin(radians(yaw2)) * cos(radians(pitch2)); //cos(glm::radians(yaw2)) * cos(glm::radians(pitch2));
	front.y = sin(radians(pitch2)); //sin(glm::radians(pitch2));
	front.z = -cos(radians(yaw2)) * cos(radians(pitch2)); //sin(glm::radians(yaw2)) * cos(glm::radians(pitch2));
	front = glm::normalize(front);	viewMat = lookAt(eye, eye + front, up);	/*setVM();	setPM();*/}
//-------------------------------------------------------------------------
void Camera::setPrj() {
	//projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	if (!orto) {
		orto = true;
		setPM();
		//Pongo ortogonal
		//glMatrixMode(GL_PROJECTION);
		//projMat = ortho(xLeft, xRight, yBot, yTop, nearVal, farVal);
		//glLoadMatrixd(value_ptr(projMat));
		//glMatrixMode(GL_MODELVIEW);
	}
	else {
		orto = false;
		setPM();
		//pongo perspectiva
		//glMatrixMode(GL_PROJECTION);
		//projMat = frustum(xLeft, xRight, yBot, yTop, 2*yTop, farVal);
		//glMatrixMode(GL_PROJECTION);
		//glLoadMatrixd(value_ptr(projMat));
		//setVM();
		//glMatrixMode(GL_MODELVIEW);
	}
}

//-------------------------------------------------------------------------

