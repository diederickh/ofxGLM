#pragma once
#include "ofMain.h"
#include "ofxGLMConfig.h"
#include "ofxGLMMaterial.h"
#include "glm.h"

struct ofxGLMColor {
	ofxGLMColor(float rr, float gg, float bb, float aa)
		:r(rr)
		,g(gg)
		,b(bb)
		,a(aa)
	{
	}
	float r,g,b,a;
};

// A ofxGroup is a wrapper around a GLMgroup 
class ofxGLMGroup {
public:
	ofxGLMGroup(GLMmodel* pModel, GLMgroup* pGroup);
	string getName();
	
	bool hasName();
	bool hasVertices();
	bool hasNormals();
	bool hasTexCoords();
	bool hasColors();
	
	int getNumVertices();
	int getNumNormals();
	int getNumTexCoords();
	int getNumColors();
				
	vector<ofVec3f>& getVertices();
	vector<ofVec3f>& getNormals();
	vector<ofVec2f>& getTexCoords();
	vector<ofxGLMColor>& getColors();
	
	GLMgroup* getGLMGroup();
	GLMmodel* getGLMModel();
	
	int getMaterialIndex();
	
private:
	int material_index;
	vector<ofVec3f> vertices;
	vector<ofVec3f> normals;
	vector<ofVec2f> texcoords;
	vector<ofxGLMColor> colors;
	vector<int> indices;
	
	string name;
	GLMmodel* model;
	GLMgroup* group;

};