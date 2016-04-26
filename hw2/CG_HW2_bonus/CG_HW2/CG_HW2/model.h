#pragma once

#include "header.h"

using namespace std;

class BonusModel{
public:
	GLfloat* vertices;
	GLfloat* colors;
	GLfloat maxVal[3], minVal[3];
	GLfloat dx, dy, dz;
	GLfloat xLen, yLen, zLen, maxLen, minLen, scale;
	GLfloat mvp[16];
	GLfloat tx, ty, tz, sx, sy, sz, rx, ry, rz;
	Matrix4 N;	// normalization matrix
	Matrix4 T;	// translation matrix
	Matrix4 S;	// scaling matrix
	Matrix4 R;	// final rotation matrix
	Matrix4 RX;	// rotation matrix in X-axis
	Matrix4 RY;	// rotation matrix in Y-axis
	Matrix4 RZ;	// rotation matrix in Z-axis
	Matrix4 MVP;

	BonusModel();
	~BonusModel();
};

class ModelManager{
	public:
		int displayMode, displayIndex, size, controlMode, projectionMode, bonusMode;
		BonusModel* bonusModelList[5];
		GLMmodel* displayBonusModel[5];
		Matrix4 VM;	// final viewing matrix
		Matrix4 VT;
		Matrix4 VR;
		Vector3 eyeVec, centerVec, upVec;

		ModelManager(string path);
		void showObjectInfo(int index);
		void showHelpMenu();
		void showTranslationMenu();
		void showScalingMenu();
		void showRotationMenu();
		void showEyeMenu();
		void prevIndex();
		void nextIndex();

		void startBonusManaging();
		void loadBonusModel(int index);
		void traverseBonusColorModel(GLMmodel* OBJ, int index);
		void setBonusNormalizeMatrix(int index);
		void setBonusTranslationMatrix(int index);
		void setBonusScalingMatrix(int index);
		void setBonusRotationMatrix(int index);
		void setBonusViewingMatrix();
		void setBonusProjectionMatrix(int projectionMode);
		void setBonusMVP(int index);
		~ModelManager();

	private:
		string path;
		vector<string> bonusModelNameList;

		void traverseBonusModelName(const char *pathName, int depth);
};