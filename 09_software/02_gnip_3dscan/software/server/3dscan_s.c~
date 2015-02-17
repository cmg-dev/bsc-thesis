/**
	@file 3dscan_s.c
	@author Christoph Gnip
	@date July 20th 2010
	@version 1.0
	@brief Server for MQ II serving for 3D- Scan Thesis

This program is part of my Bachelor-Thesis. It is a Server for the MiniQuadrix II with the
addition of a MiniCluster-board, wich was designdd in during work.
The Idea is to generate 3D scenedata exploiting only the casted shadows. The generation of the
shadows is one of the tasks of the MiniCluster- Borad. Therefor it holds 4 LED-arrays located on
the boards edges. It is also possible to setup usefull parameters, wich have an influence on
the aquired image.

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include "/home/christoph/src/MiniQuadrix_II/software/include/mq2_api.h"
#include "/home/christoph/src/MiniQuadrix_II/software/include/debug.h"
#include "../include/3ds.h"
#include "3dscan_s.h"
#include "../include/bmp.h"
#include "../include/font.h"

unsigned int ui_sensor = 0;
unsigned short *framebuffer1; //Framebuffer1 zur Anzeige von Bilddaten
unsigned short *framebuffer2; //Framebuffer1 zur Anzeige von Bilddaten
pthread_t th_display_vga;

/**
@fn int main( int argc, char **argv )
@param argc Argumentcount
@param **argv Given this is a commandline tool, it uses some parameters.
		Known are 3 main parameters
		@li 1 Live modus
		@li 2 Aquire 4 images (basicly for calibration)
		@li 3 Aquire sequence; 4x4 Pictures save under a path

*/
int main( int argc, char **argv )
{
	unsigned int modus;
	unsigned int ui_has_leda;
	int i = 0;
// 	int i_errorcounter;
	int i_ioresult;
	unsigned char c;
	unsigned char seq_path[300];
	/* Vars for the modes */
	unsigned char *path;
	unsigned int wid = 0;
	unsigned int hei = 0;
	unsigned int exp = 0;
	unsigned int gain = 0;
	unsigned int led_cur = 0;
	unsigned int dur = 0;
	/* use for printing strings */
	char str[200];
	char *cour10_font = &cour10_font_array[0][0];

	if ( argc < 2 ) {
		printf("Parameter check failed; Wrong Parameter!\n");
		DISPLAY_USAGE_AND_EXIT;

	}

	modus = atoi( argv[ 1 ] );
	
	t_mq2_module_desc = mq2api_make_module_description();

	exit_if(t_mq2_module_desc == NULL);

	/* Look for all sensors; exit if 1 is missing */
	exit_if( t_mq2_module_desc->sensor_info[ 0 ] == NULL );
	exit_if( t_mq2_module_desc->sensor_info[ 1 ] == NULL );
	exit_if( t_mq2_module_desc->sensor_info[ 2 ] == NULL );
	exit_if( t_mq2_module_desc->sensor_info[ 3 ] == NULL );

// 	pthread_mutex_init( &vga_mutex, NULL );
// 	pthread_cond_init( &vga_cond, NULL );

	/* Find and map hardware blocks */
	mq2api_mappb( t_mq2_module_desc, ( void * ) &t_pb_sensor_control, PB_IDENT_SENSOR_CONTROL, 0);
	mq2api_mappb( t_mq2_module_desc, ( void * ) &t_pb_dataplexer[ 0 ], PB_IDENT_DATAPLEXER, 1 );
	mq2api_mappb( t_mq2_module_desc, ( void * ) &t_pb_dataplexer[ 1 ], PB_IDENT_DATAPLEXER, 2 );
	mq2api_mappb( t_mq2_module_desc, ( void * ) &t_pb_dataplexer[ 2 ], PB_IDENT_DATAPLEXER, 3 );
	mq2api_mappb( t_mq2_module_desc, ( void * ) &t_pb_dataplexer[ 3 ], PB_IDENT_DATAPLEXER, 4 );
	mq2api_mappb( t_mq2_module_desc, ( void * ) &t_pb_vga_fifo, PB_IDENT_VGA_FIFO, 0 );
	mq2api_mappb( t_mq2_module_desc, ( void * ) &t_pb_threshold[ 0 ], PB_IDENT_THRESHOLD, 1 );
	mq2api_mappb( t_mq2_module_desc, ( void * ) &t_pb_threshold[ 1 ], PB_IDENT_THRESHOLD, 2 );
	mq2api_mappb( t_mq2_module_desc, ( void * ) &t_pb_threshold[ 2 ], PB_IDENT_THRESHOLD, 3 );
	mq2api_mappb( t_mq2_module_desc, ( void * ) &t_pb_threshold[ 3 ], PB_IDENT_THRESHOLD, 4 );


	i_ioresult = mq2api_mappb(t_mq2_module_desc, (void *) &t_pb_leda, PB_IDENT_LEDA, 0);

	ui_has_leda = TRUE;
	if ( i_ioresult != RET_SUCCESS ) ui_has_leda = FALSE;

	switch( modus ) {
		case LIVE:
			if ( argc < 4 ) {
				printf( "Not enough arguments for mode 1\n" );
				printf( "Usage: 3dscan_s 1 [exposure] [gain]\n" );
				exit( 0 );
			}
			printf( "Activating LIVE- mode\n " );

			if( ui_has_leda == TRUE ) {
				printf( "Setting up LED- Control\n" );
				mq2api_setfeature( t_mq2_module_desc, LEDA, LEDA_RESET ); //Reset Hardware
				t_pb_leda->ui_config = LEDA_ENABLE | LEDA_EN_EXT_MOD | LEDA_LED_GREEN;
				t_pb_leda->ui_data = 50; //LED Current = (ui_data * 2 mA)
				t_pb_leda->ui_led_en = LEDA_EN_LED8_BIT;
				t_pb_leda->ui_pd = LEDA_NORMAL_OPERATION;
				t_pb_leda->ui_led_on_time = 25000 * 300; //25000 ticks = 1ms trigger duration
				printf( "LEDA-Block schaltet LEDs fuer %d usec ein!\n",
					  ( unsigned int ) ( ( 40.0E-9 * ( float ) t_pb_leda->ui_led_on_time ) * 1000000.0 ) );
				mq2api_setfeature( t_mq2_module_desc, LEDA, ALL_FEATURES );

			}

			framebuffer1 = ( unsigned short * ) malloc( 752*480*2 );
			framebuffer2 = ( unsigned short * ) malloc( 752*480*2 );

			exp = atoi( argv[ 2 ] );
			gain = atoi( argv[ 3 ] );
			/* some addittional setup */
// 			t_mq2_module_desc->sensor_info[ 0 ]->us_image_startx = ( unsigned short ) 136 /*( MAX_IMG_WIDTH - wid )*/;
// 			t_mq2_module_desc->sensor_info[ 1 ]->us_image_startx = ( unsigned short ) 136 /*( MAX_IMG_WIDTH - wid )*/;
// 			t_mq2_module_desc->sensor_info[ 2 ]->us_image_startx = ( unsigned short ) 136 /*( MAX_IMG_WIDTH - wid )*/;
// 			t_mq2_module_desc->sensor_info[ 3 ]->us_image_startx = ( unsigned short ) 136 /*( MAX_IMG_WIDTH - wid )*/;

			basic_sensor_setup( ALL_SENSORS, VGA_IMG_HEIGHT, VGA_IMG_WIDTH, exp, gain );
			/* setting up Data plexer for Monitor Output */
			t_pb_dataplexer[ 0 ]->i_dapl_mon_mux = SENSOR_DATA;
			t_pb_dataplexer[ 1 ]->i_dapl_mon_mux = SENSOR_DATA;
			t_pb_dataplexer[ 2 ]->i_dapl_mon_mux = SENSOR_DATA;
			t_pb_dataplexer[ 3 ]->i_dapl_mon_mux = SENSOR_DATA;
			
			mq2api_setfeature( t_mq2_module_desc, DAPL1, ALL_FEATURES );
			mq2api_setfeature( t_mq2_module_desc, DAPL2, ALL_FEATURES );
			mq2api_setfeature( t_mq2_module_desc, DAPL3, ALL_FEATURES );
			mq2api_setfeature( t_mq2_module_desc, DAPL4, ALL_FEATURES );

			mq2api_setfeature( t_mq2_module_desc, VGA_FIFO, INITIALIZE_VGA );

			while( 1 ) {
				t_pb_vga_fifo->pus_inputbuffer = framebuffer1;
				t_pb_vga_fifo->pus_vgasource = framebuffer1;
				mq2api_setfeature( t_mq2_module_desc, VGA_FIFO, CHANGE_VGASOURCE );
				mq2api_setfeature( t_mq2_module_desc, VGA_FIFO, CHANGE_INPUTBUFFER );
				mq2api_setfeature( t_mq2_module_desc, VGA_FIFO, START_VGA );
				mq2api_setfeature( t_mq2_module_desc, VGA_FIFO, RELOAD_DMA );

				t_pb_vga_fifo->ui_inputchannel = ui_sensor;
				mq2api_setfeature( t_mq2_module_desc, VGA_FIFO, CHANGE_CHANNEL );

				exit_if( pthread_create( &th_display_vga,
					NULL,
				      ( void * )&display_vga,
					( void * ) "DISPLAY VGA" ) != 0 );

				printf( "Press ENTER switch through cams\n" );
				c = getchar( );
				if( ui_sensor < 4 )
					ui_sensor++;
				else
					ui_sensor = 1;
				printf("New cam is: %i\n", ui_sensor );

				pthread_cancel( th_display_vga );

			}
		break;

		case TAKE_PICTURE:
			// modus, wid, hei, exp, gain, path
			if ( argc < 7 ) {
				printf( "Not enough arguments for mode 2\n" );
				printf( "Usage: 3dscan_s 2 [image width] [image height] [exposure] [gain] [path]\n" );
				exit( 0 );
			}
			wid = atoi( argv[ 2 ] );
			hei = atoi( argv[ 3 ] );
			exp = atoi( argv[ 4 ] );
			gain = atoi( argv[ 5 ] );
			path = argv[ 6 ];

			printf("3dscan_s %i %i %i %i %i %s\n", modus, wid, hei, exp, gain, path );
			if( ui_has_leda == TRUE ) {
				printf( "Setting up LED- Control\n" );
				mq2api_setfeature( t_mq2_module_desc, LEDA, LEDA_RESET ); //Reset Hardware
				t_pb_leda->ui_config = LEDA_ENABLE | LEDA_EN_EXT_MOD | LEDA_LED_GREEN;
				t_pb_leda->ui_data = 60; //LED Current = (ui_data * 2 mA)
				t_pb_leda->ui_led_en = LEDA_EN_LED8_BIT;
				t_pb_leda->ui_pd = LEDA_NORMAL_OPERATION;
				t_pb_leda->ui_led_on_time = 25 * 200; //25000 ticks = 1ms trigger duration
				printf( "LEDA-Block schaltet LEDs fuer %d usec ein!\n",
					  ( unsigned int ) ( ( 40.0E-9 * ( float ) t_pb_leda->ui_led_on_time ) * 1000.0 ) );
				mq2api_setfeature( t_mq2_module_desc, LEDA, ALL_FEATURES );

			}
			
			/* some addittional setup */
			t_mq2_module_desc->sensor_info[ 0 ]->us_image_startx = ( unsigned short ) 136;
			t_mq2_module_desc->sensor_info[ 1 ]->us_image_startx = ( unsigned short ) 136;
			t_mq2_module_desc->sensor_info[ 2 ]->us_image_startx = ( unsigned short ) 136;
			t_mq2_module_desc->sensor_info[ 3 ]->us_image_startx = ( unsigned short ) 136;
		
			basic_sensor_setup( ALL_SENSORS, hei, wid, exp, gain );
			mq2api_setfeature( t_mq2_module_desc, VGA_FIFO, STOP_VGA );
			printf( "Taking Pictures\n" );
			save_imges_2_nfs( path, hei, wid );

		break;

		case RECORD_SEQUENCE:
			mq2api_setfeature( t_mq2_module_desc, VGA_FIFO, STOP_VGA );
			
			if ( argc < 8 ) {
				printf( "Not enough arguments for mode 3\n" );
				printf( "Usage: 3dscan_s 3 [image width] [image height] [exposure] [gain] [led current] [led pulse duration] [path]\n" );
				exit( 0 );
			}

			framebuffer1 = ( unsigned short * ) malloc( 752*480*2 );
			memset( framebuffer1, 0x00, ( 752*480*2 ) );

			wid = atoi( argv[ 2 ] );
			hei = atoi( argv[ 3 ] );
			exp = atoi( argv[ 4 ] );
			gain = atoi( argv[ 5 ] );
			led_cur = atoi( argv[ 6 ] );
			dur = atoi( argv[ 7 ] );
			path = argv[ 8 ];
			printf( "3dscan_s %i %i %i %i %i %i %i %s\n", modus, wid, hei, exp, gain, led_cur, dur, path );

			printf( "Setting up Image Sensors...\n" );

			/* some addittional setup */
			t_mq2_module_desc->sensor_info[ 0 ]->us_image_startx = ( unsigned short ) 136;
			t_mq2_module_desc->sensor_info[ 1 ]->us_image_startx = ( unsigned short ) 136;
			t_mq2_module_desc->sensor_info[ 2 ]->us_image_startx = ( unsigned short ) 136;
			t_mq2_module_desc->sensor_info[ 3 ]->us_image_startx = ( unsigned short ) 136;
		
			basic_sensor_setup( ALL_SENSORS, hei, wid, exp, gain );
			printf( "Sensor setup complete\n" );

			for( i = 0; i < 4; i++ ) {
				if( ui_has_leda == TRUE ) {
					printf( "Setting up LED- Control\n" );
					mq2api_setfeature( t_mq2_module_desc, LEDA, LEDA_RESET );
					t_pb_leda->ui_config = LEDA_ENABLE | LEDA_EN_EXT_MOD | LEDA_LED_GREEN;
					t_pb_leda->ui_data = led_cur;
					t_pb_leda->ui_led_en = ( LEDA_EN_LED8_BIT >> i );
					t_pb_leda->ui_pd = LEDA_NORMAL_OPERATION;
					t_pb_leda->ui_led_on_time = 25 * dur;
					printf( "LEDA-Block schaltet LEDs fuer %d usec ein!\n", ( unsigned int ) ( ( 40.0E-9 * ( float ) t_pb_leda->ui_led_on_time ) * 1000000.0 ) );
					mq2api_setfeature( t_mq2_module_desc, LEDA, ALL_FEATURES );

				}
				sprintf( seq_path, "%s_%i", path, i );
				save_imges_2_nfs( seq_path, hei, wid );
				memset( framebuffer1, 0x00, ( 752*480*2 ) );

			}
			sprintf( str,"Finished... Images can be found in: \n%s\n\n ->Exit", path );
			vid_print_string( 50, 50, LIMEGREEN_16, cour10_font, (int)framebuffer1, str );
// 			t_pb_vga_fifo->pus_inputbuffer = framebuffer1;
			t_pb_vga_fifo->pus_vgasource = framebuffer1;
			mq2api_setfeature( t_mq2_module_desc, VGA_FIFO, CHANGE_VGASOURCE );
// 			mq2api_setfeature( t_mq2_module_desc, VGA_FIFO, CHANGE_INPUTBUFFER );
			mq2api_setfeature( t_mq2_module_desc, VGA_FIFO, START_VGA );
			sleep( 10 );
			mq2api_setfeature( t_mq2_module_desc, VGA_FIFO, STOP_VGA );
			
		break;
		case CALIBRATION_RUN:
			mq2api_setfeature( t_mq2_module_desc, VGA_FIFO, STOP_VGA );

			if ( argc < 10 ) {
				printf( "Not enough arguments for mode 4\n" );
				printf( "Usage: 3dscan_s 4 [image width] [image height] [exposure] [gain] [led current] [led pulse duration] [Lower Threshold] [Upper Threshold] [path]\n" );
				exit( 0 );
			}

			framebuffer1 = ( unsigned short * ) malloc( 752*480*2 );
			memset( framebuffer1, 0x00, ( 752*480*2 ) );

			wid = atoi( argv[ 2 ] );
			hei = atoi( argv[ 3 ] );
			exp = atoi( argv[ 4 ] );
			gain = atoi( argv[ 5 ] );
			led_cur = atoi( argv[ 6 ] );
			dur = atoi( argv[ 7 ] );
			path = argv[ 10 ];
			printf( "3dscan_s %i %i %i %i %i %i %i %s\n", modus, wid, hei, exp, gain, led_cur, dur, path );

			printf( "Setting up Image Sensors...\n" );

			/* some addittional setup */
			t_mq2_module_desc->sensor_info[ 0 ]->us_image_startx = ( unsigned short ) 136;
			t_mq2_module_desc->sensor_info[ 1 ]->us_image_startx = ( unsigned short ) 136;
			t_mq2_module_desc->sensor_info[ 2 ]->us_image_startx = ( unsigned short ) 136;
			t_mq2_module_desc->sensor_info[ 3 ]->us_image_startx = ( unsigned short ) 136;

			basic_sensor_setup( ALL_SENSORS, hei, wid, exp, gain );
			printf( "Sensor setup complete\n" );

			if( ui_has_leda == TRUE ) {
				printf( "Setting up LED- Control\n" );
				mq2api_setfeature( t_mq2_module_desc, LEDA, LEDA_RESET );
				t_pb_leda->ui_config = LEDA_ENABLE | LEDA_EN_EXT_MOD | LEDA_LED_GREEN;
				t_pb_leda->ui_data = led_cur;
				t_pb_leda->ui_led_en = ( LEDA_EN_LED8_BIT >> i );
				t_pb_leda->ui_pd = LEDA_NORMAL_OPERATION;
				t_pb_leda->ui_led_on_time = 25 * dur;
				printf( "LEDA-Block schaltet LEDs fuer %d usec ein!\n", ( unsigned int ) ( ( 40.0E-9 * ( float ) t_pb_leda->ui_led_on_time ) * 1000000.0 ) );
				mq2api_setfeature( t_mq2_module_desc, LEDA, ALL_FEATURES );

			}
			sprintf( seq_path, "%s_%i", path, i );
			determine_calibration( seq_path, hei, wid, ( short ) atoi( argv[ 8 ] ), ( short ) atoi( argv[ 9 ] ) );

		break;

		default:
			printf( "Mode Unknown...\n" );

		break;

	}

	mq2api_free_module_description(t_mq2_module_desc); //Alles wieder freigeben
	printf("Exit...\n");
	return(0);

}

