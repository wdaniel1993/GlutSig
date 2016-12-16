
#ifndef _BASE_GUI_FUNCTIONALITY_H_
#define _BASE_GUI_FUNCTIONALITY_H_

#include <iostream>
#include "./../lib/glut_3_7_6/glut-3.7.6-bin/glut.h"

bool leftMouseDown = false;
bool rightMouseDown = false;
int lastMouseX = 0, lastMouseY = 0;
int rotateX = 0, rotateY = 0;
double zoom = -20.0;

int currMouseX = 0;
int currMouseY = 0;

void resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(15.0, height != 0 ? (double)width / (double)height : 1.0, 5.0, 80.0);
	std::cout << " resize to " << width << " " << height << " with aspect-ratio= " << ((double)width / (double)height) << std::endl;
	glMatrixMode(GL_MODELVIEW);
} // resize

void passivMouseMotion(int x, int y) {
	currMouseX = x;
	currMouseY = y;
} // passivMouseMotion

void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		leftMouseDown = (state == GLUT_DOWN);
	} // if
	else if (button == GLUT_RIGHT_BUTTON) {
		rightMouseDown = (state == GLUT_DOWN);
	} // else if
	if (state == GLUT_DOWN) {
		lastMouseX = x;
		lastMouseY = y;
	} // if
} // mouseButton

void mouseMotion(int x, int y) {
	if (leftMouseDown) {
		rotateX = (rotateX + (x - lastMouseX)) % 360;
		rotateY = (rotateY + (y - lastMouseY)) % 360;
		//std::cout << " rotating to " << rotateX << " " << rotateY << std::endl;
	} // if
	else if (rightMouseDown) {
		zoom += ((x - lastMouseX) + (y - lastMouseY)) / 2.0;
		//std::cout << " zoom new " << zoom << std::endl;
	} // else if

	std::cout << " new zoom = " << zoom << std::endl;

	//std::cout << " mouse pos " << lastMouseX << " " << lastMouseY << std::endl;
	lastMouseX = x;
	lastMouseY = y;
	glutPostRedisplay();
} // mouseMotion


#endif //_BASE_GUI_FUNCTIONALITY_H_