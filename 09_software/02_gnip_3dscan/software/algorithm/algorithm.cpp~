/**
	@file		quad_test_client.cpp
	@author	Christoph Gnip
	@date		16. Februar 2010 a. D.
	@brief	Autonomer Testclient für die Software der RedCam2 sowie die MiniQuadrix
	@version 	0.1

Dieser Client ermöglicht einen semi- autonomen Test des Miniquadrix- und des RedCam2- Servers.
Zusätzlich wird selbständig ein Protokoll geschrieben.

*/
#include <stdint.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>

/*
	Defines
*/
#define NUM_OF_IMGAGES 4

// #define DISPLAY_USAGE \
// 	printf("qdrx_client [ip] [logfile] [testmethod]\n \
// 	testmethod can be:\n\
// 		1 ->\t Automomus Test\n \
// 		2 ->\t Extern TriggerTest\n \
// 		3 ->\t Normal Trigger Test\n \
// 		4 ->\t Change IP to 192.168.1.181 after reboot\n \
// 		5 ->\t Livemodus \n\
// 		6 ->\t Change MAC to DEFAULT_MAC_ASDDRESS (00:07:ED:00:00:00) after reboot \n \
// 		7 ->\t Laser on \n \
// 		8 ->\t Laser off \n \
// 		9 ->\t Set Laser Pulsese\n \
// 		any ->\t Default Test\n \
// \n"); \
// 	exit(0)

/* Include der OpenCV- lib */
#include "/home/christoph/dev/OpenCV-2.0.0/include/opencv/cv.h"
#include "/home/christoph/dev/OpenCV-2.0.0/include/opencv/highgui.h"

/* Define the light direction */
#define	LEFT		0
#define	BOTTOM	1
#define	TOP		2
#define	RIGHT		3
#define	SHADOW	0xFFFFFFFF

/** @def PX_ANGLE_SCALING_FACTOR Angle resolution [deg/pxs] */
#define PX_ANGLE_SCALING_FACTOR	0.02
/** @def PX_ANGLE_SCALING_FACTOR_RAD_INT1 Angle resolution [rad/pxs] */
#define PX_ANGLE_SCALING_FACTOR_RAD_INT1 0.00036
/** @def PX_ANGLE_SCALING_FACTOR_RAD_INT2 Angle resolution [rad/pxs] */
#define PX_ANGLE_SCALING_FACTOR_RAD_INT2 0.00035
/** @def PX_RES Resolution of a single pixel [mm/pxs] */
#define PX_RES				0.1667

//g++ algorithm.cpp -o 3d_recon -I /usr/local/include/opencv -L /usr/local/lib -lm -lcv -lhighgui -lcvaux -lpthread

typedef struct offset {
	int x_offs;
	int y_offs;
} t_offs;

t_offs t_offset[4];
/*
	Funktionsprototypen
*/
int			PicRot90Deg( unsigned char *pic,
					 int img_width,
					 int img_height,
					 unsigned char *dest_pic,
					 int times );

void			save_PicturesAsBmp_cv( unsigned char *ucPictures,
						     const unsigned int *uiRes,
						     unsigned int uiLen,
						     unsigned char *ucPath );

void			release_ImageSets( void );
int			init_ImageSetsGrayscale( int i_height, int i_width );
void			invert_Image( IplImage * img );
void			invert_ImageSet( IplImage * imgSet[] );
int			takeReferenceShot( int i_numberImages );
void			save_ImageSets( char *cDest );
void			*reconstruct_img( void *_name );
void			*correct_img( void *_name );
char get_height( int current_col, int shadow_len );

/*
	Globales
*/

char _picstart = 0;
int _count = 0;
IplImage	*ReconResult[ NUM_OF_IMGAGES ];
IplImage	*SingleMerge[ NUM_OF_IMGAGES ];
IplImage	*FinalMerge;
pthread_t 	th_recon_sng_image[ NUM_OF_IMGAGES ];
pthread_t 	th_img_correction[ NUM_OF_IMGAGES ];

