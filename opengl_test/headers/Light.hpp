#pragma once
#include <GL/freeglut.h>

class Light {
public :
	Light() = default;
	Light(float x, float y, float z, int L_ID);
	void setLightID(int L_ID);
	void setPosition(float x, float y, float z);
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	void light_control();
	void draw() const;

	int lightID;
	float pos[3];
	float ambient[4];
	float diffuse[4];
	float specular[4];
	bool light_on = false;
};