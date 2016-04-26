#pragma once

#include "header.h"

using namespace std;

class Model{
	public:
		GLfloat* vertices;
		GLfloat* colors;
		GLfloat maxVal[3], minVal[3];
		GLfloat dx, dy, dz;
		GLfloat xLen, yLen, zLen, maxLen, scale;
		GLfloat mvp[16];
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

		Model();
		~Model();
};

class ModelManager{
	public:
		int displayMode, displayIndex, size, controlMode, projectionMode;
		Model* model;
		GLMmodel* displayModel;

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
		void prevIndex();
		void nextIndex();
		void setMVP();
		~ModelManager();

	private:
		string path;
		vector<string> modelNameList;

		void traverseModelName(const char *pathName, int depth);
};