//#pragma once

#ifndef _H_Texture_H_
#define _H_Texture_H_
#include <GL/freeglut.h>
#include <glm.hpp>
#include <string>
#include <iostream>
#include "Pixmap32RGBA.h"
class Texture
{
public:
	Texture() : w(0), h(0), id(0) {};
	~Texture() { if (id != 0) glDeleteTextures(1, &id); }
	bool load(const std::string & BMP_Name, GLubyte alpha = 255);
	bool load(const std::string & BMP_Name, glm::ivec3 color, GLubyte alpha);
	// cargar y transferir a openGL
	void bind();
	void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };
	bool loadColorBuffer(GLsizei width, GLsizei height);
	bool save(const std::string & BMP_Name);

protected:
	GLuint w, h; // dimensiones de la imagen
	GLuint id; // identificador interno (GPU) de la textura
	void init();
};

#endif //_H_Texture_H_