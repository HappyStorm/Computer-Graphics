#include "utilize.h"

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
	glEnableVertexAttribArray(iLocColor);

	mm.setMVP();

	glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, mm.model->vertices);
	glVertexAttribPointer(iLocColor,	3, GL_FLOAT, GL_FALSE, 0, mm.model->colors);

	// bind uniform matrix to shader
	glUniformMatrix4fv(iLocMVP, 1, GL_FALSE, mm.model->mvp);

	// draw the array we just bound
	glDrawArrays(GL_TRIANGLES, 0, mm.displayModel->numtriangles * 3);
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
		case GLUT_KEY_T: case GLUT_KEY_t:
			mm.controlMode = 0;
			// mm.model->tx = 0, mm.model->ty = 0, mm.model->tz = 0;
			puts("\n\n  ====== Translation Mode Start ======");
			mm.showTranslationMenu();
			break;
		case GLUT_KEY_S: case GLUT_KEY_s:
			mm.controlMode = 1;
			puts("\n\n  ====== Scaling Mode Start ======");
			mm.showScalingMenu();
			break;
		case GLUT_KEY_R: case GLUT_KEY_r:
			mm.controlMode = 2;
			puts("\n\n  ====== Rotation Mode Start ======");
			mm.showRotationMenu();
			break;
		case GLUT_KEY_E: case GLUT_KEY_e:
			mm.controlMode = 3;
			puts("\n\n  ====== Eye Mode Start ======");
			mm.showEyeMenu();
			break;
		case GLUT_KEY_P: case GLUT_KEY_p:
			mm.projectionMode = !mm.projectionMode;
			if (!mm.projectionMode) puts("\n\n  ====== Parallel Projection Start ======\n");
			else puts("\n\n  ====== Perspective Projection Start ======\n");
			break;

		case GLUT_KEY_L: case GLUT_KEY_l:
			switch (mm.controlMode){
				case 0:
					// mm.model->T.translate(0.01, 0, 0);
					mm.model->tx += (GLfloat)0.01;
					break;
				case 1:
					// mm.model->S.scale(1.01, 1, 1);
					mm.model->sx += (GLfloat)0.01;
					break;
				case 2:
					// mm.model->R.rotateX(1);
					mm.model->rx += (GLfloat)0.01;
					break;
				case 3:
					mm.model->eyeVec[0] += 0.01;
					mm.model->centerVec[0] += 0.01;
					mm.model->upVec[0] += 0.01;
					break;
			}
			break;
		case GLUT_KEY_I: case GLUT_KEY_i:
			switch (mm.controlMode){
				case 0:
					// mm.model->T.translate(0, 0.01, 0);
					mm.model->ty += (GLfloat)0.01;
					break;
				case 1:
					// mm.model->S.scale(1, 1.01, 1);
					mm.model->sy += (GLfloat)0.01;
					break;
				case 2:
					// mm.model->R.rotateY(1);
					mm.model->ry += (GLfloat)0.01;
					break;
				case 3:
					mm.model->eyeVec[1] += 0.01;
					mm.model->centerVec[1] += 0.01;
					mm.model->upVec[1] += 0.01;
					break;
			}
			break;
		case GLUT_KEY_M: case GLUT_KEY_m:
			switch (mm.controlMode){
				case 0:
					// mm.model->T.translate(0, 0, 0.01);
					mm.model->tz += (GLfloat)0.01;
					break;
				case 1:
					// mm.model->S.scale(1, 1, 1.01);
					mm.model->sz += (GLfloat)0.01;
					break;
				case 2:
					// mm.model->R.rotateZ(1);
					mm.model->rz += (GLfloat)0.01;
					break;
				case 3:
					mm.model->eyeVec[2] += 0.01;
					mm.model->centerVec[2] += 0.01;
					mm.model->upVec[2] += 0.01;
					break;
			}
			break;
		case GLUT_KEY_J: case GLUT_KEY_j:
			switch (mm.controlMode){
				case 0:
					// mm.model->T.translate(-0.01, 0, 0);
					mm.model->tx -= (GLfloat)0.01;
					break;
				case 1:
					// mm.model->S.scale(0.99, 1, 1);
					mm.model->sx -= (GLfloat)0.01;
					break;
				case 2:
					// mm.model->R.rotateX(-1);
					mm.model->rx -= (GLfloat)0.01;
					break;
				case 3:
					mm.model->eyeVec[0] -= 0.01;
					mm.model->centerVec[0] -= 0.01;
					mm.model->upVec[0] -= 0.01;
					break;
			}
			break;
		case GLUT_KEY_K: case GLUT_KEY_k:
			switch (mm.controlMode){
				case 0:
					// mm.model->T.translate(0, -0.01, 0);
					mm.model->ty -= (GLfloat)0.01;
					break;
				case 1:
					// mm.model->S.scale(1, 0.99, 1);
					mm.model->sy -= (GLfloat)0.01;
					break;
				case 2:
					// mm.model->R.rotateY(-1);
					mm.model->ry -= (GLfloat)0.01;
					break;
				case 3:
					mm.model->eyeVec[1] -= 0.01;
					mm.model->centerVec[1] -= 0.01;
					mm.model->upVec[1] -= 0.01;
					break;
			}
			break;
		case GLUT_KEY_O: case GLUT_KEY_o:
			switch (mm.controlMode){
				case 0:
					// mm.model->T.translate(0, 0, -0.01);
					mm.model->tz -= (GLfloat)0.01;
					break;
				case 1:
					// mm.model->S.scale(1, 1, 0.99);
					mm.model->sz -= (GLfloat)0.01;
					break;
				case 2:
					// mm.model->R.rotateZ(-1);
					mm.model->rz -= (GLfloat)0.01;
					break;
				case 3:
					mm.model->eyeVec[2] -= 0.01;
					mm.model->centerVec[2] -= 0.01;
					mm.model->upVec[2] -= 0.01;
					break;
			}
			break;
		case GLUT_KEY_z: case GLUT_KEY_Z:
			mm.displayIndex = (mm.size + mm.displayIndex - 1) % mm.size;
			mm.loadOBJModel(mm.displayIndex);
			break;
		case GLUT_KEY_x: case GLUT_KEY_X:
			mm.displayIndex = (mm.displayIndex + 1) % mm.size;
			mm.loadOBJModel(mm.displayIndex);
			break;
		case GLUT_KEY_h: case GLUT_KEY_H:
			mm.showHelpMenu();
			break;
		case GLUT_KEY_c: case GLUT_KEY_C :
			system("cls");
			break;
		case GLUT_KEY_w: case GLUT_KEY_W:
			mm.displayMode = (mm.displayMode==0) ? 1 : 0;
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