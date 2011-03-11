#pragma once

#include "ofMain.h"

#include "glm.h"
#include "ofxGLMConfig.h"
#include "ofxGLMGroup.h"
#include "ofxGLMMaterial.h"
// based on: http://devernay.free.fr/hacks/glm/

typedef std::map<std::string, ofxGLMGroup*> ofxGLMNamedGroups;
typedef std::pair<std::string, ofxGLMGroup*> ofxGLMNamedGroupPair;
typedef std::map<int, ofxGLMGroup*> ofxGLMGroups;
typedef std::pair<int, ofxGLMGroup*> ofxGLMGroupPair;
typedef std::map<int, ofxGLMMaterial*> ofxGLMMaterials;
typedef std::pair<int, ofxGLMMaterial*> ofxGLMMaterialPair;

class ofxGLM {
public:
	ofxGLM();
	bool load(string sFile, float nScale = -1.0, bool bNormalize = true);
	void draw();
	
	// TODO: Check how this implementation work. But a ofxGLM object 
	// acts like a assimp model loader. It's the root to retrieve all 
	// kinds of info from. 
	int getNumMaterials();
	bool hasDiffuseMaterial(int nMaterialIndex);
	bool getDiffuseMaterialTextureFile(int nMaterialIndex, string& rFileHolder);
	int getNumMeshes();
	int getNumVertices(int nMeshIndex);
	ofVec3f getMeshVertex(int nMeshIndex, int nVertexIndex);	
	bool getMeshName(int nMeshIndex, string& rNameHolder);
	int getNumNormals(int nMeshIndex);
	ofVec3f getMeshNormal(int nMeshIndex, int nNormalIndex);
	int getNumTexCoords(int nMeshIndex);
	ofVec2f getMeshTexCoord(int nMeshIndex, int nTexCoordIndex);
	int getMeshMaterialIndex(int nMeshIndex);
		
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
	ofxGLMGroup* getGroup(int nIndex);
	ofxGLMMaterial* getMaterial(int nIndex);

	void createGroups();
	void createMaterials();

	ofxGLM& listGroups();
	
	ofxGLMGroups groups;
	ofxGLMNamedGroups named_groups;
	ofxGLMMaterials materials; 
private:
	GLuint render_mode;
	GLMmodel* model;
};