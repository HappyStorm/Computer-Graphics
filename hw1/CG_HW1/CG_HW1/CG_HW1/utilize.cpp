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
	glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, mm.model->vertices);
	glVertexAttribPointer(iLocColor, 3, GL_FLOAT, GL_FALSE, 0, mm.model->colors);

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
		case GLUT_KEY_H:
			puts("\n\n  ====== This is help menu ======\n");
			puts("  'h'         - show this help menu");
			puts("  'c'         - clear console");			
			puts("  'z' / 'x'   - previous / next model");
			puts("  'w'         - wireframe / fill mode");
			puts("  Esc         - exit\n");
			break;
		case GLUT_KEY_C:
			system("cls");
			break;
		case GLUT_KEY_W:
			mm.displayMode = (mm.displayMode==0) ? 1 : 0;
			break;
		case GLUT_KEY_X:
			mm.displayIndex = (mm.displayIndex+1) % mm.size;
			mm.loadOBJModel(mm.displayIndex);
			break;
		case GLUT_KEY_Z:
			mm.displayIndex = (mm.size + mm.displayIndex-1) % mm.size;
			mm.loadOBJModel(mm.displayIndex);
			break;
	}
	// printf("\n");
}

void onKeyboardSpecial(int key, int x, int y){
	// printf("%18s(): (%d, %d) ", __FUNCTION__, x, y);
	switch(key){
		case GLUT_KEY_LEFT:
			// printf("key: LEFT ARROW");
			break;

		case GLUT_KEY_RIGHT:
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
	if (height == 0) height == 1;
	float aspectRatio = (float) width/height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);       // fix up the viewport to maintain aspect ratio
	gluPerspective(45, aspectRatio, .001, 1000);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}