#ifndef _BMP_ 
#define _BMP_/*
$Rev: 23 $
$Date: 2007-10-01 15:33:21 +0200 (Mo, 01 Okt 2007) $:
$Author: Hielen $:
*/
//---------------------------------------------------------------------------

int Save8BitGrayscaleBmp(char * filename, long wid, long hei, short *image);

#define ERR_OPENFILE                        -1
#define ERR_READBITMAPFILEHEADER            -2
#define ERR_READBITMAPINFOHEADER            -3
#define ERR_NOTABMPFILE                     -4

typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef long LONG;
//typedef char BYTE;

#define CHUNK 16384

//---------------------------------------------------------------------------
#pragma pack(1)

typedef struct 
{
    WORD bfType;
    DWORD  bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD  bfOffBits;
} STRUCT_BMPFILEHEADER;


//---------------------------------------------------------------------------

#pragma pack(1)



typedef struct
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
} STRUCT_BMPINFOHEADER;


#pragma pack(1)

typedef struct
{
    char R,G,B,dummy;
} STRUCT_RGBQUAD;


//---------------------------------------------------------------------------
//- Hilfstruktur, um innerhalb eines Speicherbereiches eine Bitmap zu
//- zu erzeugen.
//---------------------------------------------------------------------------

typedef struct
{
    STRUCT_BMPFILEHEADER bitmapfileheader;
    STRUCT_BMPINFOHEADER bitmapinfoheader;
    STRUCT_RGBQUAD colormap[256];
} STRUCT_8BITGRAYSCALEBITMPA_PREAMBLE;

//---------------------------------------------------------------------------

#endif //_BMP_