int main( int argc, char *argv[ ] )
{
	int i = 0;
	int width = 0;
	int height = 0;
	char file[ 200 ];
	int offset[ 4 ];
	char *PicP;
	char *p1;
	char *p2;
	char *p3;
	char *p4;
	double *PicPdbl;

	/* checking parameter */
	/* expecting: 3d_recon picstart width height */
	if( argc < 4 ) {
		printf( "Error\n" );
		exit( -1 );

	}
	_picstart = atoi( argv[ 1 ] );
	width = atoi( argv[ 2 ] );
	height = atoi( argv[ 3 ] );

	init_ImageSetsGrayscale( height, width );

	t_offset[ 0 ].x_offs = -5;
	t_offset[ 0 ].y_offs = -3;

	t_offset[ 1 ].x_offs = -4;
	t_offset[ 1 ].y_offs = -4;

	t_offset[ 2 ].x_offs = 5;
	t_offset[ 2 ].y_offs = 2;

	t_offset[ 3 ].x_offs = 1;
	t_offset[ 3 ].y_offs = 2;
	
// 	printf("Correcting the images...\n... \r" );
	/* do image correction */
// 	do {
// 		/* Launch the single Image reconstruction */
// 		for( i = 0; i < NUM_OF_IMGAGES; i++ ) {
// 			pthread_create( &th_img_correction[ i ],
// 							NULL,
// 						      correct_img,
// 							( void *) i );
// 
// 		}
// 
// 		/* wait 'til reconstruction threads are ready */
// 		for( i = 0; i < NUM_OF_IMGAGES; i++ ) {
// 			pthread_join( th_img_correction[ i ], NULL );
// 
// 		}
// 		_count++;
// 
// 	} while( _count < NUM_OF_IMGAGES );
// 	printf( "Image corrected\n" );

	printf( "Processing shadow information from images...\n...\r" );
	/* do processing shadow information */
	_count = 0;
	do {
		/* Launch the single Image reconstruction */
		for( i = 0; i < NUM_OF_IMGAGES; i++ ) {
			pthread_create( &th_recon_sng_image[ i ],
							NULL,
						      reconstruct_img,
							( void *) i );

		}

		/* wait 'til reconstruction threads are ready */
		for( i = 0; i < NUM_OF_IMGAGES; i++ ) {
			pthread_join( th_recon_sng_image[ i ], NULL );

		}
		_count++;

	} while( _count < NUM_OF_IMGAGES );

	printf("Merging images...\n...\r" );
	/* do Merge of the Single Images */

	for( i = 0; i < NUM_OF_IMGAGES; i++ )
		cvReleaseImage( &ReconResult[ i ] );

	_count = 0;
	do {
// 		SingleMerge[ _count ] = cvCreateImage( cvSize( ( width / 2 ) * 3, ( height /2 ) * 3 ), IPL_DEPTH_8U, 1 );
		SingleMerge[ _count ] = cvCreateImage( cvSize( width, height ), IPL_DEPTH_8U, 1 );

		if( SingleMerge[ _count ] == NULL )
			return -1;
		memset( SingleMerge[ _count ]->imageData,
			  0x00,
			  ( SingleMerge[ _count ]->height *
				  SingleMerge[ _count ]->width *
				  sizeof( unsigned char ) )
			  );

		/* Load the images with the processed shadow information */
		for( i = 0; i < NUM_OF_IMGAGES; i++ ) {
			sprintf( file, "img/result_%i_%i_%i.bmp", _picstart, i, _count );
			ReconResult[ i ] = cvLoadImage( file, 0 );
			if( ReconResult[ i ] == NULL ) {
				printf( "Unable to load file: %s for merging\n", file );
				exit( -1 );

			}
		}

		offset[ 0 ] = 0;
		offset[ 1 ] = 0;
		offset[ 2 ] = 0;
		offset[ 3 ] = 0;

		PicP = SingleMerge[ _count ]->imageData;
		for( int k = 0; k < NUM_OF_IMGAGES; k++ ) {
		/* Images */
			for( int j = 0; j < 480; j++ ) {
			/* Rows */
				for( i = 0; i < 480; i++ ) {
				/* Columns */
					*( PicP + offset[ k ] + i + j * SingleMerge[ _count ]->width ) += (char)
							(double) ReconResult[ k ]->imageData[ i + j * ReconResult[ k ]->width ] * 0.3;

				}
			}
		}
		sprintf( file, "img/singleMerge_%i_%i.bmp", _picstart, _count );
		cvSaveImage( file, SingleMerge[ _count ] );
		_count++;

	} while( _count < NUM_OF_IMGAGES );

	/* Merge the single images to 1 final */
	for( i = 0; i < NUM_OF_IMGAGES; i++ )
		cvReleaseImage( &ReconResult[ i ] );

	/* Load the images with the processed shadow information */
	for( i = 0; i < NUM_OF_IMGAGES; i++ ) {
		sprintf( file, "img/singleMerge_%i_%i.bmp", _picstart, i );
		ReconResult[ i ] = cvLoadImage( file, 0 );
		if( ReconResult[ i ] == NULL ) {
			printf( "Unable to load file: %s for merging\n", file );
			exit( -1 );

		}
	}
	FinalMerge = cvCreateImage( cvSize( ( width / 2 ) * 3, ( height /2 ) * 3 ), IPL_DEPTH_64F, 1 );
	if( FinalMerge == NULL )
			return -1;
	memset( FinalMerge->imageData,
		  0x00,
		  ( FinalMerge->height *
			  FinalMerge->width *
			  sizeof( unsigned char ) )
		  );
// 	memcpy( FinalMerge->imageData, ReconResult[ 1 ]->imageData, ReconResult[ 1 ]->width * ReconResult[ 1 ]->height );


	/*
	 * layout of the images are located in the final image...
	 *  ----------
	 * |1    3    |
	 * |          |
	 * |0    4    |
	 * |          |
	 *  ----------
	 *
	 * Now calculate an offset for the automatic merge
	 *
	 */
	offset[ 2 ] = ( width / 2 );

	offset[ 0 ] = ( 720 * ( height / 2 ) );

	offset[ 3 ] = offset[ 0 ];
	offset[ 3 ] += offset[ 2 ];

	PicPdbl = (double *) FinalMerge->imageData;
	for( int k = 0; k < NUM_OF_IMGAGES; k++ ) {
	/* Images */
// 	if( k == 1) continue;
		for( int j = 0; j < 480 ;j++ ) {
		/* Rows */
			for( i = 0; i < 480; i++ ) {
			/* Columns */
				*( PicPdbl + offset[ k ] + i + j * SingleMerge[ _count ]->width ) +=
						(double) (ReconResult[ k ]->imageData[ i + j * ReconResult[ k ]->width ]  );
			}
		}
	}

	sprintf( file, "img/finalMerge_%i.bmp", _picstart );
	cvSaveImage( file, FinalMerge );

	printf("Merge complete...Images saved...\n" );

	release_ImageSets( );
	return 0; 

} //Main End

