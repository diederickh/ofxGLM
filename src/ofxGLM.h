#pragma once
#include "ofMain.h"
#include "glm.h"

// based on: http://devernay.free.fr/hacks/glm/

class ofxGLM {
public:
	ofxGLM();
	bool load(string sFile, bool bNormalize = true);
	void draw();
	ofxGLM& renderFlat(bool bDoRender = true);
	ofxGLM& renderSmooth(bool bDoRender = true);
	ofxGLM& renderTexture(bool bDoRender = true);
	ofxGLM& renderTwoSided(bool bDoRender = true);
	ofxGLM& renderColor(bool bDoRender = true);
	ofxGLM& renderMaterial(bool bDoRender = true);
	ofxGLM& renderVertices(); // resets render mode
	
	ofxGLM& scale(float nScale);
	ofxGLM& normalize();
	
private:
	GLuint render_mode;
	GLMmodel* model;
};