#include "utilize.h"

void xMove(float value)
{
	switch (mm.controlMode){
		case Translation:
			// mm.model->T.translate(0.01, 0, 0);
			mm.model->tx += (GLfloat)value;
			break;
		case Scaling:
			// mm.model->S.scale(1.01, 1, 1);
			mm.model->sx += (GLfloat)value;
			break;
		case Rotation:
			// mm.model->R.rotateX(1);
			mm.model->rx += (GLfloat)value;
			break;
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
			mm.lightSource[2].spotExponent += value * 100;
			glUniform1f(iLocSSpotExponent, mm.lightSource[2].spotExponent);
			break;
	}
}

void yMove(float value)
{
	switch (mm.controlMode){
		case Translation:
			// mm.model->T.translate(0.01, 0, 0);
			mm.model->ty += (GLfloat)value;
			break;
		case Scaling:
			// mm.model->S.scale(1.01, 1, 1);
			mm.model->sy += (GLfloat)value;
			break;
		case Rotation:
			// mm.model->R.rotateX(1);
			mm.model->ry += (GLfloat)value;
			break;
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
			mm.lightSource[2].spotExponent += value * 100;
			glUniform1f(iLocSSpotExponent, mm.lightSource[2].spotExponent);
			break;
	}
}

void zMove(float value)
{
	switch (mm.controlMode){
		case Translation:
			// mm.model->T.translate(0.01, 0, 0);
			mm.model->tz += (GLfloat)value;
			break;
		case Scaling:
			// mm.model->S.scale(1.01, 1, 1);
			mm.model->sz += (GLfloat)value;
			break;
		case Rotation:
			// mm.model->R.rotateX(1);
			mm.model->rz += (GLfloat)value;
			break;
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
			mm.lightSource[2].spotExponent += value * 100;
			glUniform1f(iLocSSpotExponent, mm.lightSource[2].spotExponent);
			break;
	}
}

void rotateTimer(int value)
{
	if (mm.rotate == true)
		mm.model->ry += (GLfloat)0.01;
	glutPostRedisplay();
	glutTimerFunc(1, rotateTimer, value);
}

void onIdle()
{
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

	mm.setMVP();

	mm.updateModelGroup();

	glutSwapBuffers();
}

void onMouse(int who, int state, int x, int y)
{
	// printf("%18s(): (%d, %d) ", __FUNCTION__, x, y);
	switch(who){
		// case GLUT_LEFT_BUTTON:   printf("left button   "); break;
		// case GLUT_MIDDLE_BUTTON: printf("middle button "); break;
		// case GLUT_RIGHT_BUTTON:  printf("right button  "); break;
		// case GLUT_WHEEL_UP:      printf("wheel up      "); break;
		// case GLUT_WHEEL_DOWN:    printf("wheel down    "); break;
		// default:                 printf("0x%02X          ", who); break;
		default:
			break;
	}
	switch(state){
		// case GLUT_DOWN: printf("start "); break;
		// case GLUT_UP:   printf("end   "); break;
		default:
			break;
	}
	// printf("\n");
}

void onMouseMotion(int x, int y)
{
	// printf("%18s(): (%d, %d) mouse move\n", __FUNCTION__, x, y);
}

void onKeyboard(unsigned char key, int x, int y)
{
	// printf("%18s(): (%d, %d) key: %c(0x%02X) ", __FUNCTION__, x, y, key, key);
	switch(key){
		case GLUT_KEY_ESC: /* the Esc key */
			exit(0);
			break;
		case 'T': case 't':
			mm.controlMode = Translation;
			// mm.model->tx = 0, mm.model->ty = 0, mm.model->tz = 0;
			puts("\n\n  ====== Translation Mode Start ======");
			mm.showTranslationMenu();
			break;
		case 'S': case 's':
			mm.controlMode = Scaling;
			puts("\n\n  ====== Scaling Mode Start ======");
			mm.showScalingMenu();
			break;
		case 'R': case 'r':
			mm.rotate = !mm.rotate;
			break;
		/*case 'r':
			mm.controlMode = Rotation;
			puts("\n\n  ====== Rotation Mode Start ======");
			mm.showRotationMenu();
			break;*/
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
		case 'M': case 'm':
			zMove(0.01);
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
			mm.loadOBJModel(mm.displayIndex);
			break;
		case 'X': case 'x':
			mm.displayIndex = (mm.displayIndex + 1) % mm.size;
			mm.loadOBJModel(mm.displayIndex);
			break;
		case 'H': case 'h':
			mm.showHelpMenu();
			break;
		case 'C': case 'c':
			system("cls");
			break;
		case 'W': case 'w':
			mm.displayMode = (mm.displayMode==0) ? 1 : 0;
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
		case'4':
			if (lightType[3] == 0.0f) lightType[3] = 1.0f;
			else lightType[3] = 0.0f;
			break;
		
	}
	// printf("\n");
}

void onKeyboardSpecial(int key, int x, int y){
	// printf("%18s(): (%d, %d) ", __FUNCTION__, x, y);
	switch(key){
		case GLUT_KEY_LEFT:
			mm.displayIndex = (mm.size + mm.displayIndex - 1) % mm.size;
			mm.loadOBJModel(mm.displayIndex);
			// printf("key: LEFT ARROW");
			break;

		case GLUT_KEY_RIGHT:
			mm.displayIndex = (mm.displayIndex + 1) % mm.size;
			mm.loadOBJModel(mm.displayIndex);
			// printf("key: RIGHT ARROW");
			break;
		default:
			// printf("key: 0x%02X      ", key);
			break;
	}
	// printf("\n");
}

void onWindowReshape(int width, int height)
{
	// printf("%18s(): %dx%d\n", __FUNCTION__, width, height);
	if (height == 0) height = 1;
	float aspectRatio = (float) width/height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);       // fix up the viewport to maintain aspect ratio
	gluPerspective(45, aspectRatio, .001, 1000);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}