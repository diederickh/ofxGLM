#pragma once

#include "ofMain.h"
#include "ofxGLMConfig.h"
#include "glm.h"

enum ofxGLMMaterialType {
	 OFXGLM_MAT_NONE			= (0 << 0)
	,OFXGLM_MAT_DIFFUSE 		= (1 << 1) 
};

//class ofxGLMMaterial : public ofMaterial {
class ofxGLMMaterial {
public:
	ofxGLMMaterial();
	void setGLMMaterial(int nIndex, GLMmaterial* pMat, GLMmodel* pModel);
	
	ofColor convertFloatsToColor(float* pColor) {
		ofColor col((*pColor * 255), *(pColor+1)*255, *(pColor+2)*255, *(pColor+3) * 255);
		return col;
	}
	bool getDiffuseMaterialTextureFile(string& rHolderForFile);
	bool getMaterialTextureFile(ofxGLMMaterialType nType, string& rHolderForFile);
	
	bool hasMaterial(ofxGLMMaterialType nMat); 
	bool hasDiffuseMaterial(); 
	
	int found_materials;
	int material_index;
	
private:
	map<ofxGLMMaterialType, string> material_files;
};