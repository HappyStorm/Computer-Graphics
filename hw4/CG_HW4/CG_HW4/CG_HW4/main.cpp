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

GLint iLocTexCoord;
GLint iLocTexMapping;
GLfloat texMapping = 1;

GLuint texNum[MAX_TEXTURE_NUM];
unsigned char image[MAX_TEXTURE_NUM][MAXSIZE]; //image data array 
FileHeader FH[MAX_TEXTURE_NUM]; //BMP FileHeader 
InfoHeader IH[MAX_TEXTURE_NUM]; //BMP InfoHeader

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

ModelManager mm = ModelManager("./TextureModels");
int screenWidth;
int screenHeight;

int main(int argc, char **argv)
{	
	// glut init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	// create window
	glutInitWindowPosition(800, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("10420 CS550000 CG HW4 Haley");

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
	mm.startManaging(0);

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
