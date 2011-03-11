#pragma once
#include "ofMain.h"
#include "ofxGLMConfig.h"
#include "ofxGLMMaterial.h"
#include "glm.h"


// A ofxGroup is a wrapper around a GLMgroup 
class ofxGLMGroup {
public:
	ofxGLMGroup(GLMmodel* pModel, GLMgroup* pGroup, ofxGLMMaterial* pMaterial);
	string getName();
	
	bool hasVertices();
	bool hasNormals();
	bool hasTexCoords();
	bool hasColors();
		
	vector<ofVec3f>& getVertices();
	vector<ofVec3f>& getNormals();
	vector<ofVec2f>& getTexCoords();
	vector<ofxGLMColor>& getColors();
	
	GLMgroup* getGLMGroup();
	GLMmodel* getGLMModel();
private:
	vector<ofVec3f> vertices;
	vector<ofVec3f> normals;
	vector<ofVec2f> texcoords;
	vector<ofxGLMColor> colors;
	vector<int> indices;
	
	string name;
	GLMmodel* model;
	GLMgroup* group;

};