#include "header.h"
#include "shader.h"
#include "utilize.h"
#include "model.h"

#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "freeglut.lib")

// Shader attributes
GLint iLocPosition;
GLint iLocColor;
GLint iLocMVP;
Matrix4 M = Matrix4(
					1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
Matrix4 V = Matrix4(
					1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
Matrix4 P = Matrix4(
					1, 0,  0, 0,
					0, 1,  0, 0,
					0, 0, -1, 0,
					0, 0,  0, 1);

ModelManager mm = ModelManager("./ColorModels");

int main(int argc, char **argv)
{	
	// glut init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	// create window
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("10420 CS550000 CG HW2 Haley");

	glewInit();
	if(glewIsSupported("GL_VERSION_2_0")){
		printf("Ready for OpenGL 2.0\n");
	}
	else{
		printf("OpenGL 2.0 not supported\n");
		system("pause");
		exit(1);
	}
	mm.showHelpMenu();

	puts("\n\n  ====== Translation Mode Start ======\n");
	mm.startManaging();

	// register glut callback functions
	glutDisplayFunc(onDisplay);
	glutIdleFunc(onIdle);
	glutKeyboardFunc(onKeyboard);
	glutSpecialFunc(onKeyboardSpecial);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMouseMotion);
	glutReshapeFunc(onWindowReshape);

	// set up shaders here
	setShaders();

	glEnable(GL_DEPTH_TEST);

	// main loop
	glutMainLoop();

	return 0;
}