/**
	@fn void *correct_img( void *_name )
	@brief Functions corrects the offets of the images
	@param *_name Thou void, it contains a number indicating wich Thread it is


*/
void *correct_img( void *_name ) {
	IplImage *Image;
	char file[200];
	char *cp_orig;
	unsigned char *ucp_temp_img;
	double *dbl_res;
	int iCol = 0;
	int iRow = 0;
	int i = 0;
	int shadow_len = 0; /**< Described as delta_x */
	char shadow_flag = 0;
	long img_no;
	img_no = (long) _name;

	FILE *fp;

	sprintf( file, "img/ds_%i_%i_%li.bmp", _picstart, _count, img_no );

	/* Load the image */
	Image = cvLoadImage( file, 0 );
	if( Image == NULL ) {
		printf( "[%li]\tCould not load picture: %s\n", img_no, file );
		exit( 0 );

	}
	ucp_temp_img = ( unsigned char* ) malloc( Image->height * Image->width );
	memset( ucp_temp_img, 0x00, Image->height * Image->width );

	cp_orig = ( char * ) Image-> imageData;

	/* Linescan the Picture */
	for( iRow = 0; iRow < Image->height; iRow++ ) {
		if( iRow >  t_offset[ img_no ].y_offs ) {
			for( iCol = 0; iCol < Image->width; iCol++ ) {
				if( iCol > t_offset[ img_no ].x_offs ) {
					*ucp_temp_img = *( cp_orig );

				}

			}
		}
	}
	cvSaveImage( file, ReconResult[ img_no ] );

	cvReleaseImage( &Image );


	/* ready; image correction */

}

