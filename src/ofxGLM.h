#pragma once

#include "ofMain.h"

#include "glm.h"
#include "ofxGLMConfig.h"
#include "ofxGLMGroup.h"
// based on: http://devernay.free.fr/hacks/glm/

typedef std::map<std::string, ofxGLMGroup*> ofxGLMGroups;
typedef std::pair<std::string, ofxGLMGroup*> ofxGLMGroupPair;

class ofxGLM {
public:
	ofxGLM();
	bool load(string sFile, float nScale = -1.0, bool bNormalize = true);
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
	
	void createGroups();
	ofxGLMGroup* getGroup(string sName);
	ofMesh* getMesh(string sName);
	ofVertexData* getVertexData(string sName);
	
	/**
	 * OBJ files can contain face groups. One can use these
	 * face groups to i.e. animate a certain part of a 3D model.
	 * This method just lists the found groups.
	 *
	 * To export a 3D model from blender 2.5 including face groups
	 * you can follow these steps:
	 * - select the object you want to export as group
	 * - in the outliner you can see the selected object; by default
	 *   this gets a auto generated name. You can rename this by editing
	 *   the input field in the OBJ pane. For example when working on 
	 *	 a butterfly 3D model, you can select the right wing and call
	 *   the right wing object "wing" in the Object-pane. 
	 * - then in the Object Data pane you type "right".
	 * - then File > Export > Wavefront (.obj) and select these options
	 *      [ ] Objects as OBJ Objects
	 *      [X] Objects as OBJ Groups
	 * - the exported face group is called "wing_right".
	 */
	ofxGLM& listGroups();
	
	ofxGLMGroups groups;
	
private:
	GLuint render_mode;
	GLMmodel* model;
};