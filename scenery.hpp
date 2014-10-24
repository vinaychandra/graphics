#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdio.h>
#include <cstdlib>

#ifndef _GL_SCENERY_
#define _GL_SCENERY_

struct scenery
{
	GLuint ground_texture;
	GLuint sky_texture;

	void load_textures();
	void create_all();
	void create_ground();
	void create_sky();
	void make_lights();

	GLuint load_texture(const char*);

};

#endif