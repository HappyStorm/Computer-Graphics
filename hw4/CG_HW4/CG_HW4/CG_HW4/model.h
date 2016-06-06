#pragma once

#include "header.h"
using namespace std;

struct LightSourceParameters {
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float position[4];
	float halfVector[4];
	float spotDirection[4];
	float spotExponent;
	float spotCutoff;		// (range: [0.0,90.0], 180.0)
	float spotCosCutoff;	// (range: [1.0,0.0],-1.0)
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
}typedef LightSource;

class Model{
	public:
		GLfloat* vertices;
		GLMgroup* groups;

		GLfloat maxVal[3], minVal[3];
		GLfloat dx, dy, dz;
		GLfloat xLen, yLen, zLen, maxLen, scale;
		GLfloat mvp[16];
		GLfloat mn[16];
		GLfloat vmn[16];
		GLfloat v[16];
		Vector3 eyeVec, centerVec, upVec;
		Matrix4 N;	// normalization matrix
		Matrix4 T;	// translation matrix
		Matrix4 S;	// scaling matrix
		Matrix4 R;	// final rotation matrix
		Matrix4 VM;	// final viewing matrix
		Matrix4 VT;
		Matrix4 VR;
		Matrix4 MVP;
		Matrix4 MN; // MN = (T * S * R) * N
		Matrix4 VMN; // VM = V * M * N
		Matrix4 V;

		Model();
		~Model();
};

class ModelManager{
	public:
		const float xmin = -1.0, xmax = 1.0;
		const float ymin = -1.0, ymax = 1.0;
		const float znear = 0.0f - sqrtf(3.0f), zfar = 0.0f + sqrtf(3.0f);
		int displayMode, displayIndex, size, controlMode, projectionMode;
		bool rotate;
		Model* model;
		GLMmodel* displayModel;
		LightSource lightSource[3];
		Matrix4 viewPort;
		GLint mag_Filter;
		GLint min_Filter;
		GLint wrap_Mode;

		ModelManager(string path);
		void loadOBJModel(int index);
		void startManaging(int index);
		void showHelpMenu();
		void showEyeMenu();
		void traverseColorModel(GLMmodel* OBJ);
		void setNormalizeMatrix();
		void setViewingMatrix();
		void setProjectionMatrix(int projectionMode);
		void setMVP();
		void setLightingSource();
		void updateModelGroup();

		void LoadTextures(char* filename, int index);
		void initTextures(int index);
		void setTexture();
		void toggleTextureMapping();
		void toggleMagFilter();
		void toggleMinFilter();
		void toggleWrapMode();
		void toggleShading();
		~ModelManager();

	private:
		string path;
		vector<string> modelNameList;
		void traverseModelName(const char *pathName, int depth);
};
