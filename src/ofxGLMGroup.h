#pragma once
#include "ofMain.h"
#include "ofxGLMConfig.h"
#include "glm.h"


// A ofxGroup is a wrapper around a GLMgroup 
class ofxGLMGroup {
public:
	ofxGLMGroup(GLMmodel* pModel, GLMgroup* pGroup);
	ofVertexData* getVertexData();
	string getName();
	
	ofMesh* getMesh();
	ofMeshNode* getMeshNode();
	
	GLMgroup* getGLMGroup();
	GLMmodel* getGLMModel();
private:
	ofMesh mesh;
	ofMeshNode mesh_node;
	ofVertexData vertex_data;
	
	string name;
	GLMmodel* model;
	GLMgroup* group;

};