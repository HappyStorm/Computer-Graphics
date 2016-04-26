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
extern GLint iLocColor;
extern GLint iLocMVP;
const float ASPECT = 1.0;

extern Matrix4 M;
extern Matrix4 V;
extern Matrix4 P;
