#include "ofxGLMGroup.h"
#define T(x) (model->triangles[(x)])

ofxGLMGroup::ofxGLMGroup(GLMmodel* pModel, GLMgroup* pGroup, ofxGLMMaterial* pMaterial)
:model(pModel)
,group(pGroup)
,name(pGroup->name)
{
	int i,j;
	GLMtriangle* triangle;
  
	// diffuse color
	ofColor c(255,255,255,255);
	if(pMaterial != NULL) {
		c = pMaterial->getDiffuseColor();
		mesh_node.addMaterial(pMaterial);
	}
	
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

	if(vertex_data.getNumNormals() > 0) {
		mesh.enableNormals();
	}
	
	if(vertex_data.getNumColors() > 0) {
		mesh.enableNormals();
	}
		
	if(vertex_data.getNumTexCoords() > 0) {
		mesh.enableTexCoords();
		mesh.disableColors();
	}
	mesh.setupVbo();
	//mesh.setRenderMethod(OF_MESH_USING_VBO);
	/*
	
	*/
	//cout << "mum normals: " << vertex_data.getNumTexCoords();
	//cout << "------------------\n";
	//mesh.enableColors();
	
	// setup meshnode
	mesh_node.setMesh(mesh);
	cout << name << "\n=================\n";
	cout << vertex_data << std::endl;
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