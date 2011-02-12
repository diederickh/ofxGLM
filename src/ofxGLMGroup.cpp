#include "ofxGLMGroup.h"
#define T(x) (model->triangles[(x)])

ofxGLMGroup::ofxGLMGroup(GLMmodel* pModel, GLMgroup* pGroup)
:model(pModel)
,group(pGroup)
,name(pGroup->name)
{
	int i,j;
	GLMtriangle* triangle;
    GLuint material = group->material;
    GLMmaterial* materialp = &model->materials[material];


	// diffuse color
	ofColor c(
		 materialp->diffuse[0] 
		,materialp->diffuse[1] 
		,materialp->diffuse[2] 
		,materialp->diffuse[3] 
	);
	
	for(int i = 0; i < group->numtriangles; ++i) {
		triangle = &T(group->triangles[i]);
		
		for(int j = 0; j < 3; ++j) {
			// add a color 
			vertex_data.addColor(c);
			
			// normal
			if (triangle->nindices[j] != -1) {
				GLfloat* np = &model->normals[3 * triangle->nindices[j]];
				ofVec3f n(*np, *(np+1), *(np+2));
				vertex_data.addNormal(n);
			}
			// texcoord
			if (triangle->tindices[j] != -1) {
				GLfloat* tp = &model->texcoords[2 * triangle->tindices[j]];
				ofVec2f tc(*tp, *(tp+1));
				vertex_data.addTexCoord(tc);
			}
			
			// vertex
			GLfloat* vp = &model->vertices[3 * triangle->vindices[j]];		
			ofVec3f v(*vp, *(vp+1), *(vp+2));
			vertex_data.addVertex(v);
		}
	}
	
	// create the mesh.
	mesh.setVertexData(&vertex_data);
	mesh.enableColors();
	
	// setup meshnode
	mesh_node.setMesh(mesh);
}

ofVertexData* ofxGLMGroup::getVertexData() {
	return &vertex_data;
}

string ofxGLMGroup::getName() {
	return name;
}


ofMesh* ofxGLMGroup::getMesh() {
	return &mesh;
}

ofMeshNode* ofxGLMGroup::getMeshNode() {
	return &mesh_node;
}

GLMgroup* ofxGLMGroup::getGLMGroup() {
	return group;
}

GLMmodel* ofxGLMGroup::getGLMModel() {
	return model;
}