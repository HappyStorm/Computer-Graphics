#include "header.h"
#include "shader.h"
#include "utilize.h"
#include "model.h"

#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "freeglut.lib")

// Shader attributes
GLint iLocPosition;
GLint iLocNormal;
GLint iLocMVP;
GLint iLocVMN;
GLint iLocMN;
GLint iLocV;
GLint iLocMDiffuse,  iLocMAmbient,  iLocMSpecular,  iLocMShininess;
GLint iLocLDAmbient, iLocLDDiffuse, iLocLDSpecular, iLocLDPosition, iLocLDSpotcutoff, iLocLDCAttenuation;
GLint iLocLPAmbient, iLocLPDiffuse, iLocLPSpecular, iLocLPPosition, iLocLPSpotcutoff, iLocLPCAttenuation, iLocLPLAttenuation, iLocLPQAttenuation;
GLint iLocLSAmbient, iLocLSDiffuse, iLocLSSpecular, iLocLSPosition, iLocLSSpotcutoff, iLocLSCAttenuation, iLocSSpotDirection, iLocLSLAttenuation, iLocLSQAttenuation, iLocSSpotExponent;
GLint iLocLType;
GLint eyePos;
GLfloat lightType[4] = { 0.0, 0.0, 0.0, 0.0 };

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

ModelManager mm = ModelManager("./NormalModels");

int main(int argc, char **argv)
{	
	// glut init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	// create window
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("10420 CS550000 CG HW3 Haley");

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
	glutTimerFunc(1, rotateTimer, 0);

	// set up shaders here
	setShaders();

	glEnable(GL_DEPTH_TEST);

	// main loop
	glutMainLoop();

	return 0;
}
