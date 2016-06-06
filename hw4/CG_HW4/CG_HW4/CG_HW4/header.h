#pragma once
#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <freeglut/glut.h>

#include "textfile.h"
#include "glm.h"
#include "dirent.h"
#include "Matrices.h"
#include "Vectors.h"
#include "Texture.h"

#define max(a,b) (((a)>(b)) ? (a) : (b) )
#define min(a,b) (((a)<(b)) ? (a) : (b) )
#define abs(x)   (((x)>0)   ? (x) : (-x))

#define MAX_TEXTURE_NUM 50
#define MAXSIZE 200000
#define MAXGROUPSIZE 50

extern GLint iLocPosition;
// extern GLint iLocColor;
extern GLint iLocNormal;
extern GLint iLocMVP;
extern GLint iLocVMN;
extern GLint iLocMN;
extern GLint iLocV;

const float ASPECT = 1.0;

extern Matrix4 M;
extern Matrix4 V;
extern Matrix4 P;

extern GLint iLocMDiffuse,  iLocMAmbient,  iLocMSpecular,  iLocMShininess;
extern GLint iLocLDAmbient, iLocLDDiffuse, iLocLDSpecular, iLocLDPosition, iLocLDSpotcutoff, iLocLDCAttenuation;
extern GLint iLocLPAmbient, iLocLPDiffuse, iLocLPSpecular, iLocLPPosition, iLocLPSpotcutoff, iLocLPCAttenuation, iLocLPLAttenuation, iLocLPQAttenuation;
extern GLint iLocLSAmbient, iLocLSDiffuse, iLocLSSpecular, iLocLSPosition, iLocLSSpotcutoff, iLocLSCAttenuation, iLocSSpotDirection, iLocLSLAttenuation, iLocLSQAttenuation, iLocSSpotExponent;
extern GLint iLocLType;
extern GLint eyePos;
extern GLfloat lightType[4];

extern GLint iLocTexCoord;
extern GLint iLocTexMapping;
extern GLfloat texMapping;

extern GLuint texNum[MAX_TEXTURE_NUM];
extern unsigned char image[MAX_TEXTURE_NUM][MAXSIZE]; //image data array 
extern FileHeader FH[MAX_TEXTURE_NUM]; //BMP FileHeader 
extern InfoHeader IH[MAX_TEXTURE_NUM]; //BMP InfoHeader

enum LightModeControl{Eye, Directional, Point, Spot, SpotEx, SpotCo};
enum Shading{Gouraud, Phong};
