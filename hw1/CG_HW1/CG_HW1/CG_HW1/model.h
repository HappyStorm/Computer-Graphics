#pragma once

#include "header.h"

using namespace std;

class Model{
	public:
		GLfloat* vertices;
		GLfloat* colors;
		GLfloat maxVal[3], minVal[3];
		GLfloat xLen, yLen, zLen, maxLen, scale;
	
		Model();		
		~Model();
};

class ModelManager{
	public:
		int displayMode, displayIndex, size;
		Model* model;
		GLMmodel* displayModel;

		ModelManager(string path);
		void loadOBJModel(int index);
		void startManaging();
		void traverseColorModel(GLMmodel* OBJ);
		void prevIndex();
		void nextIndex();
		~ModelManager();

	private:
		string path;
		vector<string> modelNameList;

		void traverseModelName(const char *pathName, int depth);
};