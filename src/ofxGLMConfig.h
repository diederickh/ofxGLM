#pragma once
#define MATERIAL_BY_FACE
#define SINGLE_STRING_GROUP_NAMES

struct ofxGLMColor {
	ofxGLMColor(float rr, float gg, float bb, float aa)
		:r(rr)
		,g(gg)
		,b(bb)
		,a(aa)
	{
	}
	float r,g,b,a;
};