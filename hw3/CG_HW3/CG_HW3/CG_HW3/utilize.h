#pragma once

#include "header.h"
#include "model.h"

#ifndef GLUT_WHEEL_UP
	#define GLUT_WHEEL_UP   0x0003
	#define GLUT_WHEEL_DOWN 0x0004
#endif

#ifndef GLUT_KEY_ESC
	#define GLUT_KEY_ESC 0x1B
	
	#define GLUT_KEY_C   0x43
	#define GLUT_KEY_T   0x54
	#define GLUT_KEY_S   0x53
	#define GLUT_KEY_R   0x52
	#define GLUT_KEY_E   0x45
	#define GLUT_KEY_I   0x49
	#define GLUT_KEY_J   0x4A
	#define GLUT_KEY_K   0x4B
	#define GLUT_KEY_L   0x4C
	#define GLUT_KEY_O   0x4F
	#define GLUT_KEY_M   0x4D
	#define GLUT_KEY_H   0x48
	#define GLUT_KEY_P   0x50
	#define GLUT_KEY_W   0x57
	#define GLUT_KEY_Z   0x5A
	#define GLUT_KEY_X   0x58

	#define GLUT_KEY_c   0x63
	#define GLUT_KEY_t   0x74
	#define GLUT_KEY_s   0x73
	#define GLUT_KEY_r   0x72
	#define GLUT_KEY_e   0x65
	#define GLUT_KEY_i   0x69
	#define GLUT_KEY_j   0x6A
	#define GLUT_KEY_k   0x6B
	#define GLUT_KEY_l   0x6C
	#define GLUT_KEY_o   0x6F
	#define GLUT_KEY_m   0x6D
	#define GLUT_KEY_h   0x68
	#define GLUT_KEY_p   0x70
	#define GLUT_KEY_w   0x77
	#define GLUT_KEY_z   0x7A
	#define GLUT_KEY_x   0x78
	
#endif

extern ModelManager mm;

void xMove(float value);

void yMove(float value);

void zMove(float value);

void rotateTimer(int value);

void onIdle();

void onDisplay(void);

void onMouse(int who, int state, int x, int y);

void onMouseMotion(int x, int y);

void onKeyboard(unsigned char key, int x, int y);

void onKeyboardSpecial(int key, int x, int y);

void onWindowReshape(int width, int height);