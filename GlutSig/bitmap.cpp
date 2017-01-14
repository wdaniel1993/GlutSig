#include "stdafx.h"

#include <stdlib.h>
#include <stdio.h>
#include "bitmap.h"

/* -------------------------------------------------------------------------- */

typedef unsigned char	BYTE;
typedef unsigned short	WORD;
typedef unsigned long 	DWORD;
typedef long		LONG;
typedef unsigned short	UINT;

typedef struct tagBITMAPFILEHEADER
{
    UINT    bfType;
    DWORD   bfSize;
    UINT    bfReserved1;
    UINT    bfReserved2;
    DWORD   bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    DWORD   biSize;
    LONG    biWidth;
    LONG    biHeight;
    WORD    biPlanes;
    WORD    biBitCount;
    DWORD   biCompression;
    DWORD   biSizeImage;
    LONG    biXPelsPerMeter;
    LONG    biYPelsPerMeter;
    DWORD   biClrUsed;
    DWORD   biClrImportant;
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD
{
    BYTE    rgbBlue;
    BYTE    rgbGreen;
    BYTE    rgbRed;
    BYTE    rgbReserved;
} RGBQUAD;

/* constants for the biCompression field */
#define BI_RGB      0L
#define BI_RLE8     1L
#define BI_RLE4     2L

/* -------------------------------------------------------------------------- */

#ifdef CFG_BIG_ENDIAN
#define READ2(x) swpread2((char*)&x,fp);
#define WRITE2(x) swpwrite2((char*)&x,fp);
#define READ4(x) swpread4((char*)&x,fp);
#define WRITE4(x) swpwrite4((char*)&x,fp);
#else
#define READ2(x) fread((char*)&x,2,1,fp);
#define WRITE2(x) fwrite((char*)&x,2,1,fp);
#define READ4(x) fread((char*)&x,4,1,fp);
#define WRITE4(x) fwrite((char*)&x,4,1,fp);
#endif

void swpread2 (char* p, FILE *fp)
 {
  char s[2];
  fread (&s, 2, 1, fp);
  p[0]=s[1];
  p[1]=s[0];
 }

void swpread4 (char* p, FILE *fp)
 {
  char s[4];
  fread (&s, 4, 1, fp);
  p[0]=s[3];
  p[1]=s[2];
  p[2]=s[1];
  p[3]=s[0];
 }

void swpwrite2 (char* p, FILE *fp)
 {
  char s[2];
  s[0]=p[1];
  s[1]=p[0];
  fwrite (&s, 2, 1, fp);
 }

void swpwrite4 (char* p, FILE *fp)
 {
  char s[4];
  s[0]=p[3];
  s[1]=p[2];
  s[2]=p[1];
  s[3]=p[0];
  fwrite (&s, 4, 1, fp);
 }

/* -------------------------------------------------------------------------- */

void ReadFileHeader (FILE *fp, BITMAPFILEHEADER *hd)
 {
  READ2(hd->bfType);
  READ4(hd->bfSize);  
  READ2(hd->bfReserved1);
  READ2(hd->bfReserved2);
  READ4(hd->bfOffBits);
 }

void ReadInfoHeader (FILE *fp, BITMAPINFOHEADER *hd)
 {
  READ4(hd->biSize);
  READ4(hd->biWidth);
  READ4(hd->biHeight);
  READ2(hd->biPlanes);
  READ2(hd->biBitCount);
  READ4(hd->biCompression);
  READ4(hd->biSizeImage);
  READ4(hd->biXPelsPerMeter);
  READ4(hd->biYPelsPerMeter);
  READ4(hd->biClrUsed);
  READ4(hd->biClrImportant);
 }

void WriteFileHeader (FILE *fp, BITMAPFILEHEADER *hd)
 {
  WRITE2(hd->bfType);
  WRITE4(hd->bfSize);  
  WRITE2(hd->bfReserved1);
  WRITE2(hd->bfReserved2);
  WRITE4(hd->bfOffBits);
 }

void WriteInfoHeader (FILE *fp, BITMAPINFOHEADER *hd)
 {
  WRITE4(hd->biSize);
  WRITE4(hd->biWidth);
  WRITE4(hd->biHeight);
  WRITE2(hd->biPlanes);
  WRITE2(hd->biBitCount);
  WRITE4(hd->biCompression);
  WRITE4(hd->biSizeImage);
  WRITE4(hd->biXPelsPerMeter);
  WRITE4(hd->biYPelsPerMeter);
  WRITE4(hd->biClrUsed);
  WRITE4(hd->biClrImportant);
 }

/* -------------------------------------------------------------------------- */

bool LoadBMP (FILE *fp, Image *image)
 {
  BITMAPFILEHEADER filehd;
  BITMAPINFOHEADER bmphd;
  int bpr, y, a;
  unsigned char *p;

  ReadFileHeader (fp, &filehd);
  if (filehd.bfType != 0x4d42)
   {
    fprintf (stderr, "LoadBMP: invalid file signature\n");
    return false;
   }
  ReadInfoHeader (fp, &bmphd);
  if (bmphd.biCompression != BI_RGB)
   {
    fprintf (stderr, "LoadBMP: can't read compressed bitmaps\n");
    return false;
   }
  if (bmphd.biBitCount!=8)
   {
    fprintf (stderr, "LoadBMP: 8 bit image expected, got %d bit\n",bmphd.biBitCount);
   }
   
  long bits = (bmphd.biBitCount / 8);
  bpr = (bmphd.biWidth * bits) + ((bmphd.biWidth * bits) % 4);
  image->width = bmphd.biWidth;
  image->height= bmphd.biHeight;
  image->data = (unsigned char*)malloc(image->width*image->height*bits);
  p=image->data;
  for (y=0; y<(int)image->height; y++)
   {
    fread (p, 1, (image->width*bits), fp);
    p+=(image->width*bits);
    if (bpr>(int)image->width*bits)
      fseek (fp, bpr-image->width*bits, SEEK_CUR);
   }
  for(a = 0; a < (int)(image->width*image->height*bits); a += 3) {
    unsigned char temp = image->data[a];
    image->data[a] = image->data[a+2];
    image->data[a+2] = temp;
  }

  return true;
 }

/* -------------------------------------------------------------------------- */

void SaveBMP (FILE *fp, Image *image)
 {
  BITMAPFILEHEADER filehd;
  BITMAPINFOHEADER bmphd;
  int bpr, i;
  unsigned char *p;
  long l0=0;
  RGBQUAD rq;

  bpr=((((long)image->width*8+31L)/32L)*4L);

  filehd.bfType         = 0x4d42;
  filehd.bfSize         = 54+1024+bpr*image->height;
  filehd.bfReserved1    = 0;
  filehd.bfReserved2    = 0;
  filehd.bfOffBits      = 54+1024;
  WriteFileHeader (fp, &filehd);

  bmphd.biSize          = 40;
  bmphd.biWidth         = image->width;
  bmphd.biHeight        = image->height;
  bmphd.biPlanes        = 1;
  bmphd.biBitCount      = 8;
  bmphd.biCompression   = BI_RGB;
  bmphd.biSizeImage     = 0;
  bmphd.biXPelsPerMeter = 0;
  bmphd.biYPelsPerMeter = 0;
  bmphd.biClrUsed       = 0;
  bmphd.biClrImportant  = 0;
  WriteInfoHeader (fp, &bmphd);

  /* write graymap */
  rq.rgbReserved=0;
  for (i=0; i<256; i++)
   {
    rq.rgbBlue=i;
    rq.rgbGreen=i;
    rq.rgbRed=i;
    fwrite (&rq, sizeof(RGBQUAD), 1, fp);
   }

  p=image->data+image->width*image->height;
  for (i=0; i<(int)image->height; i++)
   {
    p-=image->width;
    fwrite (p, 1, image->width, fp);
    if (bpr>(int)image->width)
      fwrite (&l0, 1, bpr-image->width, fp);
   }
 }

/* -------------------------------------------------------------------------- */
