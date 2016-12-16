// TestOpenGL1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "./../lib/glut_3_7_6/glut-3.7.6-bin/glut.h"
#include "BaseGuiFunctionality.h"

static int selectedMode1;
static double resolution1;
static double size1;

#define MIN_RESOLUTION 5.0

#define SOLID_CUBE 0
#define SOLID_CONE 1
#define SOLID_DODECAHEDRON 2
#define SOLID_ICOSAHEDRON 3
#define SOLID_OCTAHEDRON 4
#define SOLID_SPHERE 5
#define SOLID_TEAPOT 6
#define SOLID_TETRAHEDRON 7
#define SOLID_TORUS 8

#define MAX_OBJ_ID 8

// Lighting values
//float ambientLight[4] = {0.2, 0.2, 0.2, 1.0};
float Lt0amb[4] = { 0.1, 0.1, 0.1, 1.0 };
float Lt0diff[4] = { 0.6, 0.6, 0.6, 1.0 };
float Lt0spec[4] = { 1.0, 1.0, 1.0, 1.0 };
float Lt0pos[4] = { 1.0, 0.0, 1.0, 0.0 };			// Directional light

// Material values
float Noemit[4] = { 0.1, 0.1, 0.1, 1.0 };
float Matspec[4] = { 1.0, 1.0, 1.0, 1.0 };
float Matnonspec[4] = { 0.8, 0.05, 0.4, 1.0 };
float Matshiny = 50.0;

static void printoutKeyInfo();

void drawSelectedObject() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3d(1.0, 1.0, 0.0);

	glPushMatrix();
	if (selectedMode1 == SOLID_CUBE) {
		glutSolidCube(size1);
		glutSetWindowTitle("SOLID_CUBE");
	} //if
	else if (selectedMode1 == SOLID_CONE) {
		glutSolidCone(size1 / 2.0, size1, resolution1, resolution1);
		glutSetWindowTitle("SOLID_CONE");
	} //else if
	else if (selectedMode1 == SOLID_DODECAHEDRON) {
		glutSolidDodecahedron();
		glutSetWindowTitle("SOLID_DODECAHEDRON");
		glScaled(size1, size1, size1);
	} //else if
	else if (selectedMode1 == SOLID_ICOSAHEDRON) {
		glutSolidIcosahedron();
		glutSetWindowTitle("SOLID_ICOSAHEDRON");
		glScaled(size1, size1, size1);
	} //else if
	else if (selectedMode1 == SOLID_OCTAHEDRON) {
		glutSolidOctahedron();
		glutSetWindowTitle("SOLID_OCTAHEDRON");
		glScaled(size1, size1, size1);
	} //else if
	else if (selectedMode1 == SOLID_SPHERE) {
		glutSolidSphere(size1, resolution1, resolution1);
		glutSetWindowTitle("SOLID_SPHERE");
	} //else if
	else if (selectedMode1 == SOLID_TEAPOT) {
		glutSolidTeapot(size1);
		glutSetWindowTitle("SOLID_TEAPOT");
	} //else if
	else if (selectedMode1 == SOLID_TETRAHEDRON) {
		glutSolidTetrahedron();
		glutSetWindowTitle("SOLID_TETRAHEDRON");
		glScaled(size1, size1, size1);
	} //else if
	else if (selectedMode1 == SOLID_TORUS) {
		glutSolidTorus(size1, size1 / 2.0, resolution1, resolution1);
		glutSetWindowTitle("SOLID_TORUS");
	} //else if

	glPopMatrix();
	glutSwapBuffers();

} // drawCube

void displayObj() {
	glClearColor(0, 0, 0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Matnonspec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Matspec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Matshiny);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);


	gluLookAt(0, 0, -zoom, 0, 0, 0, 0, 1, 0);
	glRotated(rotateX, 0, 1, 0);
	glRotated(rotateY, 1, 0, 0);
	drawSelectedObject();

	//glutSwapBuffers();
} // displayObj

void keyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 's':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 'p':
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case 'q':
		glShadeModel(GL_SMOOTH);
		break;
	case 'f':
		glShadeModel(GL_FLAT);
		break;

	case 'a':


		break;
	case 'd':

		break;

	case 'g':
		Lt0spec[0] += 0.1;
		Lt0spec[1] += 0.1;
		Lt0spec[2] += 0.1;

		if (Lt0spec[0] > 1.0) {
			Lt0spec[0] = 0.0;
		}

		glLightfv(GL_LIGHT0, GL_AMBIENT, Lt0spec);
		break;
	}

	printoutKeyInfo();
	glutPostRedisplay();
}


static void printoutKeyInfo() {
	std::cout << "curr mode = " << selectedMode1 << " resolution= " << resolution1 << " LIGHT amb= " << Lt0amb[0] << " diff= " << Lt0diff[0] << " spec= " << Lt0spec[0] << std::endl;
} //printoutKeyInfo

void specialKeyFunc(int key, int x, int y) {

	switch (key)
	{
	case GLUT_KEY_UP:
		selectedMode1++;
		if (selectedMode1 > MAX_OBJ_ID) {
			selectedMode1 = 0;
		}
		break;
	case GLUT_KEY_DOWN:
		selectedMode1--;
		if (selectedMode1 < 0) {
			selectedMode1 = MAX_OBJ_ID;
		}
		break;
	case GLUT_KEY_LEFT:
		resolution1 /= 1.1;
		if (resolution1 < MIN_RESOLUTION) {
			resolution1 = MIN_RESOLUTION;
		}
		break;
	case GLUT_KEY_RIGHT:
		resolution1 *= 1.1;
		break;
	}

	printoutKeyInfo();
	glutPostRedisplay();
}


static int ex08_RenderPreDefinedObjects_run(int argc, char* argv[])
{
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(300, 300);
	glutCreateWindow("OpenGL Test");
	glutDisplayFunc(displayObj);
	glutReshapeFunc(resize);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);

	glutKeyboardFunc(keyboardFunc);
	glutSpecialFunc(specialKeyFunc);

	selectedMode1 = 0;
	resolution1 = 10;
	size1 = 2.0;

	glPointSize(4.0);
	glLineWidth(3.0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);		// Enable lighting calculations
	glEnable(GL_LIGHT0);		// Turn on lights (unnecessary here, since also in Animate()

	// Light 0 
	glLightfv(GL_LIGHT0, GL_AMBIENT, Lt0amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Lt0spec);
	glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);


	zoom = -10.0;


	glutMainLoop();
	return 0;
}