int determine_calibration( char *path, int hei, int wid, short lower_tresh, short upper_tresh )
{
	char filename[ 200 ];
	int i = 0;
	int j = 0;
	int i_result = 0;
	short *fb1;
	short *fb2;
	short *fb3;
	short *fb4;
	short *x_offs;
	int x_offs_pos = 0;
	short *y_offs;
	int y_offs_pos = 0;
	FILE *fp;

	t_pb_dataplexer[ 0 ]->i_image_size = hei * wid;
	t_pb_dataplexer[ 1 ]->i_image_size = hei * wid;
	t_pb_dataplexer[ 2 ]->i_image_size = hei * wid;
	t_pb_dataplexer[ 3 ]->i_image_size = hei * wid;
// 	t_pb_dataplexer[ 0 ]->i_dapl_vfif_mux = SENSOR_DATA;
// 	t_pb_dataplexer[ 1 ]->i_dapl_vfif_mux = SENSOR_DATA;
// 	t_pb_dataplexer[ 2 ]->i_dapl_vfif_mux = SENSOR_DATA;
// 	t_pb_dataplexer[ 3 ]->i_dapl_vfif_mux = SENSOR_DATA;

	fb1 = ( short * ) malloc( 752*480*2 );
	fb2 = ( short * ) malloc( 752*480*2 );
	fb3 = ( short * ) malloc( 752*480*2 );
	fb4 = ( short * ) malloc( 752*480*2 );

	exit_if( fb1 == NULL );
	exit_if( fb2 == NULL );
	exit_if( fb3 == NULL );
	exit_if( fb4 == NULL );

	memset( fb1, 0x00, 752*480*2 );
	memset( fb2, 0x00, 752*480*2 );
	memset( fb3, 0x00, 752*480*2 );
	memset( fb4, 0x00, 752*480*2 );

	/* hand the pointer to the API */
	t_pb_dataplexer[ 0 ]->ps_vfif_framebuffer = fb1;
	t_pb_dataplexer[ 1 ]->ps_vfif_framebuffer = fb2;
	t_pb_dataplexer[ 2 ]->ps_vfif_framebuffer = fb3;
	t_pb_dataplexer[ 3 ]->ps_vfif_framebuffer = fb4;

	/* setup Dataplexer */
	t_pb_dataplexer[ 0 ]->i_dapl_thbl_mux = SENSOR_DATA;
	t_pb_dataplexer[ 0 ]->i_dapl_vfif_mux = THBL_DATA;
	t_pb_dataplexer[ 1 ]->i_dapl_thbl_mux = SENSOR_DATA;
	t_pb_dataplexer[ 1 ]->i_dapl_vfif_mux = THBL_DATA;
	t_pb_dataplexer[ 2 ]->i_dapl_thbl_mux = SENSOR_DATA;
	t_pb_dataplexer[ 2 ]->i_dapl_vfif_mux = THBL_DATA;
	t_pb_dataplexer[ 3 ]->i_dapl_thbl_mux = SENSOR_DATA;
	t_pb_dataplexer[ 3 ]->i_dapl_vfif_mux = THBL_DATA;

	mq2api_setfeature( t_mq2_module_desc, DAPL1, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc, DAPL2, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc, DAPL3, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc, DAPL4, ALL_FEATURES );

	/* setup Thresholdblock */
	for( i = 0; i < 4; i++ ) {
		t_pb_threshold[ i ]->s_thres_lower = lower_tresh; //set Lower-Threshold to 128
		t_pb_threshold[ i ]->s_thres_upper = upper_tresh; //set Upper-Threshold to 200

	}
	mq2api_setfeature( t_mq2_module_desc, TRHO1, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc, TRHO2, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc, TRHO3, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc, TRHO4, ALL_FEATURES );
	
	mq2api_setfeature( t_mq2_module_desc, SENSOR1, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc, SENSOR2, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc, SENSOR3, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc, SENSOR4, ALL_FEATURES );

	/* fire and forget; Take picture */
	mq2api_setfeature( t_mq2_module_desc, SENSOR_CONTROL, EXPOSURE );
	usleep( 300000 );

	/* Activate Image Aquire Logic an DMA */
	mq2api_setfeature( t_mq2_module_desc, DAPL1, RELOAD_DMA );
	mq2api_setfeature( t_mq2_module_desc, DAPL2, RELOAD_DMA );
	mq2api_setfeature( t_mq2_module_desc, DAPL3, RELOAD_DMA );
	mq2api_setfeature( t_mq2_module_desc, DAPL4, RELOAD_DMA );

	/* Take the Image */
	mq2api_setfeature( t_mq2_module_desc, SENSOR_CONTROL, EXPOSURE );
	i_result = mq2api_setfeature( t_mq2_module_desc, DAPL1, WAIT_FOR_DMA_READY );
	i_result = mq2api_setfeature( t_mq2_module_desc, DAPL2, WAIT_FOR_DMA_READY );
	i_result = mq2api_setfeature( t_mq2_module_desc, DAPL3, WAIT_FOR_DMA_READY );
	i_result = mq2api_setfeature( t_mq2_module_desc, DAPL4, WAIT_FOR_DMA_READY );

	if ( i_result == RET_DMA_TIMEOUT ) {
		printf( "DMA Timeout. Sensor liefert keine oder zu wenig Daten! Bild ist fehlerhaft!\n" );

	} else {
		for( i_result = 0; i_result < 4; i_result++ ) {
			sprintf( filename, "%s_%i.bmp", path, i_result );
			Save8BitGrayscaleBmp( filename, wid, hei, t_pb_dataplexer[ i_result ]->ps_vfif_framebuffer );
			printf( "Bild wurde unter %s gespeichert.\n", filename );

		}
	}
	/*
	 * Determine calibration for each image/ camera
	 * Search starts at CAL_START_X respectively CAL_START_Y an searches CAL_SEARCHLEN
	 */
	fp = fopen( "cal.txt", "w" );
	if( fp == NULL )
		return;
	for( i_result = 0; i_result < 4; i_result++ ) {
		fprintf( fp, " %i\n", i_result );
		x_offs_pos = 0;
		y_offs_pos = 0;
		/* search for bright-dark change */
		for( i = CAL_START_Y; i < ( CAL_START_Y + CAL_SEARCHLEN ); i++ ) {
			/* some pointer posistioning */
			x_offs = y_offs = t_pb_dataplexer[ i_result ]->ps_vfif_framebuffer;
// 			printf( "start addr. y_offs %p\n", y_offs );
// 			printf( "start addr. x_offs %p\n\n", x_offs );

			x_offs += CAL_START_X + ( wid * i );
			y_offs += ( ( CAL_START_Y * wid ) + CAL_START_X + ( i - CAL_START_Y ) );

			/* process y an x seperately; first x columns then y rows */
			for( j = CAL_START_X; j < ( CAL_START_X + CAL_SEARCHLEN ); j++ ) {
				/* differ change bright-dark from dark-bright change */
				if( *x_offs == 0x00 && *( x_offs + 1 ) > 0x00 && *( x_offs + 2 ) > 0x00 && *( x_offs + 3 ) > 0x00 ) {
// 					printf( "[pic %i] hor D-B change detected at ( %i, %i )\n", i_result, j, i );
// 					x_offs_pos += ( j - wid / 2 );
					break;
	
				} else if( *x_offs > 0x00 && *( x_offs + 1 ) == 0x00 && *( x_offs + 2 ) == 0x00 && *( x_offs + 3 ) == 0x00 ) {
					printf( "[pic %i] hor B-D change detected at ( %i, %i )\n", i_result, j, i );
					x_offs_pos += ( j - wid / 2 );
					break;

				} else if( j == ( CAL_START_X + CAL_SEARCHLEN -1 ) ) {
					printf( "[pic %i] hor Dark Row detected at Line %i\n", i_result, i );
					x_offs_pos += 240;
					break;

				}
				x_offs++;

			}
			for( j = CAL_START_Y; j < ( CAL_START_Y + CAL_SEARCHLEN ); j++ ) {
// 				printf( "addr. y_offs %p\n", y_offs );

				/* differ change bright-dark from dark-bright change */
				if( *y_offs == 0x00 && *( y_offs + ( 1 * wid ) ) > 0x00 && *( y_offs + ( 2 * wid ) ) > 0x00 && *( y_offs + ( 3 * wid ) ) > 0x00 ) {
// 					printf( "[pic %i] vert D-B change detected at ( %i, %i )\n", i_result, i, j );
// 					y_offs_pos += ( j - wid / 2 );
					break;

				} else if( *y_offs > 0x00 && *( y_offs + ( 1 * wid ) ) == 0x00 /*&& *( y_offs + ( 2 *wid ) ) == 0x00 && *( y_offs + ( 3 * wid ) ) == 0x00*/ ) {
					printf( "[pic %i] vert B-D change detected at ( %i, %i )\n", i_result, i, j );
					y_offs_pos += ( j - wid / 2 );
					break;

				} else if( j == ( CAL_START_Y + CAL_SEARCHLEN - 1 ) ) {
					printf( "[pic %i] vert Dark Row detected at Line %i\n", i_result, i );
					y_offs_pos += 240;
					break;

				}
				y_offs +=  wid;

			}	
		}
		fprintf( fp, " %i, %i\n", 2 * x_offs_pos / CAL_SEARCHLEN, 2 * y_offs_pos / CAL_SEARCHLEN );
		
		printf("Determined hor Cal for pic %i is: %i\n", i_result, x_offs_pos / CAL_SEARCHLEN );
		printf("Determined vert Cal for pic %i is: %i\n", i_result, y_offs_pos / CAL_SEARCHLEN );

	}
	fclose( fp );
	return SUCCESS;

}

