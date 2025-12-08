#include "Texture.hpp"
#include <iostream>

FIBITMAP* Texture::createBitMap(char const* filename) {
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
	if (format == -1) { // couldn't find image
		exit(-1);
	}
	else if (format == FIF_UNKNOWN) { // couldn't determine file format
		// attemp to get from file extension
		format = FreeImage_GetFIFFromFilename(filename);
		if (!FreeImage_FIFSupportsReading(format)) {
			std::cout << "Detected image format cannot be read!" << std::endl;
			exit(-1);
		}
	}
	FIBITMAP* bitmap = FreeImage_Load(format, filename);
	int bitsPerPixel = FreeImage_GetBPP(bitmap);
	// std::cout << "Source image has " << bitsPerPixel << " bits per pixel." << std::endl;
	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32) {
		// std::cout << "Skipping conversion." << std::endl;
		bitmap32 = bitmap;
	}
	else {
		// std::cout << "Converting to 32-bits." << std::endl;
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
void Texture::draw_texture(float x, float y, float size_x, float size_y) const {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, getTextureID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(x - size_x, y - size_y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(x - size_x, y + size_y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(x + size_x, y + size_y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(x + size_x, y - size_y);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}