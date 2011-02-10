#include "ofxGLM.h"

ofxGLM::ofxGLM() 
:model(NULL)
,render_mode(GLM_NONE)
{
}

bool ofxGLM::load(string sFile, bool bNormalize) {
	model = glmReadOBJ(ofToDataPath(sFile, true).c_str());
	if(!model) {
		ofLog(OF_LOG_ERROR, "Could not load model: %s", sFile.c_str());
		return false;
	}
	if(bNormalize) {
		normalize();
	}
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

ofxGLM& ofxGLM::renderTwoSided(bool bDoRender) {
	render_mode = (bDoRender) ? render_mode | GLM_2_SIDED : render_mode & ~GLM_TEXTURE;
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
	glmDraw(model, render_mode);
}