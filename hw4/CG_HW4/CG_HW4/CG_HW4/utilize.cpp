#include "utilize.h"

int rotateStartX = 0, rotateStartY = 0;
int translateStartX = -1, translateStartY = -1;
int isLBtnDown = 0;
int isRBtnDown = 0;

void xMove(float value)
{
	switch (mm.controlMode){
		case Eye:
			mm.model->eyeVec[0] += value;
			mm.model->centerVec[0] += value;
			mm.model->upVec[0] += value;
			break;
		case Directional:
			mm.lightSource[0].position[0] += value * 20;
			glUniform4fv(iLocLDPosition, 1, mm.lightSource[0].position);
			break;
		case Point:
			mm.lightSource[1].position[0] += value * 20;
			glUniform4fv(iLocLPPosition, 1, mm.lightSource[1].position);
			break;
		case Spot:
			mm.lightSource[2].position[0] += value * 2;
			glUniform4fv(iLocLSPosition, 1, mm.lightSource[2].position);
			break;
		case SpotCo:
			mm.lightSource[2].spotCutoff += value * 10;
			glUniform1f(iLocLSSpotcutoff, mm.lightSource[2].spotCutoff);
			break;
		case SpotEx:
			mm.lightSource[2].spotExponent += value * 100000;
			glUniform1f(iLocSSpotExponent, mm.lightSource[2].spotExponent);
			break;
	}
}

void yMove(float value)
{
	switch (mm.controlMode){
		case Eye:
			mm.model->eyeVec[1] += value;
			mm.model->centerVec[1] += value;
			mm.model->upVec[1] += value;
			break;
		case Directional:
			mm.lightSource[0].position[1] += value * 20;
			glUniform4fv(iLocLDPosition, 1, mm.lightSource[0].position);
			break;
		case Point:
			mm.lightSource[1].position[1] += value * 20;
			glUniform4fv(iLocLPPosition, 1, mm.lightSource[1].position);
			break;
		case Spot:
			mm.lightSource[2].position[1] += value * 2;
			glUniform4fv(iLocLSPosition, 1, mm.lightSource[2].position);
			break;
		case SpotCo:
			mm.lightSource[2].spotCutoff += value * 10;
			glUniform1f(iLocLSSpotcutoff, mm.lightSource[2].spotCutoff);
			break;
		case SpotEx:
			mm.lightSource[2].spotExponent += value * 100000;
			glUniform1f(iLocSSpotExponent, mm.lightSource[2].spotExponent);
			break;
	}
}

void zMove(float value)
{
	switch (mm.controlMode){
		case Eye:
			mm.model->eyeVec[2] += value;
			mm.model->centerVec[2] += value;
			mm.model->upVec[2] += value;
			break;
		case Directional:
			mm.lightSource[0].position[2] += value * 20;
			glUniform4fv(iLocLDPosition, 1, mm.lightSource[0].position);
			break;
		case Point:
			mm.lightSource[1].position[2] += value * 20;
			glUniform4fv(iLocLPPosition, 1, mm.lightSource[1].position);
			break;
		case Spot:
			mm.lightSource[2].position[2] += value * 2;
			glUniform4fv(iLocLSPosition, 1, mm.lightSource[2].position);
			break;
		case SpotCo:
			mm.lightSource[2].spotCutoff += value * 10;
			glUniform1f(iLocLSSpotcutoff, mm.lightSource[2].spotCutoff);
			break;
		case SpotEx:
			mm.lightSource[2].spotExponent += value * 100000;
			glUniform1f(iLocSSpotExponent, mm.lightSource[2].spotExponent);
			break;
	}
}

void onIdle()
{
	if (mm.rotate == true)
		mm.model->R.rotateY(0.08);
	glutPostRedisplay();
}

void onDisplay(void)
{
	int displayMode = !mm.displayMode ? GL_FILL : GL_LINE;
	// clear canvas
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, displayMode);

	glEnableVertexAttribArray(iLocPosition);
	glEnableVertexAttribArray(iLocNormal);
	glEnableVertexAttribArray(iLocTexCoord);

	mm.setMVP();

	mm.updateModelGroup();

	glutSwapBuffers();
}

void onMouse(int who, int state, int x, int y)
{
	if (who == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && isLBtnDown == 0){
		rotateStartX = x;
		rotateStartY = y;
		isRBtnDown = 1;
	}
	else if (who == GLUT_RIGHT_BUTTON && state == GLUT_UP)
		isRBtnDown = 0;
	else if (who == GLUT_LEFT_BUTTON && state == GLUT_DOWN && isRBtnDown == 0){
		translateStartX = x;
		translateStartY = y;
		isLBtnDown = 1;
	}
	else if (who == GLUT_LEFT_BUTTON && state == GLUT_UP)
		isLBtnDown = 0;
	else if (who == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN){
		mm.model->T.identity();
		mm.model->S.identity();
		mm.model->R.identity();
	}
	else if (who == GLUT_WHEEL_UP && state == GLUT_DOWN)
		mm.model->S.scale(1.02, 1.02, 1.02);
	else if (who == GLUT_WHEEL_DOWN && state == GLUT_DOWN)
		mm.model->S.scale(0.98, 0.98, 0.98);
}

