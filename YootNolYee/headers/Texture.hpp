#pragma once
#include <FreeImage.h>
#include <GL/freeglut.h>

class Texture {
public :
	Texture() = default;
	FIBITMAP* createBitMap(char const* filename);
	void generateTexture();
	void initializeTexture(char const* filename);
	GLuint getTextureID() const;
    void draw_texture(float x, float y, float size_x, float size_y) const;

	GLuint textureID;
	GLubyte* textureData;
	int imageWidth, imageHeight;
};