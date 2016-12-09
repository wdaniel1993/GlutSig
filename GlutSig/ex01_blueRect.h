
#include "stdafx.h"

#include <iostream>
#include "./../lib/glut_3_7_6/glut-3.7.6-bin/glut.h"
//#include "BaseGuiFunctionality.h"

void displayRect() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPointSize(7.0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	//glBegin(GL_QUADS);
	glBegin(GL_POLYGON);
	{
		//set color to blue
		glColor3d(0.0, 0.0, 1.0);
		glVertex2d(-0.5,-0.5);
		glVertex2d(-0.5,0.5);
		glVertex2d(0.5,0.5);
		glVertex2d(0.5,-0.5);
	}
	glEnd();

	glutSwapBuffers();
} // display

static int ex01_blueRect_run(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(300, 300);
	glutCreateWindow("OpenGL Test");
	glutDisplayFunc(displayRect);

	//to enable anti-aliasing
	//glEnable(GL_LINE_SMOOTH);

	glutMainLoop();
	return 0;
}