void onMouseMotion(int x, int y)
{
	if (isLBtnDown){
		float translateX = (float)x - translateStartX,
			  translateY = (float)y - translateStartY;
		mm.model->T.translate(translateX / 250, -translateY / 250, 0);
		translateStartX = x;
		translateStartY = y;
	}
	if (isRBtnDown){
		float rotateX = (float)x - rotateStartX,
			  rotateY = (float)y - rotateStartY;
		float temp = sqrt(rotateX * rotateX + rotateY * rotateY);
		mm.model->R.rotateX(rotateY / 2);
		mm.model->R.rotateY(rotateX / 2);
		rotateStartX = x;
		rotateStartY = y;
	}
}

void onKeyboard(unsigned char key, int x, int y)
{
	switch(key){
		case GLUT_KEY_ESC: /* the Esc key */
			exit(0);
			break;
		case 'T': case 't':
			mm.toggleTextureMapping();
			break;
		case 'R':
			mm.rotate = !mm.rotate;
			break;
		case 'E': case 'e':
			mm.controlMode = Eye;
			puts("\n\n  ====== Eye Mode Start ======");
			mm.showEyeMenu();
			break;
		case 'P': case 'p':
			mm.projectionMode = !mm.projectionMode;
			if (!mm.projectionMode) puts("\n\n  ====== Parallel Projection Start ======\n");
			else puts("\n\n  ====== Perspective Projection Start ======\n");
			break;
		case '5':
			mm.controlMode = Directional;
			puts("\n\n  ====== Move Directional Light Mode Start ======");
			break;
		case '6':
			mm.controlMode = Point;
			puts("\n\n  ====== Move Point Light Mode Start ======");
			break;
		case '7':
			mm.controlMode = Spot;
			puts("\n\n  ====== Move Spot Light Mode Start ======");
			break;
		case '8':
			mm.controlMode = SpotCo;
			puts("\n\n  ====== Modify SpotCo Mode Start ======");
			break;
		case '9':
			mm.controlMode = SpotEx;
			puts("\n\n  ====== Modify SpotEx Mode Start ======");
			break;
		case 'L': case 'l':
			xMove(0.01);
			break;
		case 'I': case 'i':
			yMove(0.01);
			break;
		case 'M':
			mm.toggleMagFilter();
			break;
		case 'm':
			mm.toggleMinFilter();
			break;
		case 'J': case 'j':
			xMove(-0.01);
			break;
		case 'K': case 'k':
			yMove(-0.01);
			break;
		case 'O': case 'o':
			zMove(-0.01);
			break;
		case 'Z': case 'z':
			mm.displayIndex = (mm.size + mm.displayIndex - 1) % mm.size;
			mm.startManaging(mm.displayIndex);
			break;
		case 'X': case 'x':
			mm.displayIndex = (mm.displayIndex + 1) % mm.size;
			mm.startManaging(mm.displayIndex);
			break;
		case 'H': case 'h':
			mm.showHelpMenu();
			break;
		case 'C': case 'c':
			system("cls");
			break;
		case 'W': case 'w':
			mm.toggleWrapMode();
			break;
		case ' ':
			mm.displayMode = (mm.displayMode == 0) ? 1 : 0;
			break;
		case '1':
			if (lightType[0] == 0.0f) lightType[0] = 1.0f;
			else lightType[0] = 0.0f;
			break;
		case '2':
			if (lightType[1] == 0.0f) lightType[1] = 1.0f;
			else lightType[1] = 0.0f;
			break;
		case '3':
			if (lightType[2] == 0.0f) lightType[2] = 1.0f;
			else lightType[2] = 0.0f;
			break;
		case'V': case'v':
			mm.toggleShading();
			break;
	}
}

void onKeyboardSpecial(int key, int x, int y){
	switch(key){
		case GLUT_KEY_LEFT:
			mm.displayIndex = (mm.size + mm.displayIndex - 1) % mm.size;
			mm.startManaging(mm.displayIndex);
			break;

		case GLUT_KEY_RIGHT:
			mm.displayIndex = (mm.displayIndex + 1) % mm.size;
			mm.startManaging(mm.displayIndex);
			break;
		default:
			break;
	}
}

void onWindowReshape(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
	
	glViewport(0, 0, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float ratio = (float)screenWidth / (float)screenHeight;
	gluPerspective(90.0f, ratio, mm.znear, mm.zfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
