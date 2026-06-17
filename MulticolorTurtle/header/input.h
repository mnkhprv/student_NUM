#ifndef AM_INPUT_H
#define AM_INPUT_H

#include "render.h"

void timer_cb(int);
void display();
void reshape(int w, int h);
void mouseBtn(int btn, int state, int x, int y);
void mouseMove(int x, int y);
void mouseWheel(int, int dir, int, int);
void keyboard(unsigned char key, int, int);

#endif