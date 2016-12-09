
#include "stdafx.h"

#include <iostream>
#include "./../lib/glut_3_7_6/glut-3.7.6-bin/glut.h"
//#include "BaseGuiFunctionality.h"

static int gpMode;

#define GL_LINES_MODE 0
#define GL_LINE_STRÌP_MODE 1
#define GL_LINE_LOOP_MODE 2
#define GL_POINTS_MODE 3
#define GL_QUADS_MODE 4
#define GL_TRIANGLES_MODE 5
#define GL_TRIANGLE_FAN_MODE 6
#define GL_POLYGON_MODE 7

#define MAX_NUM_GEO_PRIMITVES 7

void displayGeoPrimitives() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPointSize(6.0);
	glLineWidth(4.0);

	switch (gpMode)
	{
	case GL_LINES_MODE:
		glBegin(GL_LINES);
		break;
	case GL_LINE_STRÌP_MODE:
		glBegin(GL_LINE_STRIP);
		break;
	case GL_LINE_LOOP_MODE:
		glBegin(GL_LINE_LOOP);
		break;
	case GL_POINTS_MODE:
		glBegin(GL_POINTS);
		break;
	case GL_QUADS_MODE:
		glBegin(GL_QUADS);
		break;
	case GL_TRIANGLES_MODE:
		glBegin(GL_TRIANGLES);
		break;
	case GL_TRIANGLE_FAN_MODE:
		glBegin(GL_TRIANGLE_FAN);
		break;
	case GL_POLYGON_MODE:
		glBegin(GL_POLYGON);
		break;
	}
	glColor3d(0.0, 0.0, 1.0);

	glVertex3d(0.2, -0.4, 0.0);
	glVertex3d(0.4, -0.2, 0.0);
	glVertex3d(-0.2, -0.5, 0.0);
	glVertex3d(0.4, -0.1, 0.0);
	glVertex3d(0.2, 0.4, 0.0);
	glVertex3d(-0.4, -0.3, 0.0);

	glEnd();

	glutSwapBuffers();
} // display

void specialKeyFunc(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		gpMode++;
		if (gpMode > MAX_NUM_GEO_PRIMITVES) {
			gpMode = 0;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		gpMode--;
		if (gpMode < 0) {
			gpMode = MAX_NUM_GEO_PRIMITVES;
		}
		glutPostRedisplay();
		break;
	}
}

void keyboardFunc(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;
	case 'p':
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glutPostRedisplay();
		break;
	case 's':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutPostRedisplay();
		break;
	}
}

static int ex02_geoPrimitves_run(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(300, 300);
	glutCreateWindow("OpenGL Test");
	glutDisplayFunc(displayGeoPrimitives);

	glutKeyboardFunc(keyboardFunc);
	glutSpecialFunc(specialKeyFunc);

	//to enable anti-aliasing
	//glEnable(GL_LINE_SMOOTH);

	gpMode = 0;

	glutMainLoop();
	return 0;
}
