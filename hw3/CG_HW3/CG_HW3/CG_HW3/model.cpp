#include "model.h"

Model::Model()
{
	for(int i=0; i<3; ++i){
		this->maxVal[i] = -FLT_MAX;
		this->minVal[i] = FLT_MAX;
	}
	this->xLen = this->yLen = this->zLen = this->maxLen = -FLT_MAX;
	this->tx = 0.0, this->ty = 0.0, this->tz = 0.0;
	this->sx = 1.0, this->sy = 1.0, this->sz = 1.0;
	this->rx = 0.0, this->ry = 0.0, this->rz = 0.0;
	this->eyeVec.set(0, 0, 0), this->centerVec.set(0, 0, -1), this->upVec.set(0, 1, 0);
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
Model::~Model()
{
	free(this->vertices);
	free(this->groups);
}

ModelManager::ModelManager(string path)
{
	this->path = path;
	this->displayMode = 0, this->controlMode = 0, this->projectionMode = 0;
	this->rotate = false;
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

void ModelManager::loadOBJModel(int index)
{
	if (this->model != NULL)
		free(this->model);

	// read an OBJ model here
	if (this->displayModel != NULL)
		glmDelete(this->displayModel);

	this->displayModel = glmReadOBJ((char*)this->modelNameList[index].c_str());
	printf("%s\n", this->modelNameList[index].c_str());

	// traverse the color model
	this->model = new Model();
	this->traverseColorModel(this->displayModel);

	// set normalization matrix
	this->setNormalizeMatrix();

	// print object info
	printf("x = [%.6f, %.6f] dx=%.6f\n",
		this->model->minVal[0],
		this->model->maxVal[0],
		this->model->xLen);
	printf("y = [%.6f, %.6f] dy=%.6f\n",
		this->model->minVal[1],
		this->model->maxVal[1],
		this->model->yLen);
	printf("z = [%.6f, %.6f] dz=%.6f\n\n",
		this->model->minVal[2],
		this->model->maxVal[2],
		this->model->zLen);
}

void ModelManager::startManaging()
{
	this->loadOBJModel(0);
	this->setLightingSource();
}

void ModelManager::showHelpMenu()
{
	puts("\n\n  ======   Help   Menu   ======\n"
	     "\n        h       /       H        - Show Help Menu"
	     "\n        c       /       C        - Clear Console"
	     "\n     z  Z  Left /    x  X  Right - Previous  / Next  Model"
	     "\n        w       /       W        - Wireframe / Fill  Mode"
	     "\n        t       /       T        - Start Translation Control"
	     "\n        s       /       S        - Start Scaling  Control"
		 "\n        r       /       T        - Switch Rotate Mode"
		 //"\n                r                - Start Rotation Control"
		 //"\n                R                - Switch Rotate Mode"
	     "\n        e       /       E        - Start Change Eye Mode"
	     "\n        p       /       P        - Parallel / Perspective Mode"
		 "\n                1                - Switch on / off Directional Light"
		 "\n                2                - Switch on / off Point Light"
		 "\n                3                - Switch on / off Spot Light"
		 "\n                4                - Switch Gouraud / Phong Shading"
		 "\n                5                - Start Move Directonal Light Mode"
		 "\n                6                - Start Move Point Light Mode"
		 "\n                7                - Start Move Spot Light Mode"
		 "\n                8                - Start Modify SpotEx Light Mode"
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

void ModelManager::traverseColorModel(GLMmodel* OBJ)
{
	this->model->groups = OBJ->groups;

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

	this->model->dx = OBJ->position[0];
	this->model->dy = OBJ->position[1];
	this->model->dz = OBJ->position[2];

	this->model->xLen = abs(this->model->maxVal[0] - this->model->minVal[0]);
	this->model->yLen = abs(this->model->maxVal[1] - this->model->minVal[1]);
	this->model->zLen = abs(this->model->maxVal[2] - this->model->minVal[2]);
	this->model->maxLen = max(this->model->xLen, max(this->model->yLen, this->model->zLen));
	this->model->scale = this->model->maxLen / 2;

	this->model->vertices = (GLfloat*) malloc(sizeof(GLfloat)* 9 * OBJ->numtriangles);
	// this->model->colors   = (GLfloat*) malloc(sizeof(GLfloat)* 9 * OBJ->numtriangles);

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
		// this->model->colors[i * 9 + 0] = OBJ->colors[indc1 * 3 + 0];
		// this->model->colors[i * 9 + 1] = OBJ->colors[indc1 * 3 + 1];
		// this->model->colors[i * 9 + 2] = OBJ->colors[indc1 * 3 + 2];

		// this->model->colors[i * 9 + 3] = OBJ->colors[indc2 * 3 + 0];
		// this->model->colors[i * 9 + 4] = OBJ->colors[indc2 * 3 + 1];
		// this->model->colors[i * 9 + 5] = OBJ->colors[indc2 * 3 + 2];

		// this->model->colors[i * 9 + 6] = OBJ->colors[indc3 * 3 + 0];
		// this->model->colors[i * 9 + 7] = OBJ->colors[indc3 * 3 + 1];
		// this->model->colors[i * 9 + 8] = OBJ->colors[indc3 * 3 + 2];
	 }
}

void ModelManager::setNormalizeMatrix()
{
	Matrix4 NT = Matrix4(
						1, 0, 0, -(this->model->dx),
						0, 1, 0, -(this->model->dy),
						0, 0, 1, -(this->model->dz),
						0, 0, 0, 1);
	Matrix4 NS = Matrix4(
						1/this->model->scale, 0, 0, 0,
						0, 1/this->model->scale, 0, 0,
						0, 0, 1/this->model->scale, 0,
						0, 0, 0, 1);
	this->model->N = NS * NT;
}

void ModelManager::setTranslationMatrix()
{
	this->model->T.set(
		1, 0, 0, this->model->tx,
		0, 1, 0, this->model->ty,
		0, 0, 1, this->model->tz,
		0, 0, 0, 1);
}

void ModelManager::setScalingMatrix()
{
	this->model->S.set(
		this->model->sx, 0, 0, 0,
		0, this->model->sy, 0, 0,
		0, 0, this->model->sz, 0,
		0, 0, 0, 1);
}

void ModelManager::setRotationMatrix()
{
	this->model->RX.set(
		1, 0, 0, 0,
		0, cos(this->model->rx), -sin(this->model->rx), 0,
		0, sin(this->model->rx),  cos(this->model->rx), 0,
		0, 0, 0, 1);
	this->model->RY.set(
		 cos(this->model->ry), 0, sin(this->model->ry), 0,
		0, 1, 0, 0,
		-sin(this->model->ry), 0, cos(this->model->ry), 0,
		0, 0, 0, 1);
	this->model->RZ.set(
		cos(this->model->rz), -sin(this->model->rz), 0, 0,
		sin(this->model->rz),  cos(this->model->rz), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	this->model->R = (this->model->RZ) * (this->model->RY) * (this->model->RX);
}

void ModelManager::setViewingMatrix()
{
	this->model->VT.set(
		1, 0, 0, -(this->model->eyeVec[0]),
		0, 1, 0, -(this->model->eyeVec[1]),
		0, 0, 1, -(this->model->eyeVec[2]),
		0, 0, 0, 1);
	Vector3 Rz = (this->model->centerVec - this->model->eyeVec).normalize();
	Vector3 Rx = (this->model->centerVec - this->model->eyeVec).cross(this->model->upVec - this->model->eyeVec).normalize();
	Vector3 Ry = Rx.cross(Rz);
	this->model->VR.set(
		 Rx[0],  Rx[1],  Rx[2], 0,
		 Ry[0],  Ry[1],  Ry[2], 0,
		-Rz[0], -Rz[1], -Rz[2], 0,
			 0,		 0,		 0, 1);
	this->model->VM = this->model->VR * this->model->VT;
	GLfloat eyeVec[3] = { this->model->eyeVec[0],
						  this->model->eyeVec[1],
						  this->model->eyeVec[2]};
	glUniform3fv(eyePos, 1, eyeVec);
}

void ModelManager::setProjectionMatrix(int projectionMode)
{
	if (!projectionMode){	// parallel
		P.set(
			1, 0,  0, 0,
			0, 1,  0, 0,
			0, 0, -1, 0,
			0, 0,  0, 1);
		V.set(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}
	else{	// perspective
		P.set(
			1, 0,  0,  0,
			0, 1,  0,  0,
			0, 0, -2, -3,
			0, 0, -1,  0);
		V.set(
			1, 0, 0,  0,
			0, 1, 0,  0,
			0, 0, 1, -2,
			0, 0, 0,  1);
	}
}

void ModelManager::setMVP()
{
	this->setTranslationMatrix();
	this->setScalingMatrix();
	this->setRotationMatrix();
	this->setViewingMatrix();
	this->setProjectionMatrix(this->projectionMode);
	this->model->MVP = P * V *(this->model->VM) * M * (this->model->T) * (this->model->S) * (this->model->R) * (this->model->N);

	// row-major ---> column-major
	this->model->mvp[0] = this->model->MVP[0];  this->model->mvp[4] = this->model->MVP[1];   this->model->mvp[8] = this->model->MVP[2];    this->model->mvp[12] = this->model->MVP[3];
	this->model->mvp[1] = this->model->MVP[4];  this->model->mvp[5] = this->model->MVP[5];   this->model->mvp[9] = this->model->MVP[6];    this->model->mvp[13] = this->model->MVP[7];
	this->model->mvp[2] = this->model->MVP[8];  this->model->mvp[6] = this->model->MVP[9];   this->model->mvp[10] = this->model->MVP[10];   this->model->mvp[14] = this->model->MVP[11];
	this->model->mvp[3] = this->model->MVP[12]; this->model->mvp[7] = this->model->MVP[13];  this->model->mvp[11] = this->model->MVP[14];   this->model->mvp[15] = this->model->MVP[15];

	// MN = (T * S * R) * N
	this->model->MN = M * (this->model->T) * (this->model->S) * (this->model->R) * (this->model->N);
	this->model->mn[0] = this->model->MN[0];  this->model->mn[4] = this->model->MN[1];   this->model->mn[8] = this->model->MN[2];    this->model->mn[12] = this->model->MN[3];
	this->model->mn[1] = this->model->MN[4];  this->model->mn[5] = this->model->MN[5];   this->model->mn[9] = this->model->MN[6];    this->model->mn[13] = this->model->MN[7];
	this->model->mn[2] = this->model->MN[8];  this->model->mn[6] = this->model->MN[9];   this->model->mn[10] = this->model->MN[10];   this->model->mn[14] = this->model->MN[11];
	this->model->mn[3] = this->model->MN[12]; this->model->mn[7] = this->model->MN[13];  this->model->mn[11] = this->model->MN[14];   this->model->mn[15] = this->model->MN[15];

	// VMN = V * (T * S * R) * N
	this->model->VMN = V *(this->model->VM) * M * (this->model->T) * (this->model->S) * (this->model->R) * (this->model->N);
	this->model->vmn[0] = this->model->VMN[0];  this->model->vmn[4] = this->model->VMN[1];   this->model->vmn[8] = this->model->VMN[2];    this->model->vmn[12] = this->model->VMN[3];
	this->model->vmn[1] = this->model->VMN[4];  this->model->vmn[5] = this->model->VMN[5];   this->model->vmn[9] = this->model->VMN[6];    this->model->vmn[13] = this->model->VMN[7];
	this->model->vmn[2] = this->model->VMN[8];  this->model->vmn[6] = this->model->VMN[9];   this->model->vmn[10] = this->model->VMN[10];   this->model->vmn[14] = this->model->VMN[11];
	this->model->vmn[3] = this->model->VMN[12]; this->model->vmn[7] = this->model->VMN[13];  this->model->vmn[11] = this->model->VMN[14];   this->model->vmn[15] = this->model->VMN[15];

	// V = VM = VT * VR
	this->model->v[0] = this->model->VM[0];  this->model->v[4] = this->model->VM[1];   this->model->v[8] = this->model->VM[2];    this->model->v[12] = this->model->VM[3];
	this->model->v[1] = this->model->VM[4];  this->model->v[5] = this->model->VM[5];   this->model->v[9] = this->model->VM[6];    this->model->v[13] = this->model->VM[7];
	this->model->v[2] = this->model->VM[8];  this->model->v[6] = this->model->VM[9];   this->model->v[10] = this->model->VM[10];   this->model->v[14] = this->model->VM[11];
	this->model->v[3] = this->model->VM[12]; this->model->v[7] = this->model->VM[13];  this->model->v[11] = this->model->VM[14];   this->model->v[15] = this->model->VM[15];
}

void::ModelManager::setLightingSource()
{
	//lightSource[0]: Directional Light (Parallel)
	this->lightSource[0].position[0] = 0;
	this->lightSource[0].position[1] = 0;
	this->lightSource[0].position[2] = 10;
	this->lightSource[0].position[3] = 0;

	this->lightSource[0].ambient[0] = 0.5;
	this->lightSource[0].ambient[1] = 0.5;
	this->lightSource[0].ambient[2] = 0.5;
	this->lightSource[0].ambient[3] = 1;

	this->lightSource[0].diffuse[0] = 1;
	this->lightSource[0].diffuse[1] = 1;
	this->lightSource[0].diffuse[2] = 1;
	this->lightSource[0].diffuse[3] = 1;

	this->lightSource[0].specular[0] = 1;
	this->lightSource[0].specular[1] = 1;
	this->lightSource[0].specular[2] = 1;
	this->lightSource[0].specular[3] = 1;

	this->lightSource[0].constantAttenuation = 1;
	this->lightSource[0].spotCutoff = 180;

	//lightSource[1]: Point Lihgt
	this->lightSource[1].position[0] = 0;
	this->lightSource[1].position[1] = 0;
	this->lightSource[1].position[2] = 20;
	this->lightSource[1].position[3] = 1;

	this->lightSource[1].ambient[0] = 0.5;
	this->lightSource[1].ambient[1] = 0.5;
	this->lightSource[1].ambient[2] = 0.5;
	this->lightSource[1].ambient[3] = 1;

	this->lightSource[1].diffuse[0] = 1;
	this->lightSource[1].diffuse[1] = 1;
	this->lightSource[1].diffuse[2] = 1;
	this->lightSource[1].diffuse[3] = 1;

	this->lightSource[1].specular[0] = 1;
	this->lightSource[1].specular[1] = 1;
	this->lightSource[1].specular[2] = 1;
	this->lightSource[1].specular[3] = 1;

	this->lightSource[1].constantAttenuation = 0;
	this->lightSource[1].linearAttenuation = 0.02;
	this->lightSource[1].quadraticAttenuation = 0.001;
	this->lightSource[1].spotCutoff = 180;

	//lightSource[2]: Spot Light
	this->lightSource[2].position[0] = 0;
	this->lightSource[2].position[1] = 0;
	this->lightSource[2].position[2] = 20;
	this->lightSource[2].position[3] = 1;

	this->lightSource[2].ambient[0] = 0.5;
	this->lightSource[2].ambient[1] = 0.5;
	this->lightSource[2].ambient[2] = 0.5;
	this->lightSource[2].ambient[3] = 1;

	this->lightSource[2].diffuse[0] = 1;
	this->lightSource[2].diffuse[1] = 1;
	this->lightSource[2].diffuse[2] = 1;
	this->lightSource[2].diffuse[3] = 1;

	this->lightSource[2].specular[0] = 1;
	this->lightSource[2].specular[1] = 1;
	this->lightSource[2].specular[2] = 1;
	this->lightSource[2].specular[3] = 1;

	this->lightSource[2].spotDirection[0] = 0;
	this->lightSource[2].spotDirection[1] = 0;
	this->lightSource[2].spotDirection[2] = -1;
	this->lightSource[2].spotDirection[3] = 0;

	this->lightSource[2].spotExponent = 1;

	this->lightSource[2].constantAttenuation = 0;
	this->lightSource[2].linearAttenuation = 0.02;
	this->lightSource[2].quadraticAttenuation = 0.001;
	this->lightSource[2].spotCutoff = 1;
}

void::ModelManager::updateModelGroup()
{
	GLfloat triangle_normals[9];
	GLfloat triangle_vertex[9];
	GLfloat* ambient;
	GLfloat* diffuse;
	GLfloat* specular;
	GLfloat shininess;

	GLMgroup* mGroup = this->displayModel->groups;
	while (mGroup){
		ambient = this->displayModel->materials[mGroup->material].ambient;
		diffuse = this->displayModel->materials[mGroup->material].diffuse;
		specular = this->displayModel->materials[mGroup->material].specular;
		shininess = this->displayModel->materials[mGroup->material].shininess;
		for (int i = 0; i < (int)mGroup->numtriangles; i++){
			int triangleID = mGroup->triangles[i];

			// the index of each vertex
			int indv1 = this->displayModel->triangles[triangleID].vindices[0];
			int indv2 = this->displayModel->triangles[triangleID].vindices[1];
			int indv3 = this->displayModel->triangles[triangleID].vindices[2];

			// the index of each color
			int indn1 = this->displayModel->triangles[triangleID].nindices[0];
			int indn2 = this->displayModel->triangles[triangleID].nindices[1];
			int indn3 = this->displayModel->triangles[triangleID].nindices[2];

			// vertices
			triangle_vertex[0] = this->displayModel->vertices[indv1 * 3 + 0];
			triangle_vertex[1] = this->displayModel->vertices[indv1 * 3 + 1];
			triangle_vertex[2] = this->displayModel->vertices[indv1 * 3 + 2];

			triangle_vertex[3] = this->displayModel->vertices[indv2 * 3 + 0];
			triangle_vertex[4] = this->displayModel->vertices[indv2 * 3 + 1];
			triangle_vertex[5] = this->displayModel->vertices[indv2 * 3 + 2];

			triangle_vertex[6] = this->displayModel->vertices[indv3 * 3 + 0];
			triangle_vertex[7] = this->displayModel->vertices[indv3 * 3 + 1];
			triangle_vertex[8] = this->displayModel->vertices[indv3 * 3 + 2];

			triangle_normals[0] = this->displayModel->normals[indn1 * 3 + 0];
			triangle_normals[1] = this->displayModel->normals[indn1 * 3 + 1];
			triangle_normals[2] = this->displayModel->normals[indn1 * 3 + 2];

			triangle_normals[3] = this->displayModel->normals[indn2 * 3 + 0];
			triangle_normals[4] = this->displayModel->normals[indn2 * 3 + 1];
			triangle_normals[5] = this->displayModel->normals[indn2 * 3 + 2];

			triangle_normals[6] = this->displayModel->normals[indn3 * 3 + 0];
			triangle_normals[7] = this->displayModel->normals[indn3 * 3 + 1];
			triangle_normals[8] = this->displayModel->normals[indn3 * 3 + 2];

			// TODO:
			//// Please define the model transformation matrix, viewing transformation matrix, 
			//// projection transformation matrix

			//pass model material value to the shader
			glUniform4fv(iLocMAmbient,  1, ambient);
			glUniform4fv(iLocMDiffuse,  1, diffuse);
			glUniform4fv(iLocMSpecular, 1, specular);
			glUniform1f (iLocMShininess, shininess);

			// bind array pointers to shader
			glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, triangle_vertex);
			glVertexAttribPointer(iLocNormal,   3, GL_FLOAT, GL_FALSE, 0, triangle_normals);

			// bind uniform matrix to shader
			glUniformMatrix4fv(iLocMVP, 1, GL_FALSE, this->model->mvp);
			glUniformMatrix4fv(iLocVMN, 1, GL_FALSE, this->model->vmn);
			glUniformMatrix4fv(iLocMN,  1, GL_FALSE, this->model->mn);
			glUniformMatrix4fv(iLocV,   1, GL_FALSE, this->model->v);

			glUniform4fv(iLocLType, 1, lightType);

			// draw the array we just bound
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		mGroup = mGroup->next;
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
		else{
			if (((string)path).find(".mtl") == std::string::npos)
				this->modelNameList.push_back(path);
		}
	}
	closedir(dir);
}