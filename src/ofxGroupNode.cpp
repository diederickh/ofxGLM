#include "ofxGroupNode.h"
#include "ofMesh.h"
#include "ofxGroupMesh.h"
#include "ofxGroup.h"

ofxGroupNode::ofxGroupNode() 
:group(NULL)
{
	gmesh = new ofxGroupMesh();
}

ofxGroupNode::ofxGroupNode(ofxGroup* pGroup) 
:group(pGroup)
{
	::ofxGroupNode();
	setGroup(group);
}

ofxGroupNode::~ofxGroupNode() {
	delete gmesh;
}

void ofxGroupNode::setGroup(ofxGroup* pGroup) {
	if(pGroup != NULL) {
		group = pGroup;
		gmesh->setup(pGroup);
	}
}

void ofxGroupNode::customDraw() {
	ofBox(10);
	ofDrawAxis(30);
	if(group != NULL) {
		GLMgroup* g = group->getGLMGroup();
		GLMmodel* model = group->getGLMModel();
		GLMmaterial* m = &model->materials[g->material];
		int i = 0;
	}
	gmesh->draw(OF_MESH_FILL);
}