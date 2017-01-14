#include "./../lib/glut_3_7_6/glut-3.7.6-bin/glut.h"
#include "BaseGuiFunctionality.h"

bool anaglyphMode1 = true;

void drawStereoObjects1() {

	GLUquadricObj *quad = gluNewQuadric();
	if (anaglyphMode1) {
		glColor3d(0.9, 0.9, 0.9);
	} // if
	else {
		glColor3d(1.0, 1.0, 0.0);
	} // else

	glPushMatrix();
	glTranslated(-2, -6.0, 0);
	gluDisk(quad, 1.0, 2.0, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0.0, 0);
	gluDisk(quad, 1.0, 2.0, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslated(2, 6.0, 0);
	gluDisk(quad, 1.0, 2.0, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2, -6.0, 4);
	gluCylinder(quad, 2.0, 2.0, 4.0, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0.0, 4);
	gluCylinder(quad, 2.0, 2.0, 4.0, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslated(2, 6.0, 4);
	gluCylinder(quad, 2.0, 2.0, 4.0, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2, -6.0, -4);
	gluSphere(quad, 2.0, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0.0, -4);
	gluSphere(quad, 2.0, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslated(2, 6.0, -4);
	gluSphere(quad, 2.0, 100, 100);
	glPopMatrix();

	gluDeleteQuadric(quad);
} // drawObjects

void displayS1() {
	if (anaglyphMode1) {
		glClearColor(0.7, 0, 0.7, 1.0);
	} // if
	else {
		glClearColor(0, 0, 0, 1.0);
	} // else
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glShadeModel(GL_FLAT);

	//float lightPosition[] = { 0.0, 0.0, 1.0, 0.0 };
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	if (anaglyphMode1) {

		//glClear(GL_DEPTH_BUFFER_BIT);
		glColorMask(GL_FALSE, GL_FALSE, GL_TRUE, GL_TRUE);
		glPushMatrix();
		gluLookAt(1.2, 0, -zoom, 0, 0, 0, 0, 1, 0);
		glRotated(rotateX, 0, 1, 0);
		glRotated(rotateY, 1, 0, 0);
		drawStereoObjects1();
		glPopMatrix();

		glClear(GL_DEPTH_BUFFER_BIT);
		glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
		glPushMatrix();
		gluLookAt(-1.2, 0, -zoom, 0, 0, 0, 0, 1, 0);
		glRotated(rotateX, 0, 1, 0);
		glRotated(rotateY, 1, 0, 0);
		drawStereoObjects1();
		glPopMatrix();

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

		//glClear(GL_DEPTH_BUFFER_BIT);
		/*	glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
		glPushMatrix();
		gluLookAt(+0.2, 0, -zoom, 0, 0, 0, 0, 1, 0);
		glRotated(rotateX, 0, 1, 0);
		glRotated(rotateY, 1, 0, 0);
		drawStereoObjects1();
		glPopMatrix();
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); */
	} // if
	else {
		//glTranslated(0, 0, zoom);
		gluLookAt(0, 0, -zoom, 0, 0, 0, 0, 1, 0);
		glRotated(rotateX, 0, 1, 0);
		glRotated(rotateY, 1, 0, 0);
		drawStereoObjects1();
	} // else

	glutSwapBuffers();
} // display


int ex11_AnaglyphTest_run(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(300, 300);
	glutCreateWindow("OpenGL Test");
	glutDisplayFunc(displayS1);
	glutReshapeFunc(resize);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);

	float lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float lightDiffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glutMainLoop();
	return 0;
} // main