ofxGLM
=======
GLM is a amazing Wavefront OBJ file loader, with:
- support for materials
- auto loading images (png,jpg,tiff,etc)
- vertices,normals,colors, etc..
- normalizing objects to a unitcube
- has it's own draw functions!

This addon is very handy when you want to load 3D models you created 
for example using Blender.

Example
========
ofxGLM obj;
if(obj.load("grass3.obj")){
	obj.renderTexture()
		.renderSmooth()
		.renderTwoSided();
	obj.scale(400);
}

// in draw:
obj.draw();




