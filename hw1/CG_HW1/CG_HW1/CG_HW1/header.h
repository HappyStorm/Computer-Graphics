#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <freeglut/glut.h>

#include "textfile.h"
#include "glm.h"
#include "dirent.h"

#define max(a,b) (((a)>(b)) ? (a) : (b) )
#define min(a,b) (((a)<(b)) ? (a) : (b) )
#define abs(x)   (((x)>0)   ? (x) : (-x))

extern GLint iLocPosition;
extern GLint iLocColor;
const float ASPECT = 1.0;