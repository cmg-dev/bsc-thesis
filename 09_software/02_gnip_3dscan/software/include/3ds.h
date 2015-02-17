/**
	@file 3ds.h 
	@author Christoph Gnip
	@date July 20th 2010
	@version 1.0
	@brief Collection of nice defines and utilities used in my thesis.

*/

#ifndef _3D_SCAN_H_
#define _3D_SCAN_H_

#ifndef SUCCESS
	#define SUCCESS 1
#endif
#ifndef FAILED
	#define FAILED 0
#endif

#define ALL_SENSORS 0

/* Defines redirect of the LEDA- bit defines, so that they are mathing my thesis */
#define LED_1 LEDA_EN_LED8_BIT
#define LED_2 LEDA_EN_LED7_BIT
#define LED_3 LEDA_EN_LED6_BIT
#define LED_4 LEDA_EN_LED5_BIT

/**
@def exit_if Exits if the expr (containing an if statement) is TRUE.
	Displays linenumber and file in the error message. Very usefull for small controls.

*/
#define exit_if(expr) \
		if(expr) { \
		  fprintf(stderr, "%s( %d ) %s\n", __FILE__, __LINE__, strerror(errno)); \
		  exit(1); \
		}

#endif
