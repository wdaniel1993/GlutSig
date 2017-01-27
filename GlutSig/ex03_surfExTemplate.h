#ifndef _SURFACE__TEMP_FROM_RAW_FILE_H_
#define _SURFACE__TEMP_FROM_RAW_FILE_H_

#pragma warning( disable : 4996 )


#include "stdafx.h"

#include <iostream>
#include "math.h"
#include "./../lib/glut_3_7_6/glut-3.7.6-bin/glut.h"
#include "BaseGuiFunctionality.h"
#include "ReadRaw.h"
#include <vector>

static Image3D* loadedImage;
static double scaleX;
static double scaleY;
static double scaleZ;


void drawSurface1() {
  std::cout << " draw called ! " << std::endl;
  int fgValue = 255; //100;
  int fgCount = 0;

 // double scaleFactor = 200.0;
  double midX = loadedImage->width / 2.0;
  double midY = loadedImage->height / 2.0;
  double midZ = loadedImage->depth / 2.0;

  glPolygonMode( GL_FRONT, GL_FILL);

  //--------------------- opacity --------------------------------------
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //--------------------- opacity --------------------------------------

  //glColor4d(0.8, 0.15, 0.25, 0.5); 
  glColor4d(0.8, 0.15, 0.25, 1.0); 

  double baseArr1[12] = {0.5, -0.5, 0.5, 0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, 0.5};
  double normArr1[3] = {0, -1, 0}; 

   int surfaceAreaCount = 0;
  for(int xIdx = 0; xIdx < loadedImage->width; xIdx++) {
	for(int yIdx = 0; yIdx < loadedImage->height; yIdx++) {
	  for(int zIdx = 0; zIdx < loadedImage->depth; zIdx++) {
		int actVal = loadedImage->data[xIdx][yIdx][zIdx];
		if(actVal == fgValue) {
		  fgCount++;

		  double currX = (xIdx - midX);
		  double currY = (yIdx - midY);
		  double currZ = (zIdx - midZ);

          int nbX = xIdx + normArr1[0];
		  int nbY = yIdx + normArr1[1];
		  int nbZ = zIdx + normArr1[2];
		  if((nbX >= 0) && (nbX < loadedImage->width) && (nbY >= 0) && (nbY < loadedImage->height) && (nbZ >= 0) && (nbZ < loadedImage->depth)) {
			 //check if neighbour is a bg pixel
			 if(loadedImage->data[nbX][nbY][nbZ] != fgValue) {
			    glBegin(GL_QUADS);
				  glNormal3d(normArr1[0], normArr1[1], normArr1[2]);
                  glVertex3d((currX + baseArr1[0]), (currY + baseArr1[1]) , (currZ + baseArr1[2]) ); 
				  glVertex3d((currX + baseArr1[3]) , (currY + baseArr1[4]) , (currZ + baseArr1[5]) ); 
				  glVertex3d((currX + baseArr1[6]) , (currY + baseArr1[7]) , (currZ + baseArr1[8]) ); 
				  glVertex3d((currX + baseArr1[9]) , (currY + baseArr1[10]) , (currZ + baseArr1[11]) ); 
				glEnd();

				surfaceAreaCount++;
			  } //if
			} //if

        } //if
	  } //for z
	} //for y
  } //for x 

  std::cout << " num of FG values = " << fgCount << " num of surface areas = " << surfaceAreaCount << std::endl;
  glutSwapBuffers();
	
} // drawSurface1

void displaySurface1() {
   
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
	//glShadeModel(GL_FLAT);

   double extentX = loadedImage->width * scaleX;
   double extentY = loadedImage->height * scaleY;
   double extentZ = loadedImage->depth * scaleZ;

   double maxExtent = extentX;
   if(extentY > maxExtent) {
     maxExtent = extentY;
   } //if
   if(extentZ > maxExtent) {
     maxExtent = extentZ;
   } //if

   double aspectRatioSize = 4.0;
   double scaleFactor = 0.7 * aspectRatioSize / maxExtent;

	float lightPosition[] = { 0.0, 0.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	gluLookAt(0, 0, -zoom, 0, 0, 0, 0, 1.0, 0);
	glRotated(rotateX, 0, 1, 0);
	glRotated(rotateY, 1, 0, 0);

	std::cout << " maxExtent = " << maxExtent << " scaleFactor = " << scaleFactor << " scale X = " << (scaleX * scaleFactor) << std::endl;

	//!!!!!!!!!!!!!! SCALING to correct voxel spacing !!!!!!!!!!!!!!!!!!!!!!!!!!
	glScaled(scaleX * scaleFactor, scaleY * scaleFactor, scaleZ * scaleFactor);
	drawSurface1();
	
	//glutSwapBuffers();
} // displaySurface1


static int ex03_surfExTemplate_run(int argc, char* argv[])
{
    glutInit(&argc, argv);

	FILE *fp = fopen(".\\textures\\truncOctahedron_51_51_51.raw", "rb");
	if(fp == 0) {
		return -1;
	} // if
	
	unsigned int width = 51;
	unsigned int height = 51;
	unsigned int depth = 51;

	scaleX = 0.5468;
    scaleY = 0.5468;
    scaleZ = 0.5468;

	loadedImage = ReadRaw::loadRawImage(fp, width, height, depth);
	std::cout << " in image loaded ! " << std::endl;
  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(300, 300);
	glutCreateWindow("OpenGL Surface Rendering Test");
	glutDisplayFunc(displaySurface1);
	glutReshapeFunc(resize);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);

	float lightAmbient[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
	float lightDiffuse[]  = { 0.7f, 0.7f, 0.7f, 1.0f };
	float lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	zoom = -5.0;

	glutMainLoop();
	return 0;
} //SurfaceFromRawFile_run


#endif // _SURFACE__TEMP_FROM_RAW_FILE_H_