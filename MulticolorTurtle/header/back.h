#pragma once
#include <GL/gl.h>

GLuint loadBMP(const char* file);
void   init_background(const char* file);
void   init_menu_background(const char* file);
void   drawBackground();
void   drawMenuBackground();
