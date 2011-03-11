#include "ofxGLMGroup.h"
#define T(x) (model->triangles[(x)])

ofxGLMGroup::ofxGLMGroup(GLMmodel* pModel, GLMgroup* pGroup, ofxGLMMaterial* pMaterial)
:model(pModel)
,group(pGroup)
,name(pGroup->name)
{
	int i,j;
	GLMtriangle* triangle;
  
	// diffuse color
	ofColor c(255,255,255,255);
	
	if(pMaterial != NULL) {
		//	c = pMaterial->getDiffuseColor();
		//	mesh_node.addMaterial(pMaterial);
	}
	
	for(int i = 0; i < group->numtriangles; ++i) {
		triangle = &T(group->triangles[i]);

		for(int j = 0; j < 3; ++j) {
			if (triangle->nindices[j] != -1) {
				GLfloat* np = &model->normals[3 * triangle->nindices[j]];
				ofVec3f n(*np, *(np+1), *(np+2));
				normals.push_back(n);
			}
			
			if (triangle->tindices[j] != -1) {
				GLfloat* tp = &model->texcoords[2 * triangle->tindices[j]];
				ofVec2f tc(*tp, *(tp+1));
				texcoords.push_back(tc);
			}
			
			// vertex
			GLfloat* vp = &model->vertices[3 * triangle->vindices[j]];		
			ofVec3f v(*vp, *(vp+1), *(vp+2));
			vertices.push_back(v);


			// TODO: implement colors
		}
	}
}

// check if we've got has vertices.
bool ofxGLMGroup::hasVertices() {
	return vertices.size() > 0;
}

// check if we've got normals.
bool ofxGLMGroup::hasNormals() {
	return normals.size() > 0;
}

// check if we've got texture coords.
bool ofxGLMGroup::hasTexCoords() {  
	return texcoords.size() > 0;
}

// check if we've got colors
bool ofxGLMGroup::hasColors() {
	return colors.size() > 0;
}

// get vertices.
vector<ofVec3f>& ofxGLMGroup::getVertices() {
	return vertices;
}

// get normals
vector<ofVec3f>& ofxGLMGroup::getNormals() {
	return normals;
}

// get texcoords
vector<ofVec2f>& ofxGLMGroup::getTexCoords() {
	return texcoords;
}

// get colors
vector<ofxGLMColor>& ofxGLMGroup::getColors() {
	return colors;
}
	


string ofxGLMGroup::getName() {
	return name;
}

/*
ofMesh* ofxGLMGroup::getMesh() {
	return &mesh;
}
*/
/*
ofMeshNode* ofxGLMGroup::getMeshNode() {
	return &mesh_node;
}
*/

GLMgroup* ofxGLMGroup::getGLMGroup() {
	return group;
}

GLMmodel* ofxGLMGroup::getGLMModel() {
	return model;
}