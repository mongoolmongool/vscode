#include <iostream>
#include <vector>

#include "Sphere.hpp"
#include "Light.hpp"
#include "Texture.hpp"

using namespace std;

#define WINDOW_X 300
#define WINDOW_Y 300

#define WINDOW_WIDTH 640		// window's width
#define WINDOW_HEIGHT 640		// window's height

#define boundaryX (WINDOW_WIDTH)/2
#define boundaryY (WINDOW_HEIGHT)/2


clock_t start_t = clock();
clock_t end_t;

vector<Sphere> spheres;
Light light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);
Texture texture;

void initialize() {
	light.setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	light.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

	Material mtl1;
	mtl1.setEmission(0.1f, 0.1f, 0.1f, 1.0f);
	mtl1.setAmbient(0.4f, 0.4f, 0.1f, 1.0f);
	mtl1.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	mtl1.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	mtl1.setShininess(10.0f);

	Material mtl2(mtl1), mtl3(mtl1);
	mtl2.setAmbient(0.1f, 0.4f, 0.4f, 1.0f);
	mtl3.setAmbient(0.4f, 0.1f, 0.4f, 1.0f);

	Sphere sphere1(50, 20, 20);
	sphere1.setCenter(0.0f, -200.0f, 0.0f);
	sphere1.setVelocity(0.3f, 0.6f, 0.0f);
	sphere1.setMTL(mtl1);
	spheres.push_back(sphere1);

	Sphere sphere2(sphere1);
	sphere2.setCenter(100.0f, 200.0f, 0.0f);
	sphere2.setVelocity(-0.6f, -0.5f, 0.0f);
	sphere2.setMTL(mtl2);
	spheres.push_back(sphere2);

	Sphere sphere3(sphere1);
	sphere3.setCenter(-100.0f, 0.0f, 0.0f);
	sphere3.setVelocity(-2.0f, 2.0f, 0.0f);
	sphere3.setMTL(mtl3);
	spheres.push_back(sphere3);

	/* Implement: initialize texture*/
	texture.initializeTexture("team3.png");
}

void idle() {
	/* Implement: update spheres and handle collision at boundary*/

	end_t = clock();

	if (end_t - start_t > 1000 / 120) {

		spheres[0].move(boundaryX, boundaryY); 
		spheres[1].move(boundaryX, boundaryY); 
		spheres[2].move(boundaryX, boundaryY);

		start_t = end_t;
		glutPostRedisplay();
	}
}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);
	//gluOrtho2D(-boundaryX, boundaryX, -boundaryY, boundaryY);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* Implement: Draw 2D (texture)*/
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture.textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-boundaryX / 2.0f, -boundaryY / 2.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-boundaryX / 2.0f, boundaryY / 2.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(boundaryX / 2.0f, boundaryY / 2.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(boundaryX / 2.0f, -boundaryY / 2.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	/* Implement: Draw 3D (light and spheres)*/
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(light.lightID);

	light.draw();
	spheres[0].draw();
	spheres[1].draw();
	spheres[2].draw();

	glDisable(light.lightID);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Draw three spheres");

	initialize();

	// register callbacks
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
