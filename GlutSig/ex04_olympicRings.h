#include "stdafx.h"

#include <iostream>
#include "math.h"
#include "./../lib/glut_3_7_6/glut-3.7.6-bin/glut.h"
//#include "BaseGuiFunctionality.h"

#define PI 3.14159

GLuint theCircle;

//draw circle
static void getCircle(int resolution, double radius) {
	double anglePerPoint = 360.0 / (double)resolution;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < resolution; i++) {
		//double currAngle = i * anglePerPoint; currentAngle in degrees
		double cosineX = cos(i * 2 * PI / resolution) * radius;
		double sineX = sin(i * 2 * PI / resolution) * radius;
		glVertex2d(cosineX, sineX);
	}
	glEnd();
}

//init display lists
static void init(void)
{
	theCircle = glGenLists(1);
	glNewList(theCircle, GL_COMPILE);
	int resolution = 100;
	double radius = 1.0;

	//define the circle
	getCircle(resolution, radius);
	glEndList();
}

void displayRings(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(7.0);

	int resolution = 100;
	double radius = 0.5;

	glPushMatrix();
	glColor3d(0.0, 0.0, 1.0);
	glTranslated(0.25, 0, 0);
	glScaled(0.3, 0.3, 0.3);
	glCallList(theCircle);
	//getCircle(resolution, radius);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.0, 5.0, 0.0);
	glTranslated(0.0, 0.25, 0);
	glScaled(0.5, 0.5, 0.5);
	//getCircle(resolution, radius);
	glCallList(theCircle);
	glPopMatrix();

	glutSwapBuffers();
}


static int ex04_olympicRingsDisplayLists_run(int argc, char* argv[])
{
	glutInitWindowSize(200, 200);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("ex04: olympic rings");
	init();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);

	glutDisplayFunc(displayRings);
	glutMainLoop();
	return 0;
}

