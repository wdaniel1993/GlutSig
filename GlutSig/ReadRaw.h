
#ifndef _READ_RAW_H_
#define _READ_RAW_H_

#include <stdio.h>
#include <iostream>

typedef struct Image3D
{
  unsigned int   width;
  unsigned int   height;
  unsigned int   depth;
  unsigned char***		 data;
} Image3D;


class ReadRaw {
public:
	static Image3D* loadRawImage(FILE *fp, unsigned int width, unsigned int height, unsigned int depth);


}; //class ReadRaw



#endif //_READ_RAW_H_