/**
	@fn void *reconstruct_img( void *_name )
	@brief Functions called as thread several times; processes the shadow information
	@param *_name Thou void, it contains a number indicating wich Thread it is
	

*/
void *reconstruct_img( void *_name ) {
	IplImage *Image;
	char file[200];
	char *cp_orig;
	char *cp_res;
	unsigned char *ucp_temp_img;
// 	double *dbl_res;
	int iCol = 0;
	int iRow = 0;
	int i = 0;
	int shadow_len = 0; /**< Described as delta_x */
	char shadow_flag = 0;
	long img_no;
	img_no = (long) _name;

	FILE *fp;
	
	sprintf( file, "img/%i_%i_%li.bmp", _picstart, _count, img_no );

	/* Load the image */
	Image = cvLoadImage( file, 0 );
	if( Image == NULL ) {
		printf( "[%li]\tCould not load picture: %s\n", img_no, file );
		exit( 0 );

	}
	ucp_temp_img = ( unsigned char* ) malloc( Image->height * Image->width );
	memset( ucp_temp_img, 0x00, Image->height * Image->width );

	PicRot90Deg( ( unsigned char * ) Image->imageData, Image->width, Image->height, ucp_temp_img, _count );
	
	cp_orig = ( char * ) Image-> imageData;
	cp_res = ( char * ) ReconResult[ img_no ]-> imageData;

	memset( ReconResult[ img_no ]->imageData, 0.0, sizeof( char ) * ReconResult[ img_no ]->height * ReconResult[ img_no ]->width );

	/* Linescan the Picture */
	for( iRow = 0; iRow < Image->height; iRow++ ) {
		for( iCol = 0; iCol < Image->width; iCol++ ) {
// 			printf("0x%X\n", *cp_orig );
			if( *cp_orig == SHADOW ) {
				shadow_flag = 1;
				shadow_len++;
// 				printf("0x%X\n", *cp_orig );

			} else {
				if( shadow_flag == 1 ) {
					/* Process shadow information */
					/* Height of pixel described as delta_y */
					*( cp_res  - shadow_len ) = get_height( iCol, shadow_len );

					shadow_len = 0;
					shadow_flag = 0;

				}
				else {

				}
			}
			cp_orig++;
// 			dbl_res++;
			cp_res++;

		}
		if( *cp_orig == SHADOW ) {
				shadow_flag = 1;
				shadow_len++;

		} else {
			if( shadow_flag == 1 ) {
				/* Process shadow information */
					*( cp_res  - shadow_len ) = get_height( iCol, shadow_len );


			}
			else {
				

			}
		}
		shadow_len = 0;
		shadow_flag = 0;

	}
	sprintf( file, "img/result_%i_%i_%li.bmp", _picstart, _count, img_no );
	cvSaveImage( file, ReconResult[ img_no ] );

	cvReleaseImage( &Image );

	Image = cvLoadImage( file, 0 );
	if( Image == NULL ) {
		printf( "[%li]\tCould not perform final adjustments %s\n", img_no, file );
		exit( 0 );

	}


	cp_orig =Image->imageData;
	cp_orig += Image->width * Image->height;
	char temp;
	for( int j = 0; j < Image->height; j++ ) {
	/* Images */
		for( i = 0; i < Image->width; i++ ) {
		/* Columns */
			if( *( cp_orig - 1 ) )
				temp += *( cp_orig - 1 );

			*cp_orig = temp;
			cp_orig--;

		}
		temp = 0;
	}
	
	PicRot90Deg( ( unsigned char * ) Image->imageData, Image->width,
			 Image->height, ucp_temp_img,
			 NUM_OF_IMGAGES - _count );

	cvSaveImage( file, Image );

	sprintf(file, "img/result_%i_%i_%li.txt", _picstart, _count, img_no );
	if( ( fp = fopen( file, "w" ) ) != NULL ) {
		cp_res = ( char * ) ReconResult[ img_no ]-> imageData;
		for(i = 0; i < ReconResult[ img_no ]->height * ReconResult[ img_no ]->width; i++ ) {
			if( ( i + 1 ) % ReconResult[ img_no ]->width == 0 )
				fprintf( fp, "%i \n", *( cp_res + i  ) );
			else
				fprintf( fp, "%i, ", *( cp_res + i ) );
		}
		fclose( fp );

	}
	else
		printf("Fehler\n");

	/* ready */

}

