#include "ofxGLM.h"

ofxGLM::ofxGLM() 
:model(NULL)
,render_mode(GLM_NONE)
{
}

bool ofxGLM::load(string sFile, float nScale, bool bNormalize) {
	char* filename = (char*)ofToDataPath(sFile, true).c_str();
	model = glmReadOBJ(filename);
	if(!model) {
		ofLog(OF_LOG_ERROR, "Could not load model: %s", sFile.c_str());
		return false;
	}
	if(bNormalize) {
		normalize();
	}
	if(nScale != -1.0) {
		scale(nScale);
	}
	
	createMaterials();
	createGroups();
	return true;
}

void ofxGLM::createGroups() {
	GLMgroup* group = model->groups;
	while(group) {	
		//ofxGLMMaterial* mat = getMaterial(group->material);
		
		// store named group.
		ofxGLMGroup* vg = new ofxGLMGroup(model, group);
		named_groups.insert(ofxGLMNamedGroupPair(vg->getName(), vg));
		
		// and indexed group (not sure if map is necessary.. but if material indices are not incremental it does matter)
		groups.insert(ofxGLMGroupPair(group->material, vg));
		group = group->next;
	}
}

void ofxGLM::createMaterials() {
	for(int i = 0; i < model->nummaterials; ++i) {
		ofxGLMMaterial* mat = new ofxGLMMaterial();
		GLMmaterial* glm_mat = &model->materials[i];
		mat->setGLMMaterial(i, glm_mat, model);
		materials.insert(ofxGLMMaterialPair(i,mat));
		cout << "Created material i:" << i << endl;
	}
}

ofxGLMMaterial* ofxGLM::getMaterial(int nIndex) {
	ofxGLMMaterials::iterator it = materials.find(nIndex);
	if(it == materials.end()) {
		return NULL;
	}
	else {	
		return it->second;
	}
}
/*
ofMesh* ofxGLM::getGroupMesh(string sName) {
	ofxGLMGroup* group = getGroup(sName);
	if(group != NULL) {
		return group->getMesh();
	}
	return NULL;
}

ofMeshNode* ofxGLM::getGroupMeshNode(string sName) {
	ofxGLMGroup* group = getGroup(sName);
	if(group != NULL) {
		return group->getMeshNode();
	}
	return NULL;
}
*/

ofxGLM& ofxGLM::listGroups() {
	ofxGLMGroups::iterator it = groups.begin();
	while(it != groups.end()) {
		std::cout << "Group: '" << it->second->getName() << "'" << std::endl;
		++it;
	}
}

ofxGLMGroup* ofxGLM::getGroup(string sName) {
	ofxGLMNamedGroups::iterator it = named_groups.find(sName);
	if(it != named_groups.end()) {
		return it->second;
	}
	ofLog(OF_LOG_VERBOSE, "ofxGroup NOT found: '%s'", sName.c_str());
	return NULL;
}

ofxGLMGroup* ofxGLM::getGroup(int nIndex) {
	ofxGLMGroups::iterator it = groups.find(nIndex);
	if(it != groups.end()) {
		return it->second;
	}
	return NULL;
}


ofxGLM& ofxGLM::scale(float nScale) {
	glmScale(model, nScale);
	return *this;
}

ofxGLM& ofxGLM::normalize() {
	glmUnitize(model);
	return *this;
}

ofxGLM& ofxGLM::renderVertices() {
	render_mode = GL_NONE;
}

ofxGLM& ofxGLM::renderFlat(bool bDoRender) {
	// when one wants to render flat, you cannot render smooth.
	render_mode = (bDoRender) ? (render_mode | GLM_FLAT) & ~GLM_SMOOTH : (render_mode & ~GLM_FLAT) | GLM_SMOOTH;
	return *this;
}

ofxGLM& ofxGLM::renderSmooth(bool bDoRender) {
	render_mode = (bDoRender) ? (render_mode | GLM_SMOOTH) & ~GLM_FLAT : (render_mode & ~GLM_SMOOTH) | GLM_FLAT;
	return *this;
}

ofxGLM& ofxGLM::renderTexture(bool bDoRender) {
	render_mode = (bDoRender) ? (render_mode | GLM_TEXTURE) : render_mode & ~GLM_TEXTURE;
	return *this;
}

ofxGLM& ofxGLM::renderMaterial(bool bDoRender) {
	render_mode = (bDoRender) ? render_mode | GLM_MATERIAL : render_mode & ~GLM_MATERIAL;
	return *this;
}

ofxGLM& ofxGLM::renderColor(bool bDoRender) {
	render_mode = (bDoRender) ? render_mode | GLM_COLOR : render_mode & ~GLM_COLOR;
}

void ofxGLM::draw() {
	//cout << render_mode << "," << GLM_TEXTURE << endl;
	glmDraw(model, render_mode);
}

// model loader helpers
// ---------------------------------------
int ofxGLM::getNumMaterials() {
	return materials.size();
}

bool ofxGLM::hasDiffuseMaterial(int nMaterialIndex) {
	return materials[nMaterialIndex]->hasDiffuseMaterial();
}

bool ofxGLM::getDiffuseMaterialTextureFile(int nMaterialIndex, string& rFileHolder) {
	return materials[nMaterialIndex]->getDiffuseMaterialTextureFile(rFileHolder);
}

int ofxGLM::getNumMeshes() {
	return groups.size();
}

int ofxGLM::getNumVertices(int nMeshIndex) {
	return groups[nMeshIndex]->getNumVertices();
}

ofVec3f ofxGLM::getMeshVertex(int nMeshIndex, int nVertexIndex) {
	return groups[nMeshIndex]->getVertices()[nVertexIndex];
}

bool ofxGLM::getMeshName(int nMeshIndex, string& rNameHolder) {
	if(!groups[nMeshIndex]->hasName()) {
		return false;
	}
	rNameHolder = groups[nMeshIndex]->getName();
	return true;
}

int ofxGLM::getNumNormals(int nMeshIndex) {
	return groups[nMeshIndex]->getNumNormals();
}

ofVec3f ofxGLM::getMeshNormal(int nMeshIndex, int nNormalIndex) {
	return groups[nMeshIndex]->getNormals()[nNormalIndex];
}

int ofxGLM::getNumTexCoords(int nMeshIndex) {
	return groups[nMeshIndex]->getNumTexCoords();
}

ofVec2f ofxGLM::getMeshTexCoord(int nMeshIndex, int nTexCoordIndex) {
	return groups[nMeshIndex]->getTexCoords()[nTexCoordIndex];
}

// returns -1 when no material was found.
int ofxGLM::getMeshMaterialIndex(int nMeshIndex) {
	int mat_index = groups[nMeshIndex]->getMaterialIndex();
	return mat_index;
}
