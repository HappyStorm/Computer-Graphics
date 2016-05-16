#pragma once

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

#define max(a,b) (((a)>(b)) ? (a) : (b) )
#define min(a,b) (((a)<(b)) ? (a) : (b) )
#define abs(x)   (((x)>0)   ? (x) : (-x))

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

enum LightModeControl{Translation, Scaling, Rotation, Eye, Directional, Point, Spot, SpotEx, SpotCo};
