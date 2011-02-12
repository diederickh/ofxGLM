#include "ofxGroupMesh.h"
#include "ofxGroup.h"

ofxGroupMesh::ofxGroupMesh() {
}

void ofxGroupMesh::setup(ofxGroup* pGroup) {
	group = pGroup;
	mesh.setVertexData(group->getVertexData());
	mesh.enableColors();
	//mesh.setupVertexArray();
}

ofMesh& ofxGroupMesh::getMesh() {
	return mesh;
}

void ofxGroupMesh::draw(polyMode nMode) {
	mesh.draw(nMode);
}
