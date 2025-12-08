#include "Yoot.hpp"
#include "Constants.hpp"
#include "In_game.hpp"
#include <iostream>
#include <GL/freeglut.h>

In_game in_game(3, 4);
// int num_of_teams;
// int num_of_pieces;

using namespace std;

void initialize() {
    in_game.initialize();
}

void idle() {
    in_game.idle();
}

void display() {
    in_game.display();
}

void keyboardDown(unsigned char key, int x, int y) {
	in_game.keyboardDown(key, x, y);
}

void mouse(int button, int state, int x, int y) {
	in_game.mouse(button, state, x, y);
}

int main(int argc, char** argv) {
	// std::cin >> num_of_teams;
	// std::cin >> num_of_pieces;

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("WELCOME BRASS SEOLLAL");

    initialize();

	// register callbacks
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardDown);
	glutMouseFunc(mouse);
    glutIdleFunc(idle);

	// enter GLUT event processing cycle
 	glutMainLoop();
}