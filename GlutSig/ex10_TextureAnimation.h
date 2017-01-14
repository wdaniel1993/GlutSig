#include "stdafx.h"

#include <iostream>
#include "./../lib/glut_3_7_6/glut-3.7.6-bin/glut.h"
#include "bitmap.h"
#include "BaseGuiFunctionality.h"

GLuint textureID = 0;
double rotateZ = 0;

void displayTexturePlane() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//TODO: draw rectangle -------
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float lightPos[] = { 0.0, 0.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


	glTranslated(0, 0, zoom);
	glRotated(rotateX, 0, 1, 0);
	glRotated(rotateY, 1, 0, 0);
	glRotated(rotateZ, 0, 0, 1);

	//TODO: enable texture and build up geometric structure    
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glBegin(GL_QUADS);

	glTexCoord2d(0,0);
	glVertex3d(-20,-20,5);
	glTexCoord2d(0.5,0);
	glVertex3d(0,-20,0);
	glTexCoord2d(0.5,1);
	glVertex3d(0,20,0);
	glTexCoord2d(0,1);
	glVertex3d(-20,20,5);

	glTexCoord2d(1,0);
	glVertex3d(20,-20,5);
	glTexCoord2d(0.5,0);
	glVertex3d(0,-20,0);
	glTexCoord2d(0.5,1);
	glVertex3d(0,20,0);
	glTexCoord2d(1,1);
	glVertex3d(20,20,5);


	glEnd();
	//---------------------------

	glutSwapBuffers();
} // displayTexturePlane

void timer(int value) {
	rotateZ += 0.5;
	glutTimerFunc(value, timer, value);
	std::cout << "rotating to " << rotateZ << " timer interval = " << value << std::endl;
	glutPostRedisplay();
}

static int ex10_TextureAnimation_run(int argc, char* argv[])
{
	glutInit(&argc, argv);
	//TODO: load the file
	FILE *fp = fopen(".\\textures\\Texture2.bmp", "rb");

	if (fp == 0) {
		return -1;
	}

	std::cout << " file open " << std::endl;
	Image img;
	if (!LoadBMP(fp,&img)) {
		return -1;
	}

	std::cout << " bmp successfully loaded " << std::endl;
	std::cout << " w= " << img.width << " h= " << img.height << std::endl;
	std::cout << " pixel at [100] " << (int)img.data[100] << std::endl;


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(300, 300);
	glutCreateWindow("OpenGL Texture and Animation");
	glutDisplayFunc(displayTexturePlane);

	glutReshapeFunc(resize);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutTimerFunc(80, timer, 10);

	//prepare usage of textures
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, img.width, img.height, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	std::cout << "texture ID = " << textureID << std::endl;


	//free(img.data);

	glutMainLoop();
	return 0;
}