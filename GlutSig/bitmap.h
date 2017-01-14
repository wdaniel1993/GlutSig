#ifndef __BITMAP_H__
#define __BITMAP_H__

#include <stdio.h>

#define CFG_LITTLE_ENDIAN

typedef struct image
{
  unsigned int   width;
  unsigned int   height;
  unsigned char *data;
} Image;

extern bool LoadBMP (FILE *fp, Image *image);
extern void SaveBMP (FILE *fp, Image *image);

#endif
