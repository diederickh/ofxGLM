#pragma once

#include "ofMain.h"
#include "ofxGLMConfig.h"
#include "glm.h"


//class ofxGLMMaterial : public ofMaterial {
class ofxGLMMaterial {
public:
	ofxGLMMaterial();
	void setGLMMaterial(int nIndex, GLMmaterial* pMat, GLMmodel* pModel);
	
	ofColor convertFloatsToColor(float* pColor) {
		ofColor col((*pColor * 255), *(pColor+1)*255, *(pColor+2)*255, *(pColor+3) * 255);
		return col;
	}
	
	int material_index;
//	ofTexture texture;
	
private:
	
};