char get_height( int current_col, int shadow_len )
{
	unsigned char result = 0;
	result = ( unsigned char ) ( (double) shadow_len / tan( (double) ( current_col - shadow_len ) *
		(double) PX_ANGLE_SCALING_FACTOR_RAD_INT1 ) ) * ( double ) PX_RES;
// 	printf( "calc: shadowl_len %i, col %i \n result is: %i \n", shadow_len, current_col, result );
	return result;

}
/**
	@name		int PicRot90Deg(unsigned char *pic, int img_width, int img_height, unsigned char *dest_pic)
	@brief	Pic rotation for 90 degrees; clockwise
	@param	*pic Pointer to the image you whant to rotate
	@param	img_width Image width
	@param	img_height Image height
	@param	*dest_pic Target memory pointer
	@param	times How often you want to rotate

*/
int PicRot90Deg( unsigned char *pic, int img_width, int img_height, unsigned char *dest_pic, int times )
{
	int i, j, count;
	unsigned char *ptr;
	unsigned char *dest_ptr;
	
	if( times > 4 )
		times = 4;
	
	for( count = 0; count < times; count++ ) {
		dest_ptr = dest_pic;
		for( i = 0; i < img_width; i++ ) { //zeile /höhe
			for( j = img_height - 1; j >= 0; j-- ) { //spalte /breite
				ptr = pic;
				ptr += ( j * img_width + i );
				*dest_ptr = *ptr;
				dest_ptr++;

			}
		}
		if( times > 0 )
			memcpy( pic, dest_pic, img_width * img_height );
	}
	return 0;

}

// int PicRot90Deg_ccw( unsigned char *pic, int img_width, int img_height, unsigned char *dest_pic )
// {
// 	int i, j;
// 	unsigned char *ptr;
// 
// 	for( i = img_width; i < 0 ; i-- ) { //zeile /höhe
// 		for( j = 0 ; j < img_height - 1; j++ ) { //spalte /breite
// 			ptr = pic;
// 			ptr += ( j * img_width + i );
// 			*dest_pic = *ptr;
// 			dest_pic++;
// 
// 		}
// 	}
// 	return 0;
// 
// }
/**
	@fn		void invert_ImageSet( IplImage * imgSet[] )
	@brief 	Inverts an set of images
	@param[in] 	*img Pointer auf ein Bild in der IplImage Struktur

**/
void invert_ImageSet( IplImage * imgSet[] )
{
	int height;
	int width;
	int step;
	int channels;
	int i,j,k;
	int count = 0;
	unsigned char *data;

	while( imgSet[ count ] != NULL ) {
		i = j = k = height = width = step = channels = 0;

		height    = imgSet[ count ]->height;
		width     = imgSet[ count ]->width;
		step      = imgSet[ count ]->widthStep;
		channels  = imgSet[ count ]->nChannels;
		data      = (unsigned char *)imgSet[ count ]->imageData;

		for( i = 0; i < height; i++ )
			for( j = 0; j < width; j++ )
				for( k = 0; k < channels; k++ )
					/* Invertiere das Bild */
					data[ i * step + j * channels + k ] =
						255 - data[ i * step + j * channels + k ];

		count++;
	}
}

/**
	@fn		void invert_Image( IplImage * img )
	@brief 	Invertiert ein Bild
	@param[in] 	*img Pointer auf ein Bild in der IplImage Struktur

**/
void invert_Image( IplImage *img )
{
	int height;
	int width;
	int step;
	int channels;
	int i,j,k;
	unsigned char * data;

	i = j = k = height = width = step = channels = 0;

	height    = img->height;
	width     = img->width;
	step      = img->widthStep;
	channels  = img->nChannels;
	data      = (unsigned char *)img->imageData;

	for( i = 0; i < height; i++ )
		for( j = 0; j < width; j++ )
			for( k = 0; k < channels; k++ )
				/* Invertiere das Bild */
				data[ i * step + j * channels + k ] = 255 - data[ i * step + j * channels + k ];

}