/**
@fn int save_imges_2_nfs( char *path, int hei, int wid )
@brief Aquires an image from every can; saves them to a given path
@param *path Path where images are saved to
@param hei Heights of the image
@param wid Width of the image

*/
int save_imges_2_nfs( char *path, int hei, int wid )
{
	char filename[ 200 ];
	int i = 0;
	int i_result = 0;
	short *fb1;
	short *fb2;
	short *fb3;
	short *fb4;
	
	t_pb_dataplexer[ 0 ]->i_image_size = hei * wid;
	t_pb_dataplexer[ 1 ]->i_image_size = hei * wid;
	t_pb_dataplexer[ 2 ]->i_image_size = hei * wid;
	t_pb_dataplexer[ 3 ]->i_image_size = hei * wid;

// 	t_pb_dataplexer[ 0 ]->i_dapl_vfif_mux = SENSOR_DATA;
// 	t_pb_dataplexer[ 1 ]->i_dapl_vfif_mux = SENSOR_DATA;
// 	t_pb_dataplexer[ 2 ]->i_dapl_vfif_mux = SENSOR_DATA;
// 	t_pb_dataplexer[ 3 ]->i_dapl_vfif_mux = SENSOR_DATA;

	fb1 = ( short * ) malloc( 752*480*2 );
	fb2 = ( short * ) malloc( 752*480*2 );
	fb3 = ( short * ) malloc( 752*480*2 );
	fb4 = ( short * ) malloc( 752*480*2 );
	
	exit_if( fb1 == NULL );
	exit_if( fb2 == NULL );
	exit_if( fb3 == NULL );
	exit_if( fb4 == NULL );
	
	memset( fb1, 0x00, 752*480*2 );
	memset( fb2, 0x00, 752*480*2 );
	memset( fb3, 0x00, 752*480*2 );
	memset( fb4, 0x00, 752*480*2 );

	/* hand the pointer to the API */
	t_pb_dataplexer[ 0 ]->ps_vfif_framebuffer = fb1;
	t_pb_dataplexer[ 1 ]->ps_vfif_framebuffer = fb2;
	t_pb_dataplexer[ 2 ]->ps_vfif_framebuffer = fb3;
	t_pb_dataplexer[ 3 ]->ps_vfif_framebuffer = fb4;

	/* setup Dataplexer */
	t_pb_dataplexer[ 0 ]->i_dapl_thbl_mux = SENSOR_DATA;
	t_pb_dataplexer[ 0 ]->i_dapl_vfif_mux = THBL_DATA;
	t_pb_dataplexer[ 1 ]->i_dapl_thbl_mux = SENSOR_DATA;
	t_pb_dataplexer[ 1 ]->i_dapl_vfif_mux = THBL_DATA;
	t_pb_dataplexer[ 2 ]->i_dapl_thbl_mux = SENSOR_DATA;
	t_pb_dataplexer[ 2 ]->i_dapl_vfif_mux = THBL_DATA;
	t_pb_dataplexer[ 3 ]->i_dapl_thbl_mux = SENSOR_DATA;
	t_pb_dataplexer[ 3 ]->i_dapl_vfif_mux = THBL_DATA;
	
	mq2api_setfeature( t_mq2_module_desc,DAPL1, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc,DAPL2, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc,DAPL3, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc,DAPL4, ALL_FEATURES );

	/* setup Thresholdblock */
	
	for( i = 0; i < 4; i++ ) {
		t_pb_threshold[ i ]->s_thres_lower = 320;
		t_pb_threshold[ i ]->s_thres_upper = 2000; //set Upper-Threshold to 200

	}

	mq2api_setfeature( t_mq2_module_desc, TRHO1, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc, TRHO2, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc, TRHO3, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc, TRHO4, ALL_FEATURES );
	
	mq2api_setfeature( t_mq2_module_desc, SENSOR1, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc, SENSOR2, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc, SENSOR3, ALL_FEATURES );
	mq2api_setfeature( t_mq2_module_desc, SENSOR4, ALL_FEATURES );

	mq2api_setfeature( t_mq2_module_desc, SENSOR_CONTROL, EXPOSURE );
	usleep(300000);

	//Activate Image Aquire Logic an DMA
	mq2api_setfeature( t_mq2_module_desc, DAPL1, RELOAD_DMA );
	mq2api_setfeature( t_mq2_module_desc, DAPL2, RELOAD_DMA );
	mq2api_setfeature( t_mq2_module_desc, DAPL3, RELOAD_DMA );
	mq2api_setfeature( t_mq2_module_desc, DAPL4, RELOAD_DMA );


	//Take the Image
	mq2api_setfeature( t_mq2_module_desc, SENSOR_CONTROL, EXPOSURE );
	i_result = mq2api_setfeature( t_mq2_module_desc, DAPL1, WAIT_FOR_DMA_READY );
	i_result = mq2api_setfeature( t_mq2_module_desc, DAPL2, WAIT_FOR_DMA_READY );
	i_result = mq2api_setfeature( t_mq2_module_desc, DAPL3, WAIT_FOR_DMA_READY );
	i_result = mq2api_setfeature( t_mq2_module_desc, DAPL4, WAIT_FOR_DMA_READY );

	if ( i_result == RET_DMA_TIMEOUT ) {
		printf( "DMA Timeout. Sensor liefert keine oder zu wenig Daten! Bild ist fehlerhaft!\n" );

	} else {
		for( i_result = 0; i_result < 4; i_result++ ) {
// 			vid_draw_horiz_line(0, wid, (short)( hei / 2 ), RED_16, (int)t_pb_dataplexer[ i_result ]->ps_vfif_framebuffer);
// 			vid_draw_line(376, 0, 376, hei, 1, RED_16, (int)t_pb_dataplexer[ i_result ]->ps_vfif_framebuffer);
		
			sprintf( filename, "%s_%i.bmp", path, i_result );
			Save8BitGrayscaleBmp( filename, wid, hei, t_pb_dataplexer[ i_result ]->ps_vfif_framebuffer );
			printf( "Bild wurde unter %s gespeichert.\n", filename );

		}
	}
	return SUCCESS;

}

