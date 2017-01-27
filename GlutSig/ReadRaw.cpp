#include "stdafx.h"
#include "ReadRaw.h"

Image3D* ReadRaw::loadRawImage(FILE *fp, unsigned int width, unsigned int height, unsigned int depth) {
  Image3D* retImg = new Image3D();
  retImg->width = width;
  retImg->height = height;
  retImg->depth = depth;

  std::cout << "loadRawImage called! w=" << width << " h=" << height << " d=" << depth << std::endl;

  //first allocate the 3D char array 
  retImg->data = new unsigned char**[width];
  for(int xIdx = 0; xIdx < width; xIdx++) {
	retImg->data[xIdx] = new unsigned char*[height];
	for(int yIdx = 0; yIdx < height; yIdx++) {
	  retImg->data[xIdx][yIdx] = new unsigned char[depth];
	  for(int zIdx = 0; zIdx < depth; zIdx++) {
		retImg->data[xIdx][yIdx][zIdx] = 0;
	  } //for
	} //for y
  } //for x

  std::cout << " data allocated ! " << std::endl;

  double sum = 0;
  int pixelCount = 0;
  int minVal = 10000;
  int maxVal = -10000;

  unsigned char* inArr = new unsigned char[width * height * depth];
  unsigned char *p = inArr;


  //unsigned char* currVal = new unsigned char[1];
  int numOfPixel = width * height * depth;
  for(int i = 0; i < numOfPixel; i++) {
    fread (p, 1, 1, fp);
    p+=1; 
  } //for

  for(int zIdx = 0; zIdx < depth; zIdx++) {
	for(int yIdx = 0; yIdx < height; yIdx++) {
	  for(int xIdx = 0; xIdx < width; xIdx++) {	  
	    int currIntVal = inArr[pixelCount];
		retImg->data[xIdx][yIdx][zIdx] = currIntVal;
		sum += currIntVal;
		if(currIntVal > maxVal) {
		  maxVal = currIntVal;
		} //if
		if(currIntVal < minVal) {
		  minVal = currIntVal;
		} //if
		pixelCount++;
		
	  } //for x
	} //for y
  } //for z

  delete inArr;


  sum/= ((double)pixelCount);
  std::cout << " minVal= " << minVal << " maxVal= " << maxVal << " avg= " << sum << " #pixels= " << pixelCount << std::endl;


  return retImg;
} //loadRawImage