/**
	@fn		int init_ImageSetsGrayscale( unsigned int ui_height, unsigned int ui_width )
	@brief 	Initialisiert die Image Sets
	@param[in] 	ui_height Bildhöhe
	@param[in] 	ui_width Bildbreite
	@return 	1 wenn O.K

**/
int init_ImageSetsGrayscale( int i_height, int i_width )
{
	int i  = 0;
	/* initialisiere die ImgSets */
	for( i = 0; i < NUM_OF_IMGAGES; i++ ) {
		ReconResult[ i ] = cvCreateImage( cvSize( i_width, i_height ), IPL_DEPTH_8U, 1 );
		if( ReconResult[ i ] == NULL )
			return -1;
		memset( ReconResult[ i ]->imageData, 0.0, ( i_height * i_width * sizeof( char ) ) );
		

	}

	return 1;
}

/**
	@fn		int reconfigure_ImageSets( unsigned int ui_height, unsigned int ui_width )
	@brief 	Neueinstellung der Image Sets
	@param[in] 	ui_height Bildhöhe
	@param[in] 	ui_width Bildbreite
	@return 	1 wenn O.K
		      -1 wenn ImgSet_Current[] nicht konfiguriert werden konnte
			-2 wenn ImgSet_Reference[] nicht konfiguriert werden konnte

Diese Funktion erstellt die leeren Image Sets, mit gleicher Bildgröße.

**/
int reconfigure_ImageSets( unsigned int ui_height, unsigned int ui_width )
{
// 	int i  = 0;
// 
// 	while( ImgSet_Current[ i ] != NULL ){
// 		ImgSet_Current[ i ]->width = ui_width;
// 		ImgSet_Current[ i ]->height = ui_height;
// 		i++;
// 
// 	}
// 	i = 0;
// 	while( ImgSet_Reference[ i ] != NULL ){
// 		ImgSet_Reference[ i ]->width = ui_width;
// 		ImgSet_Reference[ i ]->height = ui_height;
// 		i++;
// 
// 	}
// 	return 1;
}

/**
	@fn		void release_ImageSets( void )
	@brief 	Freigabe der Image Sets

**/
void release_ImageSets( void )
{
// 	int i = 0;
// 	while( ImgSet_Current[ i ] != NULL ) {
// 		cvReleaseImage( &ImgSet_Current[ i ] );
// 		i++;
// 
// 	}
// 	i = 0;
// 
// 	while( ImgSet_Reference[ i ] != NULL ) {
// 		cvReleaseImage( &ImgSet_Reference[ i ] );
// 		i++;
// 
// 	}
}

