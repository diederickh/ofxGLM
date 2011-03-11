#include "ofxGLMMaterial.h"

//ofxGLMMaterial::ofxGLMMaterial():ofMaterial() {
ofxGLMMaterial::ofxGLMMaterial() 
:found_materials(OFXGLM_MAT_NONE)
{
}

void ofxGLMMaterial::setGLMMaterial(int nIndex, GLMmaterial* pMat, GLMmodel* pModel) {
	material_index = nIndex;

	// Diffuse material file
	if(pMat->map_kd != NULL) {
		cout << "Material: " << nIndex << " has diffuse texture: " << pMat->map_kd << endl;;
		found_materials |= OFXGLM_MAT_DIFFUSE;
		material_files.insert(pair<ofxGLMMaterialType, string>(OFXGLM_MAT_DIFFUSE, pMat->map_kd));
	}
}

// Get the filepath for the diffuse texture.
bool ofxGLMMaterial::getDiffuseMaterialTextureFile(string& rHolderForFile) {
	return getMaterialTextureFile(OFXGLM_MAT_DIFFUSE, rHolderForFile);
}

// Get the filepath for one fo the defined materials
bool ofxGLMMaterial::getMaterialTextureFile(ofxGLMMaterialType nType, string& rHolderForFile) {
	map<ofxGLMMaterialType, string>::iterator it = material_files.find(nType);
	if(it == material_files.end()) {
		return false;
	}
	rHolderForFile = it->second;
	return true;
}

// Check if we've got a diffuse material
bool ofxGLMMaterial::hasDiffuseMaterial() {
	return hasMaterial(OFXGLM_MAT_DIFFUSE);
}

// Check if we've got a general material.
bool ofxGLMMaterial::hasMaterial(ofxGLMMaterialType nMat) {
	if (nMat & found_materials) {
		cout << "Check if we have a material: " << material_index << " : YES \n" ;
		return true;
	}
	cout << "Check if we have a material: " << material_index << " : NO \n" ;
	return false;
}
	
