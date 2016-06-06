#pragma once

#include "header.h"
#include "model.h"

#ifndef GLUT_WHEEL_UP
	#define GLUT_WHEEL_UP   0x0003
	#define GLUT_WHEEL_DOWN 0x0004
#endif

#ifndef GLUT_KEY_ESC
	#define GLUT_KEY_ESC 0x1B
#endif

extern ModelManager mm;
extern int rotateStartX, rotateStartY;
extern int translateStartX, translateStartY;
extern int isLBtnDown;
extern int isRBtnDown;
extern int screenWidth;
extern int screenHeight;

void xMove(float value);

void yMove(float value);

void zMove(float value);

void onIdle();

void onDisplay(void);

void onMouse(int who, int state, int x, int y);

void onMouseMotion(int x, int y);

void onKeyboard(unsigned char key, int x, int y);

void onKeyboardSpecial(int key, int x, int y);

void onWindowReshape(int width, int height);
