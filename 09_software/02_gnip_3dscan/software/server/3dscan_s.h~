/**
	@file 3dscan_s.h
	@author Christoph Gnip
	@date July 20th 2010
	@version 1.0
	@brief Server for MQ II serving for 3D- Scan Thesis

*/

#ifndef _3D_SCAN_SERVER_H_
#define _3D_SCAN_SERVER_H_

/*
 * Some defines for the modeselection via 
 */
#define	LIVE				1
#define	TAKE_PICTURE		2
#define	RECORD_SEQUENCE		3
#define	CALIBRATION_RUN		4

#define	VGA_IMG_HEIGHT		480
#define	VGA_IMG_WIDTH		640
#define	MAX_IMG_HEIGHT		480
#define	MAX_IMG_WIDTH		752

/**
@def CAL_START_Y
	Y-Startoffset for the bright-dark change search [pxs]
@def CAL_START_X
	X-Startoffset for the bright-dark change search [pxs]
@def CAL_SEARCHLEN
	Length to serch for a bright-dark change in the image [pxs]

*/
#define	CAL_START_Y			220
#define	CAL_START_X			220
#define	CAL_SEARCHLEN		40

#define DISPLAY_USAGE_AND_EXIT \
	printf("3dscan_s [Mode] [...]\n \
	Mode can be:\n\
		1 ->\t Display image on extern monitor\n \
		2 ->\t Take a picture of all cameras\n \
		3 ->\t Record Image sequence\n \
	\n"); \
	exit(0)

PB_SENSOR_CONTROL		*t_pb_sensor_control;
PB_VGA_FIFO			*t_pb_vga_fifo = NULL;
PB_DATAPLEXER		*t_pb_dataplexer[ 4 ];
PB_THRESHOLD		*t_pb_threshold[ 4 ];
PB_LEDA			*t_pb_leda = NULL;
MQ2_MODULE_DESC 		*t_mq2_module_desc; //MQ2 Modul-Beschreibungsstruktur

int basic_sensor_setup( int ui_snr, int hei, int wid, int exp, int gain );
int save_imges_2_nfs( char *path, int hei, int wid );
int determine_calibration( char *path, int hei, int wid, short lower_tresh, short upper_tresh );
void display_vga( void *_name );

#endif /* !_3D_SCAN_SERVER_H_ */
