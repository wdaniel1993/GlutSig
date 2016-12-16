// TestOpenGL1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "./../lib/glut_3_7_6/glut-3.7.6-bin/glut.h"
#include "BaseGuiFunctionality.h"

void addVertex(double vertArr[8][3], double colorArr[8][3], int idx) {
  glColor3d(colorArr[idx][0], colorArr[idx][1], colorArr[idx][2]);
  glVertex3d(vertArr[idx][0], vertArr[idx][1], vertArr[idx][2]);
} //addVertex

void drawCube() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	double vertArr[8][3] = { { -1, -1, 1}, 
		                     { 1, -1, 1}, 
							 { 1, -1, -1}, 
							 { -1, -1, -1}, 
							 { -1, 1, 1}, 
							 { 1, 1, 1}, 
							 { 1, 1, -1}, 
							 { -1, 1, -1}	
	                        };

  
	double colorArr[8][3] = {{0.0, 0.0, 0.0} ,
	                         {1.0, 0.0, 0.0} ,
							 {1.0, 1.0, 0.0} ,
							 {0.0, 1.0, 0.0}, 
							 {0.0, 1.0, 1.0}, 
							 {0.0, 0.0, 1.0}, 
							 {1.0, 0.0, 1.0}, 
							 {1.0, 1.0, 1.0} }; 


	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

	
	glBegin(GL_QUADS);
	   //upper part of cube
       addVertex(vertArr, colorArr, 0);
	   addVertex(vertArr, colorArr, 1);
	   addVertex(vertArr, colorArr, 5);
	   addVertex(vertArr, colorArr, 4);

	   //lower part of cube
	   addVertex(vertArr, colorArr, 3);
	   addVertex(vertArr, colorArr, 2);
	   addVertex(vertArr, colorArr, 6);
	   addVertex(vertArr, colorArr, 7);
	 

	   //front part of cube
	   addVertex(vertArr, colorArr, 4);
	   addVertex(vertArr, colorArr, 5);
	   addVertex(vertArr, colorArr, 6);
	   addVertex(vertArr, colorArr, 7);
	   

	   //back part of cube
	   addVertex(vertArr, colorArr, 0);
	   addVertex(vertArr, colorArr, 1);
	   addVertex(vertArr, colorArr, 2);
	   addVertex(vertArr, colorArr, 3);
	  	

	   //left part of cube
	   addVertex(vertArr, colorArr, 0);
	   addVertex(vertArr, colorArr, 3);
	   addVertex(vertArr, colorArr, 7);
	   addVertex(vertArr, colorArr, 4);
	  	 
	   
	   //right part of cube
	   addVertex(vertArr, colorArr, 1);
	   addVertex(vertArr, colorArr, 2);
	   addVertex(vertArr, colorArr, 6);
	   addVertex(vertArr, colorArr, 5);
	  	  

	glEnd();

	//line - wire frame
	glLineWidth(4.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	glColor3d(1.0, 0.0,1.0);
	glTranslated(4.0, 0, 0);
	glutSolidCube(2.0);
	glPopMatrix();

	//points
	glPointSize(6.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glPushMatrix();
	glColor3d(0.0, 1.0, 1.0);
	glTranslated(0.0, -4.0, 0);
	glutSolidCube(2.0);
	glPopMatrix();

	//rotated solid cube
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glColor3d(1.0, 0.5, 0.7);
	glTranslated(-4.0, 0.0, 0);
	glRotated(25.0, 1.0, 0.5, 0.5);
	//glutSolidCube(2.0);
	glutSolidCone(1.0, 2.0, 10.0, 10.0);
	glPopMatrix();


	
	//glColor3d(1.0, 1.0, 0.0);
	
} // drawCube

void displayCube() {
   
   glClearColor(0, 0, 0, 1.0);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
	
	float lightPosition[] = { 0.0, 0.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	gluLookAt(0, 0, -zoom, 0, 0, 0, 0, 1, 0);
	glRotated(rotateX, 0, 1, 0);
	glRotated(rotateY, 1, 0, 0);
	drawCube();
	
	glutSwapBuffers();
} // displayCube


static int FirstCubeExample_run(int argc, char* argv[])
{
glutInit(&argc, argv);	
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA );
	glutInitWindowSize(300, 300);
	glutCreateWindow("OpenGL Cube");
	glutDisplayFunc(displayCube);
	glutReshapeFunc(resize);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);

	
	float lightAmbient[]  = { 0.4f, 0.4f, 0.4f, 1.0f };
	float lightDiffuse[]  = { 0.5f, 0.5f, 0.5f, 1.0f };
	float lightSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	zoom = -10.0;


	glutMainLoop();
	return 0;
}

