#include "model.h"

Model::Model()
{
	for(int i=0; i<3; ++i){
		this->maxVal[i] = -FLT_MAX;
		this->minVal[i] = FLT_MAX;
	}
	this->xLen = this->yLen = this->zLen = this->maxLen = -FLT_MAX;
}
Model::~Model()
{
	free(this->vertices);
	free(this->colors);
}

ModelManager::ModelManager(string path)
{
	this->path = path;
	this->displayMode = 0;
	this->traverseModelName(path.c_str(), 0);
	this->displayIndex = 0;
    this->size = modelNameList.size();
    this->model = NULL;
	this->displayModel = NULL;
}

ModelManager::~ModelManager()
{
	if(this->displayModel != NULL)
		glmDelete(this->displayModel);
}

void ModelManager::startManaging()
{
	this->loadOBJModel(0);
}

void ModelManager::loadOBJModel(int index)
{
	if(this->model != NULL)
		free(this->model);

	// read an OBJ model here
	if(this->displayModel != NULL)
		glmDelete(this->displayModel);
	
	this->displayModel = glmReadOBJ((char*)this->modelNameList[index].c_str());
	printf("%s\n", this->modelNameList[index].c_str());

	// traverse the color model
	this->model = new Model();
	this->traverseColorModel(this->displayModel);

	// print object info
	printf("x=[%f, %f] dx=%f\n",
				this->model->minVal[0],
				this->model->maxVal[0],
				this->model->xLen);
	printf("y=[%f, %f] dy=%f\n",
				this->model->minVal[1],
				this->model->maxVal[1],
				this->model->yLen);
	printf("z=[%f, %f] dz=%f\n\n",
				this->model->minVal[2],
				this->model->maxVal[2],
				this->model->zLen);
}