/**
@fn void display_vga( void *_name )
@brief Displays a cameraimage on the screen
@param *_name Name of the Thread

Use as thread to display the camdata

*/
void display_vga( void *_name )
{
	int i_errorcounter, i_result;

	while( 1 )
	{
		t_pb_vga_fifo->pus_inputbuffer = framebuffer2;

		mq2api_setfeature(t_mq2_module_desc,VGA_FIFO,RELOAD_DMA);

		mq2api_setfeature(t_mq2_module_desc,SENSOR_CONTROL, EXPOSURE);
		i_result = mq2api_setfeature(t_mq2_module_desc,VGA_FIFO,WAIT_FOR_DMA_READY);
		if (i_result == RET_DMA_TIMEOUT)
		{
			printf( "DMA Timeout bei Framebuffer2. Sensor liefert keine oder zu wenig Daten!\n" );
			i_errorcounter++;
			if (i_errorcounter > 5) break;
		}
		if( ui_sensor > 2 ) {
			vid_draw_horiz_line(0, 752, 240, RED_16, (int)framebuffer1);
			vid_draw_line(376, 0, 376, 480, 1, RED_16, (int)framebuffer1);
		} else {
			vid_draw_horiz_line(0, 752, 240, RED_16, (int)framebuffer1);
			vid_draw_line(264, 0, 264, 480, 1, RED_16, (int)framebuffer1);

		}
		t_pb_vga_fifo->pus_vgasource = t_pb_vga_fifo->pus_inputbuffer;
		mq2api_setfeature(t_mq2_module_desc,VGA_FIFO,CHANGE_VGASOURCE);


		t_pb_vga_fifo->pus_inputbuffer = framebuffer1;
		mq2api_setfeature(t_mq2_module_desc,VGA_FIFO,RELOAD_DMA);

		mq2api_setfeature(t_mq2_module_desc,SENSOR_CONTROL, EXPOSURE);
		i_result = mq2api_setfeature(t_mq2_module_desc,VGA_FIFO,WAIT_FOR_DMA_READY);
		if (i_result == RET_DMA_TIMEOUT)
		{
			printf( "DMA Timeout bei Framebuffer1. Sensor liefert keine oder zu wenig Daten!\n" );
			i_errorcounter++;
			if (i_errorcounter > 5) break;
		}
		if( ui_sensor > 2 ) {
			vid_draw_horiz_line(0, 752, 240, RED_16, (int)framebuffer1);
			vid_draw_line(376, 0, 376, 480, 1, RED_16, (int)framebuffer1);
		} else {
			vid_draw_horiz_line(0, 752, 240, RED_16, (int)framebuffer1);
			vid_draw_line(264, 0, 264, 480, 1, RED_16, (int)framebuffer1);
		
		}
		
		t_pb_vga_fifo->pus_vgasource = t_pb_vga_fifo->pus_inputbuffer;
		mq2api_setfeature( t_mq2_module_desc,VGA_FIFO,CHANGE_VGASOURCE );

	}
}

