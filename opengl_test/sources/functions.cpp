#include "Sphere.hpp"
#include "Light.hpp"
#include "Texture.hpp"
#include <iostream>
using namespace std;

////////// Material Functions //////////
void Material::setEmission(float r, float g, float b, float a) {
	emission[0] = r; emission[1] = g; emission[2] = b; emission[3] = a;
}
void Material::setAmbient(float r, float g, float b, float a) {
	ambient[0] = r; ambient[1] = g; ambient[2] = b; ambient[3] = a;

}
void Material::setDiffuse(float r, float g, float b, float a) {
	diffuse[0] = r; diffuse[1] = g; diffuse[2] = b; diffuse[3] = a;

}
void Material::setSpecular(float r, float g, float b, float a) {
	specular[0] = r; specular[1] = g; specular[2] = b; specular[3] = a;
}
void Material::setShininess(float sh) {
	shininess[0] = sh;
}

////////// Light Functions //////////
Light::Light(float x, float y, float z, int L_ID) {
	setPosition(x, y, z);
	setLightID(L_ID);
}

void Light::setLightID(int L_ID) {
	lightID = L_ID;
}
void Light::setPosition(float x, float y, float z) {
	pos[0] = x; pos[1] = y; pos[2] = z;
}
void Light::setAmbient(float r, float g, float b, float a) {
	ambient[0] = r; ambient[1] = g; ambient[2] = b; ambient[3] = a;
}
void Light::setDiffuse(float r, float g, float b, float a) {
	diffuse[0] = r; diffuse[1] = g; diffuse[2] = b; diffuse[3] = a;
}
void Light::setSpecular(float r, float g, float b, float a) {
	specular[0] = r; specular[1] = g; specular[2] = b; specular[3] = a;
}
void Light::light_control() {
	if (!light_on) {
		if (lightID == 0) {
			glEnable(GL_LIGHT0);
		}
		if (lightID == 1) {
			glEnable(GL_LIGHT1);
		}
		light_on = true;
	}
	else {
		if (lightID == 0) {
			glDisable(GL_LIGHT0);
		}
		if (lightID == 1) {
			glDisable(GL_LIGHT1);
		}
		light_on = false;
	}
}

void Light::draw() const {
	glPushMatrix();

	glLightfv(lightID, GL_AMBIENT, ambient);
	glLightfv(lightID, GL_DIFFUSE, diffuse);
	glLightfv(lightID, GL_SPECULAR, specular);
	glLightfv(lightID, GL_POSITION, pos);

	glPopMatrix();
}

////////// Sphere Functions //////////
Sphere::Sphere(float r, int sl, int st) {
	setRadius(r);
	setSlice(sl);
	setStack(st);
}
void Sphere::setRadius(float r) {
	radius = r;
}
float Sphere::getRadius() const {
	return radius;
}
void Sphere::setSlice(int sl) {
	slice = sl;
}
void Sphere::setStack(int st) {
	stack = st;
}
void Sphere::setCenter(float x, float y, float z) {
	center[0] = x; center[1] = y; center[2] = z;
}
const float* Sphere::getCenter() const {
	return center;
}
void Sphere::setVelocity(float x, float y, float z) {
	velocity[0] = x; velocity[1] = y; velocity[2] = z;
}
const float* Sphere::getVelocity() const {
	return velocity;
}
void Sphere::setMTL(const Material& m) {
	mtl = m;
}
void Sphere::move(float bx, float by) {

	center[0] += velocity[0];
	center[1] += velocity[1];
	center[2] += velocity[2];

	if (center[0] + radius >= bx || center[0] - radius <= -bx) {
		velocity[0] *= -1;
	}
	if (center[1] + radius >= by || center[1] - radius <= -by) {
		velocity[1] *= -1;
	}
	//if (center[2] + radius >= bz || center[2] - radius <= -bz) {
	//	velocity[2] *= -1;
	//}

}
void Sphere::draw() const {
	glPushMatrix();

	/*glShadeModel(GL_SMOOTH);*/
	glTranslatef(center[0], center[1], center[2]);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.emission);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.shininess);

	glutSolidSphere(radius, slice, stack);

	glPopMatrix();
}

////////// Texture Functions //////////
FIBITMAP* Texture::createBitMap(char const* filename) {
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
	if (format == -1) { // couldn't find image
		exit(-1);
	}
	else if (format == FIF_UNKNOWN) { // couldn't determine file format
		// attemp to get from file extension
		format = FreeImage_GetFIFFromFilename(filename);
		if (!FreeImage_FIFSupportsReading(format)) {
			cout << "Detected image format cannot be read!" << endl;
			exit(-1);
		}
	}
	FIBITMAP* bitmap = FreeImage_Load(format, filename);
	int bitsPerPixel = FreeImage_GetBPP(bitmap);
	cout << "Source image has " << bitsPerPixel << " bits per pixel." << endl;
	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32) {
		cout << "Skipping conversion." << endl;
		bitmap32 = bitmap;
	}
	else {
		cout << "Converting to 32-bits." << endl;
		bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
	}
	return bitmap32;
}
void Texture::generateTexture() {
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,
		0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, textureData);
}
void Texture::initializeTexture(char const* filename) {
	FIBITMAP* bitmap32 = createBitMap(filename);
	imageWidth = FreeImage_GetWidth(bitmap32);
	imageHeight = FreeImage_GetHeight(bitmap32);
	textureData = FreeImage_GetBits(bitmap32);
	generateTexture();

}
GLuint Texture::getTextureID() const {
	return textureID;
}