void ModelManager::traverseColorModel(GLMmodel* OBJ)
{
	for(int i=1; i<=(int)OBJ->numvertices; ++i){
		this->model->maxVal[0] = max(this->model->maxVal[0], OBJ->vertices[i * 3 + 0]);
		this->model->maxVal[1] = max(this->model->maxVal[1], OBJ->vertices[i * 3 + 1]);
		this->model->maxVal[2] = max(this->model->maxVal[2], OBJ->vertices[i * 3 + 2]);
		this->model->minVal[0] = min(this->model->minVal[0], OBJ->vertices[i * 3 + 0]);
		this->model->minVal[1] = min(this->model->minVal[1], OBJ->vertices[i * 3 + 1]);
		this->model->minVal[2] = min(this->model->minVal[2], OBJ->vertices[i * 3 + 2]);
	}

	OBJ->position[0] = (this->model->maxVal[0] + this->model->minVal[0]) / 2;
	OBJ->position[1] = (this->model->maxVal[1] + this->model->minVal[1]) / 2;
	OBJ->position[2] = (this->model->maxVal[2] + this->model->minVal[2]) / 2;

	this->model->xLen = abs(this->model->maxVal[0] - this->model->minVal[0]);
	this->model->yLen = abs(this->model->maxVal[1] - this->model->minVal[1]);
	this->model->zLen = abs(this->model->maxVal[2] - this->model->minVal[2]);
	this->model->maxLen = max(this->model->xLen, max(this->model->yLen, this->model->zLen));
	this->model->scale = this->model->maxLen / 2;

	for(int i=1; i<=(int)OBJ->numvertices; ++i){
		OBJ->vertices[i * 3 + 0] -= OBJ->position[0];
		OBJ->vertices[i * 3 + 1] -= OBJ->position[1];
		OBJ->vertices[i * 3 + 2] -= OBJ->position[2];
		OBJ->vertices[i * 3 + 0] /= this->model->scale;
		OBJ->vertices[i * 3 + 1] /= this->model->scale;
		OBJ->vertices[i * 3 + 2] /= this->model->scale;
	}
	this->model->vertices = (GLfloat*) malloc(sizeof(GLfloat)* 9 * OBJ->numtriangles);
	this->model->colors   = (GLfloat*) malloc(sizeof(GLfloat)* 9 * OBJ->numtriangles);

	// traverse the triangles
	for(int i=0; i<(int)OBJ->numtriangles; ++i){
	 	// the index of each vertex
		int indv1 = OBJ->triangles[i].vindices[0];
		int indv2 = OBJ->triangles[i].vindices[1];
		int indv3 = OBJ->triangles[i].vindices[2];

	 	// the index of each color
	 	int indc1 = indv1;
	 	int indc2 = indv2;
	 	int indc3 = indv3;

	 	// vertices
		this->model->vertices[i * 9 + 0] = OBJ->vertices[indv1 * 3 + 0];
		this->model->vertices[i * 9 + 1] = OBJ->vertices[indv1 * 3 + 1];
		this->model->vertices[i * 9 + 2] = OBJ->vertices[indv1 * 3 + 2];

		this->model->vertices[i * 9 + 3] = OBJ->vertices[indv2 * 3 + 0];
		this->model->vertices[i * 9 + 4] = OBJ->vertices[indv2 * 3 + 1];
		this->model->vertices[i * 9 + 5] = OBJ->vertices[indv2 * 3 + 2];

		this->model->vertices[i * 9 + 6] = OBJ->vertices[indv3 * 3 + 0];
		this->model->vertices[i * 9 + 7] = OBJ->vertices[indv3 * 3 + 1];
		this->model->vertices[i * 9 + 8] = OBJ->vertices[indv3 * 3 + 2];

	 	// colors
		this->model->colors[i * 9 + 0] = OBJ->colors[indc1 * 3 + 0];
		this->model->colors[i * 9 + 1] = OBJ->colors[indc1 * 3 + 1];
		this->model->colors[i * 9 + 2] = OBJ->colors[indc1 * 3 + 2];

		this->model->colors[i * 9 + 3] = OBJ->colors[indc2 * 3 + 0];
		this->model->colors[i * 9 + 4] = OBJ->colors[indc2 * 3 + 1];
		this->model->colors[i * 9 + 5] = OBJ->colors[indc2 * 3 + 2];

		this->model->colors[i * 9 + 6] = OBJ->colors[indc3 * 3 + 0];
		this->model->colors[i * 9 + 7] = OBJ->colors[indc3 * 3 + 1];
		this->model->colors[i * 9 + 8] = OBJ->colors[indc3 * 3 + 2];
	 }
}

void ModelManager::traverseModelName(const char *pathName, int depth)
{
	// Data Type: struct dirent
	//     char d_name[]
	//     unsigned char d_type
	//         DT_UNKNOWN
	// 			The type is unknown. Only some filesystems have full support to return the type of the file, others might always return this value.
	//         DT_REG
	// 			A regular file.
	//         DT_DIR
	// 			A directory.
	//         DT_FIFO
	// 			A named pipe, or FIFO. See FIFO Special Files.
	//         DT_SOCK
	// 			A local-domain socket.
	//         DT_CHR
	// 			A character device.
	//         DT_BLK
	// 			A block device.
	//         DT_LNK
	// 			A symbolic link.

	DIR *dir;
	struct dirent *obj;

	if(!(dir = opendir(pathName))) return;
	
	while(obj = readdir(dir)){
		char path[1024];
		int len = sprintf(path, "%s/%s", pathName, obj->d_name);
		path[len] = '\0';

		if (obj->d_type == DT_DIR) {
			if (strcmp(obj->d_name, ".") == 0
			|| strcmp(obj->d_name, "..") == 0) continue;
			// printf("%*s[%s]\n", depth * 2, "", obj->d_name);
			this->traverseModelName(path, depth + 1);
		}
		else 
			this->modelNameList.push_back(path);
	}
	closedir(dir);
}