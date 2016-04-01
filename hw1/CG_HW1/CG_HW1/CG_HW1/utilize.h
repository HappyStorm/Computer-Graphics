#pragma once

#include "header.h"
#include "model.h"

#ifndef GLUT_WHEEL_UP
	#define GLUT_WHEEL_UP   0x0003
	#define GLUT_WHEEL_DOWN 0x0004
#endif

#ifndef GLUT_KEY_ESC
	#define GLUT_KEY_ESC 0x1B
	#define GLUT_KEY_C   0x63
	#define GLUT_KEY_W   0x77
	#define GLUT_KEY_Z   0x7A
	#define GLUT_KEY_X   0x78
	#define GLUT_KEY_H   0x68
#endif

extern ModelManager mm;

void onIdle();

void onDisplay(void);

void onMouse(int who, int state, int x, int y);

void onMouseMotion(int x, int y);

void onKeyboard(unsigned char key, int x, int y);

void onKeyboardSpecial(int key, int x, int y);

void onWindowReshape(int width, int height);