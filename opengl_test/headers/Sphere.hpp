#pragma once
#include "Material.hpp"

class Sphere {
public : 
	Sphere(float r, int sl, int st);
	void setRadius(float r);
	float getRadius() const;
	void setSlice(int sl);
	void setStack(int st);
	void setCenter(float x, float y, float z);
	const float* getCenter() const;
	void setVelocity(float x, float y, float z);
	const float* getVelocity() const;
	void setMTL(const Material& m);
	void move(float bx, float by);
	void draw() const;

	float radius;
	int slice;
	int stack;
	float center[3];
	float velocity[3];
	Material mtl;
};