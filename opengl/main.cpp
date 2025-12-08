#include <fstream>
#include <GL/freeglut.h>

using namespace std;

float x, y, w, h, r, g, b;

void readFile() {
	/* Implement: read rectangle.txt */
	ifstream ifs1("rectangle.txt");
	ifs1 >> x >> y >> w >> h >> r >> g >> b;
	ifs1.close();
}

void drawRectangle() {
	/* Implement: draw a rectangle */
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	glVertex2f(x + w / 2, y + h / 2);
	glVertex2f(x - w / 2, y + h / 2);
	glVertex2f(x - w / 2, y - h / 2);
	glVertex2f(x + w / 2, y - h / 2);
	glEnd();
}

void renderScene() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	drawRectangle();

	glFlush();
	// glFinish();
}

int main(int argc, char** argv) {
	readFile();

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Draw a rectangle");

	// register callbacks
	glutDisplayFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();
}
