//---------------------------------------------------------------------------

#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/********************************************************************************
 * Save8BitGrayscaleBmp															*
 ********************************************************************************
 * BESCHREIBUNG:														 		*
 * 	Funktion speichert ein 8-Bit Graustufen-Bild im BMP-Format					*
 ********************************************************************************
 * UEBERGABEPARAMETER:															*
 * 	char *filename = String-Ptr auf den Dateinamen	des zu speichernden Bildes	*
 *  long wid = Bildbreite														*
 *  long hei = Bildhoehe														*
 *  char *image = Ptr auf die Bilddaten											*
 ********************************************************************************
 * RUECKGABEPARAMETER:															*
 *	<0= Fehler beim Speichern.													*
 *   1 = Alles Ok.																*
 ********************************************************************************/

int Save8BitGrayscaleBmp(char * filename, long wid, long hei, short *image)
{
    int i,y;
    long lResult;
    long wid_step; /* Tats�hlicher Platzbedarf einer Bildzeile zwecks Alignment */
    long alignpixels;
    
    //unsigned char * pixel_buffer;
    FILE * filehandle = NULL;
    STRUCT_BMPFILEHEADER bitmapfileheader;
    STRUCT_BMPINFOHEADER bitmapinfoheader;
    STRUCT_RGBQUAD colorquad;
    unsigned char *puc_temp;
    puc_temp = calloc(1,wid*hei);
    if (puc_temp==NULL)
        return -1;
   
    /* Datei erzeugen, eine vorhandene Datei berschreiben */
	//pixel_buffer = (unsigned char *)FRAMEBUFFER_BASE;
    filehandle = fopen(filename,"wb+");
    if (filehandle==NULL)
	{
	free(puc_temp);
        return ERR_OPENFILE;
	}
	//setbuf(filehandle, pixel_buffer);
    /* Platzbedarf einer Zeile berechnen; hier ist die Pixelzahl immer ein vielfaches von 4 */
    wid_step=wid;
    //wid_step=(wid_step/4)*4;
    alignpixels=0;
    /*
	if (wid_step<wid)
    {
        wid_step+=4;
        alignpixels=wid_step-wid;
    }
	*/
    /* Bitmap-FileHeader ausfllen und schreiben */
    bitmapfileheader.bfType=0x4d42;
    bitmapfileheader.bfReserved1=0;
    bitmapfileheader.bfReserved2=0;
    bitmapfileheader.bfOffBits=sizeof(bitmapfileheader)+sizeof(bitmapinfoheader)+1024; /* 1024 ist die Gr�e der ColorMap */
    bitmapfileheader.bfSize=bitmapfileheader.bfOffBits+wid_step*hei;
    lResult=fwrite(&bitmapfileheader,sizeof(bitmapfileheader),1,filehandle);

    /* Bitmap-InfoHeader schreiben */
    bitmapinfoheader.biSize=sizeof(bitmapinfoheader);
    bitmapinfoheader.biWidth=wid;
    bitmapinfoheader.biHeight=-hei;
    bitmapinfoheader.biPlanes=1;
    bitmapinfoheader.biBitCount=8;
    bitmapinfoheader.biCompression=0;
    bitmapinfoheader.biSizeImage=wid_step*hei;
    bitmapinfoheader.biXPelsPerMeter=2834;
    bitmapinfoheader.biYPelsPerMeter=2834;
    bitmapinfoheader.biClrUsed=256;
    bitmapinfoheader.biClrImportant=256;
    lResult=fwrite(&bitmapinfoheader,sizeof(bitmapinfoheader),1,filehandle);

    /* RGB_QUADS schreiben */
    for (i=0; i<256; i++)
    {
        colorquad.R=i;
        colorquad.G=i;
        colorquad.B=i;
        colorquad.dummy=0;
        lResult=fwrite(&colorquad,sizeof(colorquad),1,filehandle);
    }
    /* Bilddatenschreiben */

	//test_buffer = image;
	i = wid*hei;
    for (y=0; y<hei; y+=1)
    {

	for (i = 0 ; i < wid ; i++)
	  {
	    puc_temp[i] = (unsigned char)(image[i] >> 2);
	  }
	fwrite(puc_temp,1,wid,filehandle);
	image += wid;
    }
	
   
    fflush(filehandle);
    fclose (filehandle);
     free(puc_temp);

    return 1;
}
