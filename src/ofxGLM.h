#pragma once

#include "ofMain.h"

#include "glm.h"
#include "ofxGLMConfig.h"
#include "ofxGLMGroup.h"
#include "ofxGLMMaterial.h"
// based on: http://devernay.free.fr/hacks/glm/

typedef std::map<std::string, ofxGLMGroup*> ofxGLMGroups;
typedef std::pair<std::string, ofxGLMGroup*> ofxGLMGroupPair;
typedef std::map<int, ofxGLMMaterial*> ofxGLMMaterials;
typedef std::pair<int, ofxGLMMaterial*> ofxGLMMaterialPair;

class ofxGLM {
public:
	ofxGLM();
	bool load(string sFile, float nScale = -1.0, bool bNormalize = true);
	void draw();
	
	
	// TODO: remove these! We're just importing? 
	ofxGLM& renderFlat(bool bDoRender = true);
	ofxGLM& renderSmooth(bool bDoRender = true);
	ofxGLM& renderTexture(bool bDoRender = true);
	ofxGLM& renderColor(bool bDoRender = true);
	ofxGLM& renderMaterial(bool bDoRender = true);
	ofxGLM& renderVertices(); // resets render mode
	
	ofxGLM& scale(float nScale);
	ofxGLM& normalize();
	

	ofxGLMGroup* getGroup(string sName);
	ofxGLMMaterial* getMaterial(int nIndex);

	void createGroups();
	void createMaterials();

	ofxGLM& listGroups();
	
	ofxGLMGroups groups;
	ofxGLMMaterials materials; 
private:
	GLuint render_mode;
	GLMmodel* model;
};