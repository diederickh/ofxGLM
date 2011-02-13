#include "ofxGLMMaterial.h"

ofxGLMMaterial::ofxGLMMaterial():ofMaterial() {
}


void ofxGLMMaterial::setGLMMaterial(int nIndex, GLMmaterial* pMat, GLMmodel* pModel) {
	material_index = nIndex;
	ofColor c= convertFloatsToColor(pMat->diffuse);
	cout << c << std::endl;
	setDiffuseColor(convertFloatsToColor(pMat->diffuse));
	setAmbientColor(convertFloatsToColor(pMat->ambient));
	setSpecularColor(convertFloatsToColor(pMat->specular));
	setShininess(pMat->shininess);

	// do we have a diffuse map?
	if(pMat->map_kd != NULL) {
		ofImage img;
		if(img.loadImage(pMat->map_kd)) {
			texture.allocate(
				 img.getWidth()
				,img.getHeight()
				,img.getOFPixels().getGlDataType()
			);
			texture.loadData(img.getOFPixels());
		}
		else {
			ofLog(OF_LOG_ERROR, "Cannot load image: '%s'", pMat->map_kd);
		}
		setDiffuseMap(texture);
		ofLog(OF_LOG_VERBOSE, "Created material with texture image: '%s'", pMat->map_kd);
	}
}

