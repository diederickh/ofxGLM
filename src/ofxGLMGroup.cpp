#include "ofxGLMGroup.h"
#define T(x) (model->triangles[(x)])

ofxGLMGroup::ofxGLMGroup(GLMmodel* pModel, GLMgroup* pGroup)
:model(pModel)
,group(pGroup)
,name(pGroup->name)
{
	int i,j;
	GLMtriangle* triangle;
	
  	material_index = pGroup->material;
		
	
	for(int i = 0; i < group->numtriangles; ++i) {
		triangle = &T(group->triangles[i]);

		for(int j = 0; j < 3; ++j) {
			if(pModel->numnormals > 0) {
				
				//if (triangle->nindices[j] != -1) {
					GLfloat* np = &model->normals[3 * triangle->nindices[j]];
					ofVec3f n(*np, *(np+1), *(np+2));
					normals.push_back(n);
				//}
				
			}
			
			if(pModel->numtexcoords > 0) {

				//if (triangle->tindices[j] != -1) {
					//cout << " TC " ;
					//glTexCoord2fv(&model->texcoords[2 * triangle->tindices[2]]);
					
					int triangle_index = triangle->tindices[j];
					if (triangle_index > 0 && triangle_index < pModel->numtriangles) {
					//	cout << triangle_index << " -- " << pModel->numtriangles << endl;
						GLfloat* tp = &model->texcoords[2 * triangle->tindices[j]];
						ofVec2f tc(*tp, 1-(*(tp+1))); // !!!: somehow the Y coordinates are flipped (so they start measuring from above)
						texcoords.push_back(tc);
					}
					
				//}
			}
			
			// vertex
			GLfloat* vp = &model->vertices[3 * triangle->vindices[j]];		
			ofVec3f v(*vp, *(vp+1), *(vp+2));
			vertices.push_back(v);

			// TODO: implement colors
		}
		//cout << "\n----" << endl;
	}
}

bool ofxGLMGroup::hasName() {
	return name != "";
}

// check if we've got has vertices.
bool ofxGLMGroup::hasVertices() {
	return vertices.size() > 0;
}

// check if we've got normals.
bool ofxGLMGroup::hasNormals() {
	return normals.size() > 0;
}

// check if we've got texture coords.
bool ofxGLMGroup::hasTexCoords() {  
	return texcoords.size() > 0;
}

// check if we've got colors
bool ofxGLMGroup::hasColors() {
	return colors.size() > 0;
}

// get vertices.
vector<ofVec3f>& ofxGLMGroup::getVertices() {
	return vertices;
}

// get normals
vector<ofVec3f>& ofxGLMGroup::getNormals() {
	return normals;
}

// get texcoords
vector<ofVec2f>& ofxGLMGroup::getTexCoords() {
	return texcoords;
}

// get colors
vector<ofxGLMColor>& ofxGLMGroup::getColors() {
	return colors;
}

int ofxGLMGroup::getNumVertices() {
	return vertices.size();
}

int ofxGLMGroup::getNumNormals() {
	return normals.size();
}
	
int ofxGLMGroup::getNumTexCoords() {
	return texcoords.size();
}

int ofxGLMGroup::getNumColors() {
	return colors.size();
}

string ofxGLMGroup::getName() {
	return name;
}

/*
ofMesh* ofxGLMGroup::getMesh() {
	return &mesh;
}
*/
/*
ofMeshNode* ofxGLMGroup::getMeshNode() {
	return &mesh_node;
}
*/

GLMgroup* ofxGLMGroup::getGLMGroup() {
	return group;
}

GLMmodel* ofxGLMGroup::getGLMModel() {
	return model;
}

int ofxGLMGroup::getMaterialIndex() {
	return material_index;
}