#include "model.h"

BonusModel::BonusModel()
{
	for(int i=0; i<3; ++i){
		this->maxVal[i] = -FLT_MAX;
		this->minVal[i] = FLT_MAX;
	}
	this->minLen = FLT_MAX, this->xLen = this->yLen = this->zLen = this->maxLen = -FLT_MAX;
	this->tx = 0.0, this->ty = 0.0, this->tz = 0.0;
	this->sx = 1.0, this->sy = 1.0, this->sz = 1.0;
	this->rx = 0.0, this->ry = 0.0, this->rz = 0.0;
	this->T.set(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	this->S.set(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	this->R.set(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	this->N.set(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	this->RX.set(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	this->RY.set(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	this->RZ.set(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}
BonusModel::~BonusModel()
{
	free(this->vertices);
	free(this->colors);
}

ModelManager::ModelManager(string path)
{
	this->path = path;
	this->displayMode = 0, this->controlMode = 0, this->projectionMode = 0;
	this->traverseBonusModelName(path.c_str(), 0);
	this->displayIndex = 0;
	this->size = bonusModelNameList.size();
	this->eyeVec.set(0, 0, 0), this->centerVec.set(0, 0, -1), this->upVec.set(0, 1, 0);
	for (int i = 0; i < 5; ++i){
		this->bonusModelList[i] = NULL;
		this->displayBonusModel[i] = NULL;
	}
}

ModelManager::~ModelManager()
{
	for (int i = 0; i < 5; ++i){
		if (this->displayBonusModel[i] != NULL)
			glmDelete(this->displayBonusModel[i]);
	}
}
void ModelManager::showObjectInfo(int index)
{
	printf("%s\n", this->bonusModelNameList[index].c_str());

	// print object info
	printf("x = [%.6f, %.6f] dx=%.6f\n",
		this->bonusModelList[index]->minVal[0],
		this->bonusModelList[index]->maxVal[0],
		this->bonusModelList[index]->xLen);
	printf("y = [%.6f, %.6f] dy=%.6f\n",
		this->bonusModelList[index]->minVal[1],
		this->bonusModelList[index]->maxVal[1],
		this->bonusModelList[index]->yLen);
	printf("z = [%.6f, %.6f] dz=%.6f\n\n",
		this->bonusModelList[index]->minVal[2],
		this->bonusModelList[index]->maxVal[2],
		this->bonusModelList[index]->zLen);
}
void ModelManager::showHelpMenu()
{
	puts("\n\n  ======   Help   Menu   ======\n"
	     "\n        h       /       H        - Show Help Menu"
	     "\n        c       /       C        - Clear Console"
	     "\n     z  Z  Left /    x  X  Right - Previous  / Next  Model"
	     "\n        w       /       W        - Wireframe / Fill  Mode"
	     "\n        t       /       T        - Start Translation Mode"
	     "\n        s       /       S        - Start Scaling  Mode"
	     "\n        r       /       R        - Start Rotation Mode"
	     "\n        e       /       E        - Start Change Eye Mode"
	     "\n        p       /       P        - Parallel / Perspective Mode"
	     "\n               Esc               - Exit Program\n");
}

void ModelManager::showTranslationMenu()
{
	puts("        l       /       L     - X  UP"
		 "\n        j       /       J     - X Down"
		 "\n        i       /       I     - Y  UP"
		 "\n        k       /       K     - Y Down"
		 "\n        m       /       M     - Y  UP"
		 "\n        o       /       O     - Y Down");
}

void ModelManager::showScalingMenu()
{
	puts("        l       /       L     - X-dir  UP"
		"\n        j       /       J     - X-dir Down"
		"\n        i       /       I     - Y-dir  UP"
		"\n        k       /       K     - Y-dir Down"
		"\n        m       /       M     - Z-dir  UP"
		"\n        o       /       O     - Z-dir Down");
}

void ModelManager::showRotationMenu()
{
	puts("        l       /       L     - X-theta  UP"
		"\n        j       /       J     - X-theta Down"
		"\n        i       /       I     - Y-theta  UP"
		"\n        k       /       K     - Y-theta Down"
		"\n        m       /       M     - Z-theta  UP"
		"\n        o       /       O     - Z-theta Down");
}

void ModelManager::showEyeMenu()
{
	puts("        l       /       L     - X-eye  UP"
		"\n        j       /       J     - X-eye Down"
		"\n        i       /       I     - Y-eye  UP"
		"\n        k       /       K     - Y-eye Down"
		"\n        m       /       M     - Z-eye  UP"
		"\n        o       /       O     - Z-eye Down");
}

void ModelManager::startBonusManaging()
{
	for (int i = 0; i < 5; ++i)
		this->loadBonusModel(i);
	this->showObjectInfo(this->displayIndex);
}

void ModelManager::loadBonusModel(int index)
{
	this->displayBonusModel[index] = glmReadOBJ((char*)this->bonusModelNameList[index].c_str());
	
	// traverse the color model
	this->bonusModelList[index] = new BonusModel();
	this->traverseBonusColorModel(this->displayBonusModel[index], index);

	// set normalization matrix
	this->setBonusNormalizeMatrix(index);

	// print object info
	// this->showObjectInfo(index);
}

void ModelManager::traverseBonusColorModel(GLMmodel* OBJ, int index)
{
	GLfloat originList[5][3] = {
		{ 0, 0, 0 },
		{ 1.5, 1.5, 0 },
		{ 1.5, -1.5, 0 },
		{ -2, 2, 0 },
		{ -1.85, -1.85, 0 } };
	for (int i = 1; i <= (int)OBJ->numvertices; ++i){
		this->bonusModelList[index]->maxVal[0] = max(this->bonusModelList[index]->maxVal[0], OBJ->vertices[i * 3 + 0]);
		this->bonusModelList[index]->maxVal[1] = max(this->bonusModelList[index]->maxVal[1], OBJ->vertices[i * 3 + 1]);
		this->bonusModelList[index]->maxVal[2] = max(this->bonusModelList[index]->maxVal[2], OBJ->vertices[i * 3 + 2]);
		this->bonusModelList[index]->minVal[0] = min(this->bonusModelList[index]->minVal[0], OBJ->vertices[i * 3 + 0]);
		this->bonusModelList[index]->minVal[1] = min(this->bonusModelList[index]->minVal[1], OBJ->vertices[i * 3 + 1]);
		this->bonusModelList[index]->minVal[2] = min(this->bonusModelList[index]->minVal[2], OBJ->vertices[i * 3 + 2]);
	}
	OBJ->position[0] = (this->bonusModelList[index]->maxVal[0] + this->bonusModelList[index]->minVal[0]) / 2;
	OBJ->position[1] = (this->bonusModelList[index]->maxVal[1] + this->bonusModelList[index]->minVal[1]) / 2;
	OBJ->position[2] = (this->bonusModelList[index]->maxVal[2] + this->bonusModelList[index]->minVal[2]) / 2;

	this->bonusModelList[index]->xLen = abs(this->bonusModelList[index]->maxVal[0] - this->bonusModelList[index]->minVal[0]);
	this->bonusModelList[index]->yLen = abs(this->bonusModelList[index]->maxVal[1] - this->bonusModelList[index]->minVal[1]);
	this->bonusModelList[index]->zLen = abs(this->bonusModelList[index]->maxVal[2] - this->bonusModelList[index]->minVal[2]);
	this->bonusModelList[index]->maxLen = max(this->bonusModelList[index]->xLen, max(this->bonusModelList[index]->yLen, this->bonusModelList[index]->zLen));
	this->bonusModelList[index]->minLen = min(this->bonusModelList[index]->xLen, min(this->bonusModelList[index]->yLen, this->bonusModelList[index]->zLen));
	this->bonusModelList[index]->scale = this->bonusModelList[index]->maxLen / 0.5;

	GLfloat factor = (this->bonusModelList[index]->maxLen + this->bonusModelList[index]->minLen) / 2;
	this->bonusModelList[index]->dx = OBJ->position[0] + originList[index][0]*factor;
	this->bonusModelList[index]->dy = OBJ->position[1] + originList[index][1]*factor;
	this->bonusModelList[index]->dz = OBJ->position[2] + originList[index][2]*factor;

	this->bonusModelList[index]->vertices = (GLfloat*)malloc(sizeof(GLfloat)* 9 * OBJ->numtriangles);
	this->bonusModelList[index]->colors = (GLfloat*)malloc(sizeof(GLfloat)* 9 * OBJ->numtriangles);

	// traverse the triangles
	for (int i = 0; i < (int)OBJ->numtriangles; ++i){
		// the index of each vertex
		int indv1 = OBJ->triangles[i].vindices[0];
		int indv2 = OBJ->triangles[i].vindices[1];
		int indv3 = OBJ->triangles[i].vindices[2];

		// the index of each color
		int indc1 = indv1;
		int indc2 = indv2;
		int indc3 = indv3;

		// vertices
		this->bonusModelList[index]->vertices[i * 9 + 0] = OBJ->vertices[indv1 * 3 + 0];
		this->bonusModelList[index]->vertices[i * 9 + 1] = OBJ->vertices[indv1 * 3 + 1];
		this->bonusModelList[index]->vertices[i * 9 + 2] = OBJ->vertices[indv1 * 3 + 2];

		this->bonusModelList[index]->vertices[i * 9 + 3] = OBJ->vertices[indv2 * 3 + 0];
		this->bonusModelList[index]->vertices[i * 9 + 4] = OBJ->vertices[indv2 * 3 + 1];
		this->bonusModelList[index]->vertices[i * 9 + 5] = OBJ->vertices[indv2 * 3 + 2];

		this->bonusModelList[index]->vertices[i * 9 + 6] = OBJ->vertices[indv3 * 3 + 0];
		this->bonusModelList[index]->vertices[i * 9 + 7] = OBJ->vertices[indv3 * 3 + 1];
		this->bonusModelList[index]->vertices[i * 9 + 8] = OBJ->vertices[indv3 * 3 + 2];

		// colors
		this->bonusModelList[index]->colors[i * 9 + 0] = OBJ->colors[indc1 * 3 + 0];
		this->bonusModelList[index]->colors[i * 9 + 1] = OBJ->colors[indc1 * 3 + 1];
		this->bonusModelList[index]->colors[i * 9 + 2] = OBJ->colors[indc1 * 3 + 2];

		this->bonusModelList[index]->colors[i * 9 + 3] = OBJ->colors[indc2 * 3 + 0];
		this->bonusModelList[index]->colors[i * 9 + 4] = OBJ->colors[indc2 * 3 + 1];
		this->bonusModelList[index]->colors[i * 9 + 5] = OBJ->colors[indc2 * 3 + 2];

		this->bonusModelList[index]->colors[i * 9 + 6] = OBJ->colors[indc3 * 3 + 0];
		this->bonusModelList[index]->colors[i * 9 + 7] = OBJ->colors[indc3 * 3 + 1];
		this->bonusModelList[index]->colors[i * 9 + 8] = OBJ->colors[indc3 * 3 + 2];
	}
}

void ModelManager::setBonusNormalizeMatrix(int index)
{
	Matrix4 NT = Matrix4(
		1, 0, 0, -(this->bonusModelList[index]->dx),
		0, 1, 0, -(this->bonusModelList[index]->dy),
		0, 0, 1, -(this->bonusModelList[index]->dz),
		0, 0, 0, 1);
	Matrix4 NS = Matrix4(
		1 / this->bonusModelList[index]->scale, 0, 0, 0,
		0, 1 / this->bonusModelList[index]->scale, 0, 0,
		0, 0, 1 / this->bonusModelList[index]->scale, 0,
		0, 0, 0, 1);
	this->bonusModelList[index]->N = NS * NT;
}

void ModelManager::setBonusTranslationMatrix(int index)
{
	this->bonusModelList[index]->T.set(
		1, 0, 0, this->bonusModelList[index]->tx,
		0, 1, 0, this->bonusModelList[index]->ty,
		0, 0, 1, this->bonusModelList[index]->tz,
		0, 0, 0, 1);
}

void ModelManager::setBonusScalingMatrix(int index)
{
	this->bonusModelList[index]->S.set(
		this->bonusModelList[index]->sx, 0, 0, 0,
		0, this->bonusModelList[index]->sy, 0, 0,
		0, 0, this->bonusModelList[index]->sz, 0,
		0, 0, 0, 1);
}

void ModelManager::setBonusRotationMatrix(int index)
{
	this->bonusModelList[index]->RX.set(
		1, 0, 0, 0,
		0, cos(this->bonusModelList[index]->rx), -sin(this->bonusModelList[index]->rx), 0,
		0, sin(this->bonusModelList[index]->rx), cos(this->bonusModelList[index]->rx), 0,
		0, 0, 0, 1);
	this->bonusModelList[index]->RY.set(
		cos(this->bonusModelList[index]->ry), 0, sin(this->bonusModelList[index]->ry), 0,
		0, 1, 0, 0,
		-sin(this->bonusModelList[index]->ry), 0, cos(this->bonusModelList[index]->ry), 0,
		0, 0, 0, 1);
	this->bonusModelList[index]->RZ.set(
		cos(this->bonusModelList[index]->rz), -sin(this->bonusModelList[index]->rz), 0, 0,
		sin(this->bonusModelList[index]->rz), cos(this->bonusModelList[index]->rz), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	this->bonusModelList[index]->R = (this->bonusModelList[index]->RZ) * (this->bonusModelList[index]->RY) * (this->bonusModelList[index]->RX);
}

void ModelManager::setBonusViewingMatrix()
{
	this->VT.set(
		1, 0, 0, -(this->eyeVec[0]),
		0, 1, 0, -(this->eyeVec[1]),
		0, 0, 1, -(this->eyeVec[2]),
		0, 0, 0, 1);
	Vector3 Rz = (this->centerVec - this->eyeVec).normalize();
	Vector3 Rx = (this->centerVec - this->eyeVec).cross(this->upVec - this->eyeVec).normalize();
	Vector3 Ry = Rx.cross(Rz);
	this->VR.set(
		Rx[0], Rx[1], Rx[2], 0,
		Ry[0], Ry[1], Ry[2], 0,
		-Rz[0], -Rz[1], -Rz[2], 0,
		0, 0, 0, 1);
	this->VM = this->VR * this->VT;
}

void ModelManager::setBonusProjectionMatrix(int projectionMode)
{
	if (!projectionMode){	// parallel
		P.set(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, -1, 0,
			0, 0, 0, 1);
		V.set(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}
	else{	// perspective
		P.set(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, -2, -3,
			0, 0, -1, 0);
		V.set(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, -2,
			0, 0, 0, 1);
	}
}

void ModelManager::setBonusMVP(int index)
{
	this->setBonusTranslationMatrix(index);
	this->setBonusScalingMatrix(index);
	this->setBonusRotationMatrix(index);
	this->setBonusViewingMatrix();
	this->setBonusProjectionMatrix(this->projectionMode);
	this->bonusModelList[index]->MVP = P * V *(this->VM) * M * (this->bonusModelList[index]->T) * (this->bonusModelList[index]->S) * (this->bonusModelList[index]->R) * (this->bonusModelList[index]->N);

	// row-major ---> column-major
	this->bonusModelList[index]->mvp[0] = this->bonusModelList[index]->MVP[0];  this->bonusModelList[index]->mvp[4] = this->bonusModelList[index]->MVP[1];   this->bonusModelList[index]->mvp[8] = this->bonusModelList[index]->MVP[2];    this->bonusModelList[index]->mvp[12] = this->bonusModelList[index]->MVP[3];
	this->bonusModelList[index]->mvp[1] = this->bonusModelList[index]->MVP[4];  this->bonusModelList[index]->mvp[5] = this->bonusModelList[index]->MVP[5];   this->bonusModelList[index]->mvp[9] = this->bonusModelList[index]->MVP[6];    this->bonusModelList[index]->mvp[13] = this->bonusModelList[index]->MVP[7];
	this->bonusModelList[index]->mvp[2] = this->bonusModelList[index]->MVP[8];  this->bonusModelList[index]->mvp[6] = this->bonusModelList[index]->MVP[9];   this->bonusModelList[index]->mvp[10] = this->bonusModelList[index]->MVP[10];   this->bonusModelList[index]->mvp[14] = this->bonusModelList[index]->MVP[11];
	this->bonusModelList[index]->mvp[3] = this->bonusModelList[index]->MVP[12]; this->bonusModelList[index]->mvp[7] = this->bonusModelList[index]->MVP[13];  this->bonusModelList[index]->mvp[11] = this->bonusModelList[index]->MVP[14];   this->bonusModelList[index]->mvp[15] = this->bonusModelList[index]->MVP[15];
}

void ModelManager::traverseBonusModelName(const char *pathName, int depth)
{
	DIR *dir;
	struct dirent *obj;

	if (!(dir = opendir(pathName))) return;

	while (obj = readdir(dir)){
		char path[1024];
		int len = sprintf(path, "%s/%s", pathName, obj->d_name);
		path[len] = '\0';

		if (obj->d_type == DT_DIR) {
			if (strcmp(obj->d_name, ".") == 0
				|| strcmp(obj->d_name, "..") == 0) continue;
			// printf("%*s[%s]\n", depth * 2, "", obj->d_name);
			this->traverseBonusModelName(path, depth + 1);
		}
		else
			this->bonusModelNameList.push_back(path);
	}
	closedir(dir);
}