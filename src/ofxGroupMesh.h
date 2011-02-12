#pragma once

#include "ofMain.h"
#include "ofMesh.h"

class ofxGroup;
class ofxGroupMesh {
public:	
	ofxGroupMesh();
	void setup(ofxGroup* pGroup);
	void draw(polyMode mode);
	ofMesh& getMesh();
private:
	ofMesh mesh;
	ofxGroup* group;
};