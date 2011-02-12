#pragma once
#include "ofMain.h"

class ofxGroup;
class ofxGroupMesh;

class ofxGroupNode : public ofNode {
public:
	ofxGroupNode();
	ofxGroupNode(ofxGroup* pGroup);
	~ofxGroupNode();
	void setGroup(ofxGroup* pGroup);
	virtual void customDraw();
	
private:
	ofxGroup* group;
	ofxGroupMesh* gmesh;
};
