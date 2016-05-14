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
		GLfloat tx, ty, tz, sx, sy, sz, rx, ry, rz;
		Vector3 eyeVec, centerVec, upVec;
		Matrix4 N;	// normalization matrix
		Matrix4 T;	// translation matrix
		Matrix4 S;	// scaling matrix
		Matrix4 R;	// final rotation matrix
		Matrix4 RX;	// rotation matrix in X-axis
		Matrix4 RY;	// rotation matrix in Y-axis
		Matrix4 RZ;	// rotation matrix in Z-axis
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
		int displayMode, displayIndex, size, controlMode, projectionMode;
		bool rotate;
		Model* model;
		GLMmodel* displayModel;
		LightSource lightSource[3];

		ModelManager(string path);
		void loadOBJModel(int index);
		void startManaging();
		void showHelpMenu();
		void showTranslationMenu();
		void showScalingMenu();
		void showRotationMenu();
		void showEyeMenu();
		void traverseColorModel(GLMmodel* OBJ);
		void setNormalizeMatrix();
		void setTranslationMatrix();
		void setScalingMatrix();
		void setRotationMatrix();
		void setViewingMatrix();
		void setProjectionMatrix(int projectionMode);
		void setMVP();
		void setLightingSource();
		void updateModelGroup();
		~ModelManager();

	private:
		string path;
		vector<string> modelNameList;
		void traverseModelName(const char *pathName, int depth);
};