/**
	@fn 			void save_PicturesAsBmp_cv( unsigned char *Pictures,
				      const unsigned int *Res, unsigned int Len )
	@brief		Speichert die Bilddaten von der MQ als Bitmap (Graustufen)
	@param[in]		*Pictures Zeiger auf die Bilddaten die gespeichert werden sollen
	@param[in]		*Res Zeiger mit Daten der Auflösung der eingestellten Kamera
	@param[in]		Len Die Länge der *Pictures- Feldes
	@param[in]		*ucPath Pfad unter dem die Datei gespeichert werden soll

Diese Funktion Speichert Bilddaten im bmp- Format an eine Stelle auf der Festplatte.
Sie benutzt dazu die OpenCV Lib.

*/
void save_PicturesAsBmp_cv( unsigned char *ucPictures,
				   const unsigned int *uiRes,
				   unsigned int uiLen,
				   unsigned char *ucPath )
{
	/* Länge des Headers -> Header Length */
	const int iHL = 11;
	/* Position des Kamera Index im Header */
	const int iCIDX = 8;
	/* Position des Trigger Index */
	const int iTRIGIDX = 9;
	/* Position der Anzahl der Bilder */
	const int iNOP = 10;
	int iPos = 0;
	int iCount = 0;
	int iPicIdx = 0;
	int iCamIdx = 0;
	int iTrigIdx = 0;
	int iNoP = 0;
	char filename[ 1024 ];
	unsigned char *ucpQuery;

	IplImage *Img_Single;

// 	printf(" parameter \n\
// 			ucPictures :%p \n\
// 			uiLen %i \
// 			\n", ucPictures, uiLen );

	ucpQuery = ( unsigned char * ) ucPictures;

// 	memset( Img_Single-> imageData, 0, ( MAX_WIDTH * MAX_HEIGHT * sizeof( unsigned char ) ) );

	/* bis zum Ende des Query */
	while ( ( iPos + iHL )  < uiLen ) {
// 		printf(" ( iPos + iHL ) = %i \
// 			\n", ( iPos + iHL ) );

		iCamIdx = ( int ) ucpQuery[ iPos + iCIDX ];
		iTrigIdx = ( int ) ucpQuery[ iPos + iTRIGIDX ];
		iNoP = ( int ) ucpQuery[ iPos + iNOP ];
		/* Zeige Protokoll Header */
		fprintf(stderr,"%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x \n",
			ucpQuery[ iPos + 0 ],ucpQuery[ iPos + 1 ],ucpQuery[ iPos + 2 ],
			ucpQuery[ iPos + 3 ],ucpQuery[ iPos + 4 ],ucpQuery[ iPos + 5 ],
			ucpQuery[ iPos + 6 ],ucpQuery[ iPos + 7 ],ucpQuery[ iPos + 8 ],
			ucpQuery[ iPos + 9 ],ucpQuery[ iPos + 10 ]  );

		iPos += iHL;
		for ( iPicIdx = 0; iPicIdx < iNoP; iPicIdx++ ) {

		/* erstelle Speicherpfad */
#ifdef TEST
			if( ucPath == NULL ) {
				sprintf( filename,"000%d__%d_%d_%d.bmp", /*TESTBLOCK, TESTZEILE,*/
						DURCHLAUF_COUNT, iCamIdx, iTrigIdx, iPicIdx);

			} else {
				sprintf( filename,"%s000%d_%d_%d.bmp", ucPath, iCamIdx,
						iTrigIdx, iPicIdx );
			}

#endif
#ifndef TEST
			if( ucPath == NULL ) {
				sprintf( filename,"000%d_%d_%d.bmp", iCamIdx,
						iTrigIdx, iPicIdx );

			} else {
				sprintf( filename,"%s000%d_%d_%d.bmp", ucPath, iCamIdx,
						iTrigIdx, iPicIdx );
			}


#endif
// 		fprintf( stderr, "Speichere Bild unter:\t %s \n", filename );
		/* speichere die Bilder */
			if ( iCamIdx == 0x01 ) {
				/* erstellen des Bildes */
				Img_Single  = cvCreateImage( cvSize( uiRes[ 2 ], uiRes[ 3 ] ), IPL_DEPTH_8U, 1 );
				if( Img_Single == NULL )
					return;
// 				fprintf( stderr, "height is: %i \n width is: %i \n", Img_Single-> height, Img_Single-> width);
				Img_Single-> imageData = (char *) &ucpQuery[ iPos ];
				cvSaveImage( filename,  Img_Single );
				iPos += uiRes[ 2 ] * uiRes[ 3 ];

			}
			if ( iCamIdx == 0x02 ) {
				Img_Single  = cvCreateImage( cvSize( uiRes[ 6 ], uiRes[ 7 ] ), IPL_DEPTH_8U, 1 );
				if( Img_Single == NULL )
					return;
// 				Img_Single-> width = uiRes[ 6 ];
// 				Img_Single-> height = uiRes[ 7 ];
				Img_Single-> imageData = (char *) &ucpQuery[ iPos ];
				cvSaveImage( filename,  Img_Single );
				iPos += uiRes[ 6 ] * uiRes[ 7 ];

			}
			if ( iCamIdx == 0x03 ) {
				Img_Single  = cvCreateImage( cvSize( uiRes[ 10 ], uiRes[ 11 ] ), IPL_DEPTH_8U, 1 );
				if( Img_Single == NULL )
					return;
// 				Img_Single-> width = uiRes[ 10 ];
// 				Img_Single-> height = uiRes[ 11 ];
				Img_Single-> imageData = (char *) &ucpQuery[ iPos ];
				cvSaveImage( filename,  Img_Single );
				iPos += uiRes[ 10 ] * uiRes[ 11 ];

			}
			if ( iCamIdx == 0x04 ) {
				Img_Single  = cvCreateImage( cvSize( uiRes[ 14 ], uiRes[ 15 ] ), IPL_DEPTH_8U, 1 );
				if( Img_Single == NULL )
					return;
// 				Img_Single-> width = uiRes[ 14 ];
// 				Img_Single-> height = uiRes[ 15 ];
				Img_Single-> imageData = (char *) &ucpQuery[ iPos ];
				cvSaveImage( filename,  Img_Single );
				iPos += uiRes[ 14 ] * uiRes[ 15 ];

			}
			cvReleaseImage( &Img_Single);
		}
	}


}