/**
@fn int basic_sensor_setup( int ui_snr, int hei, int wid, int exp, int gain )
@brief Does a basic setup for a sensor
@param ui_snr Confgure sensor number; set to ALL_SENSORS if you want to configure all 
@param hei Imgae heigt
@param wid Image width
@param exp Exposure
@param gain Analog Gain

*/
int basic_sensor_setup( int ui_snr, int hei, int wid, int exp, int gain )
{
	if( ui_snr != ALL_SENSORS ) {
		if (ui_snr == 1) t_pb_sensor_control->i_sensor_1_exposureenable = TRUE;
		if (ui_snr == 2) t_pb_sensor_control->i_sensor_2_exposureenable = TRUE;
		if (ui_snr == 3) t_pb_sensor_control->i_sensor_3_exposureenable = TRUE;
		if (ui_snr == 4) t_pb_sensor_control->i_sensor_4_exposureenable = TRUE;
		mq2api_setfeature(t_mq2_module_desc,SENSOR_CONTROL,ALL_FEATURES);

		t_mq2_module_desc->sensor_info[ui_snr-1]->us_image_width = wid;
		t_mq2_module_desc->sensor_info[ui_snr-1]->us_image_height = hei;
		t_mq2_module_desc->sensor_info[ui_snr-1]->ui_exposure = exp;
		t_mq2_module_desc->sensor_info[ui_snr-1]->ui_gain = gain;
		t_mq2_module_desc->sensor_info[ui_snr-1]->ui_aec_agc = FALSE;

		if (ui_snr == 1) mq2api_setfeature(t_mq2_module_desc,SENSOR1,ALL_FEATURES);
		if (ui_snr == 2) mq2api_setfeature(t_mq2_module_desc,SENSOR2,ALL_FEATURES);
		if (ui_snr == 3) mq2api_setfeature(t_mq2_module_desc,SENSOR3,ALL_FEATURES);
		if (ui_snr == 4) mq2api_setfeature(t_mq2_module_desc,SENSOR4,ALL_FEATURES);

	} else {
		t_pb_sensor_control->i_sensor_1_exposureenable = TRUE;
		t_pb_sensor_control->i_sensor_2_exposureenable = TRUE;
		t_pb_sensor_control->i_sensor_3_exposureenable = TRUE;
		t_pb_sensor_control->i_sensor_4_exposureenable = TRUE;
		mq2api_setfeature(t_mq2_module_desc,SENSOR_CONTROL,ALL_FEATURES);

		t_mq2_module_desc->sensor_info[ 0 ]->ui_row_flip = TRUE;
		t_mq2_module_desc->sensor_info[ 0 ]->ui_col_flip = TRUE;
		t_mq2_module_desc->sensor_info[ 1 ]->ui_row_flip = TRUE;
		t_mq2_module_desc->sensor_info[ 1 ]->ui_col_flip = TRUE;

		t_mq2_module_desc->sensor_info[ 0 ]->us_image_width = wid;
		t_mq2_module_desc->sensor_info[ 0 ]->us_image_height = hei;
		t_mq2_module_desc->sensor_info[ 0 ]->ui_exposure = exp;
		t_mq2_module_desc->sensor_info[ 0 ]->ui_gain = gain;
		t_mq2_module_desc->sensor_info[ 0 ]->ui_aec_agc = FALSE;

		t_mq2_module_desc->sensor_info[ 3 ]->us_image_width =
		t_mq2_module_desc->sensor_info[ 2 ]->us_image_width =
		t_mq2_module_desc->sensor_info[ 1 ]->us_image_width =
		t_mq2_module_desc->sensor_info[ 0 ]->us_image_width;

		t_mq2_module_desc->sensor_info[ 3 ]->us_image_height =
		t_mq2_module_desc->sensor_info[ 2 ]->us_image_height =
		t_mq2_module_desc->sensor_info[ 1 ]->us_image_height =
		t_mq2_module_desc->sensor_info[ 0 ]->us_image_height;

		t_mq2_module_desc->sensor_info[ 3 ]->ui_exposure =
		t_mq2_module_desc->sensor_info[ 2 ]->ui_exposure =
		t_mq2_module_desc->sensor_info[ 1 ]->ui_exposure =
		t_mq2_module_desc->sensor_info[ 0 ]->ui_exposure;

		t_mq2_module_desc->sensor_info[ 3 ]->ui_gain =
		t_mq2_module_desc->sensor_info[ 2 ]->ui_gain =
		t_mq2_module_desc->sensor_info[ 1 ]->ui_gain =
		t_mq2_module_desc->sensor_info[ 0 ]->ui_gain;

		t_mq2_module_desc->sensor_info[ 3 ]->ui_aec_agc =
		t_mq2_module_desc->sensor_info[ 2 ]->ui_aec_agc =
		t_mq2_module_desc->sensor_info[ 1 ]->ui_aec_agc =
		t_mq2_module_desc->sensor_info[ 0 ]->ui_aec_agc;

		mq2api_setfeature(t_mq2_module_desc,SENSOR1,ALL_FEATURES);
		mq2api_setfeature(t_mq2_module_desc,SENSOR2,ALL_FEATURES);
		mq2api_setfeature(t_mq2_module_desc,SENSOR3,ALL_FEATURES);
		mq2api_setfeature(t_mq2_module_desc,SENSOR4,ALL_FEATURES);
	}
	return SUCCESS;
}
