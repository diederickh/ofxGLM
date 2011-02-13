#pragma once

#include "ofMain.h"
#include "ofxGLMConfig.h"
#include "glm.h"

class ofxGLMTexture {
public:
	ofxGLMTexture();
	void setGLMTexture(GLMtexture* pTexture, GLMmodel* pModel);
	ofTexture* getTexture();
	ofTexture texture;
};