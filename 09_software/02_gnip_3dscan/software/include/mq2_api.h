/**
	@file 		mq2_api.h
	@author		M. Brinker
	@brief		Headerfile for the MiniQuadrix II Software API
	@version	1.0
	@date 		26. Oktober 2009 
*/

#ifndef _MQ2_API_ 
#define _MQ2_API_

/**
	@def APILICENSE_FULL
	API is for full use. No restrictions
*/
#define		APILICENSE_FULL						0
#define		MAX_PB_HWBLOCKS						256			/* Maximale Anzahl Hardware-Peripherieblöcke im FPGA design */
#define		MAX_SENSORS						4			/* Maximale Anzahl an anschliessbaren Bildsensoren */
#define		HISTOGRAMM_DATA_DEPTH					256 			/*Enspricht 8 Bit */

//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
#define		PB_IDENT_MQ2_IDENT					0x4D513249		/* --> MQ2I */
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct PB_VGA_FIFO
	@brief Structure that holds spezific informations for the VGA_FIFO-Block

*/
typedef struct _PB_VGA_FIFO_
{
  	unsigned int	ui_vga_enable;								/**< TRUE enables VGA Controller. FALSE disables VGA Controller */
	unsigned int 	ui_inputchannel;							/**< Selects the input Channel (1 - 4) 0 --> FIFO disabled */
	unsigned short 	*pus_inputbuffer;							/**< Framebuffer to store Videodata from Channel */
	unsigned short 	*pus_vgasource;								/**< Pointer to VGA Source */
	int		i_vga_fifo_full;							/**< Is TRUE, when VGA-Fifo overruns. */
}PB_VGA_FIFO;
#define		PB_IDENT_VGA_FIFO					0x56474146		/* --> VGAF */
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct VE2_EVENT
	@brief Structure that holds event-info from the VE2 Block

*/
typedef struct _VE2_EVENT_
{
  	int	x1_event;								/**< X1 Coordinate of Event */
	int 	y1_event;								/**< Y1 Coordinate of Event */
	int 	width_event;								/**< Width of Event */
	int 	height_event;								/**< Height of Event */
}VE2_EVENT;
/**
	@struct PB_VIDEOENGINE
	@brief Structure that holds spezific informations for the Videoengine-Block

*/
typedef struct _PB_VIDEOENGINE_
{
	int	i_event_color;								/**< Color to find events (black or white) */
  	int	i_image_width;								/**< Width of the Image to analyse */
	int 	i_threshold;								/**< Threshold (Legal Values are 0 to 255) */
	int 	i_cluster_x;								/**< Clustering X (Legal Values are 0 to 255) */
	int 	i_cluster_y;								/**< Clustering Y (Legal Values are 0 to 255)  */
	int	i_enable_event_eliminizer;						/**< If True Events < minarea and > maxarea are excluded */
	int	i_minarea;								/**< Events must have this area min to be written into the fifo */
	int	i_maxarea;								/**< Events must have this area max to be written into the fifo */
	int	i_event_fifo_depth;							/**< Holds informations about the eventfifo depth */
	VE2_EVENT *t_event;								/**< Pointer to the event structur */
}PB_VIDEOENGINE;
#define		PB_IDENT_VIDEOENGINE					0x56454E32		/* --> VEN2 */
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct PB_SFIR
	@brief Structure that holds spezific informations for the SFIR-Block

*/
typedef struct _PB_SFIR_
{
  	unsigned int	ui_configuration_sfir;							/**< Selects the SFIR Outputmode  */
	char * pc_fir_1_coef;									/**< FIR1 cooefizients */
	char * pc_fir_2_coef;									/**< FIR2 cooefizients */
}PB_SFIR;
#define		PB_IDENT_SFIR						0x53464952		/* --> SFIR */
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct PB_HISTOGRAMM
	@brief Structure that holds spezific informations for the HISTOGRAMM-Block

*/
typedef struct _PB_HISTOGRAMM_
{
	int 	i_allways_enable_histogramm;							/**< 1 Enables Histogramm, 0 Disables Histogramm */
  	int	i_histogramm_data[HISTOGRAMM_DATA_DEPTH];					/**< Holds Histogramm  */
	int	i_error;									/**< Is set if an error condition occurs */
}PB_HISTOGRAMM;
#define		PB_IDENT_HISTOGRAMM					0x50484953		/* --> PHIS */
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct PB_IO
	@brief Structure that holds spezific informations for the IO-Block

*/
typedef struct _PB_IO_
{
	unsigned int	ui_Digital_OUT_MODE;							/**< Digital OUT Mode */
	unsigned int 	ui_Digital_OUT_DATA;							/**< Digital OUT Data */
	unsigned int 	ui_Digital_IN_MODE;							/**< Digital IN Mode */
	unsigned int 	ui_Digital_IN_DATA;							/**< Digital IN Data */
	
}PB_IO;
#define		PB_IDENT_IO						0x5042494F		/* --> PBIO */
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct PB_STEREO
	@brief Structure that holds spezific informations for the Steroskopie-Block

*/
typedef struct _PB_STEREO_EDGE_FITTER_
{
	int		i_KOEFF1_OPT0_S1;
	int		i_KOEFF2_OPT0_S1;
	int		i_KOEFF3_OPT0_S1;
	int		i_KOEFF1_OPT0_S2;
	int		i_KOEFF2_OPT0_S2;
	int		i_KOEFF3_OPT0_S2;
	int		i_KOEFF1_OPT1_S2;
	int		i_KOEFF2_OPT1_S2;
	int		i_KOEFF3_OPT1_S2;
	int		i_KOEFF1_OPT1_S3;
	int		i_KOEFF2_OPT1_S3;
	int		i_KOEFF3_OPT1_S3;
	int		i_KOEFF1_OPT2_S3;
	int		i_KOEFF2_OPT2_S3;
	int		i_KOEFF3_OPT2_S3;
	int		i_KOEFF1_OPT2_S4;
	int		i_KOEFF2_OPT2_S4;
	int		i_KOEFF3_OPT2_S4;
	int		i_FAKTOR_BASIS;
}PB_STEREO_EDGE_FITTER;

typedef struct _PB_STEREO_X_FITTER_
{
	int		i_X_OPT0_KOEFF1;
	int		i_X_OPT0_KOEFF2;
	int		i_X_OPT0_KOEFF3;
	int		i_X_OPT0_KOEFF4;
	int		i_X_OPT0_KOEFF5;
	int		i_X_OPT1_KOEFF1;
	int		i_X_OPT1_KOEFF2;
	int		i_X_OPT1_KOEFF3;
	int		i_X_OPT1_KOEFF4;
	int		i_X_OPT1_KOEFF5;
	int		i_X_OPT2_KOEFF1;
	int		i_X_OPT2_KOEFF2;
	int		i_X_OPT2_KOEFF3;
	int		i_X_OPT2_KOEFF4;
	int		i_X_OPT2_KOEFF5;
	int		i_FAKTOR_BASIS_X1;
	int		i_FAKTOR_BASIS_X2;
}PB_STEREO_X_FITTER;

typedef struct _PB_STEREO_
{
	int			i_X_POS;							/**< X-Offset */
	unsigned int 		ui_OVERLAP;							/**< Overlap */
	unsigned int 		ui_SCALE;							/**< Skalierung des Mittelwertes */
	unsigned int 		ui_GEGENSTANDSWEITE;						/**< Gegenstandsweite in mm * 1000000 */
	unsigned int		ui_Dp;
	unsigned int 		ui_Dk;
	unsigned int 		ui_BRENNWEITE;
	unsigned int		ui_BASIS;
	unsigned int		ui_Dk_SCALED;
	unsigned int		ui_MIN_DELTA;
	PB_STEREO_EDGE_FITTER	*t_edge_fitter;
	PB_STEREO_X_FITTER	*t_x_fitter;
	int			i_X_KOORD;
	int			i_Y_KOORD;
	int 			i_MW_BS0;
	int 			i_MW_BS1;
	int 			i_MW_BS2;
	int 			i_MW_BS3;
}PB_STEREO;
#define		PB_IDENT_STEREO						0x73746572		/* --> ster */


//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct PB_LEDA
	@brief Structure that holds spezific informations for the Steroskopie-Block

*/
typedef struct _PB_LEDA_
{
	  unsigned int	ui_data;
	  unsigned int	ui_pd;
	  unsigned int  ui_config;
	  unsigned int	ui_led_on_time;
	  unsigned int	ui_led_en;
}PB_LEDA;
#define		PB_IDENT_LEDA						0x4C454441		/* --> LEDA */
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct PB_DATAPLEXER
	@brief Structure that holds spezific informations for the DATAPLEXER-Block

*/
typedef struct _PB_DATAPLEXER_
{
	int 	i_dapl_pisi_mux;								/**< Picture Simulator MUX */
	int 	i_dapl_vfif_mux;								/**< Video Fifo to CPU MUX */
	int 	i_dapl_sfir_mux;								/**< Super FIR MUX */
	int 	i_dapl_ven2_mux;								/**< Videoengine MUX */
	int 	i_dapl_thbl_mux;								/**< Threshold MUX */
	int 	i_dapl_hist_mux;								/**< Histogramm MUX */
	int 	i_dapl_mon_mux;									/**< VGA Monitor MUX */
	int	i_image_size;									/**< Size of the image to store (Width * Height in Pixel) */
	short 	*ps_vfif_framebuffer;								/**< Framebufferpointer for the VFIF Interface */
}PB_DATAPLEXER;
#define		PB_IDENT_DATAPLEXER					0x4441504C		/* --> DAPL */
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct PB_THRESHOLD
	@brief Structure that holds spezific informations for the THRESHOLD-Block

*/
typedef struct _PB_THRESHOLD_
{
	short	s_thres_lower;									/**< Threshold (signed Short) */
	short	s_thres_upper;
}PB_THRESHOLD;
#define		PB_IDENT_THRESHOLD					0x5452484F		/* --> TRHO */
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct PB_PISI
	@brief Structure that holds spezific informations for the Picture-Simulator-Block

*/
typedef struct _PB_PISI_
{
	unsigned int ui_image_width;								/**< PISI Image width */
	unsigned int ui_image_height;								/**< PISI Image height */
	short 	*ps_framebuffer;								/**< Framebufferpointer */
}PB_PISI;
#define		PB_IDENT_PISI						0x50495349		/* --> PISI */
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct PB_RLEE
	@brief Structure that holds spezific informations for the RLE Encoder

*/
typedef struct _PB_RLEE_
{
	unsigned short us_rle_data;								/**< RLEE Data */
}PB_RLEE;
#define		PB_IDENT_RLEE						0x524C4545		/* --> RLEE */
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct PB_SENSOR_CONTROL
	@brief Structure that holds spezific informations for the SENSOR_CONTROL-Block

*/
typedef struct _PB_SENSOR_CONTROL_
{
	int 	i_sensor_reset;
	int 	i_sensor_1_resetenable;
	int 	i_sensor_2_resetenable;
	int 	i_sensor_3_resetenable;
	int 	i_sensor_4_resetenable;
	int 	i_sensor_1_exposureenable;
	int 	i_sensor_2_exposureenable;
	int 	i_sensor_3_exposureenable;
	int 	i_sensor_4_exposureenable;	
	int 	i_EXP_FREQ;
	int	i_BASE_FREQ;
	int	i_sensor_1_exp_freq_enable;
	int	i_sensor_2_exp_freq_enable;
	int	i_sensor_3_exp_freq_enable;
	int	i_sensor_4_exp_freq_enable;
    
}PB_SENSOR_CONTROL;
#define		PB_IDENT_SENSOR_CONTROL					0x5343544C		/* --> SCTL */
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct PB_SENSOR_SYNCHRONIZER
	@brief Structure that holds spezific informations for the SENSOR_SYNCHRONIZER-Block

*/
typedef struct _PB_SENSOR_SYNCHRONIZER_
{
	unsigned int ui_sensor1_lostsync;							/**< Is TRUE, if the Sensor 1 Downstream is out of sync */
	unsigned int ui_sensor2_lostsync;							/**< Is TRUE, if the Sensor 2 Downstream is out of sync */
	unsigned int ui_sensor3_lostsync;							/**< Is TRUE, if the Sensor 3 Downstream is out of sync */
	unsigned int ui_sensor4_lostsync;							/**< Is TRUE, if the Sensor 4 Downstream is out of sync */
	unsigned int ui_sensor1_phasesteps;
	unsigned int ui_sensor2_phasesteps;
	unsigned int ui_sensor3_phasesteps;
	unsigned int ui_sensor4_phasesteps;
}PB_SENSOR_SYNCHRONIZER;
#define		PB_IDENT_SENSOR_SYNCHRONIZER				0x53455359		/* --> SESY */
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct PB_LVDS_OUT
	@brief Structure that holds spezific informations for the LVDS_OUT-Block
	@param i_enable_driver Enables the onboard LVDS-Driver
	@param i_enable_upstream_1 Enables the onchip LVDS Upstream to Sensor 1
	@param i_enable_upstream_2 Enables the onchip LVDS Upstream to Sensor 2
	@param i_enable_upstream_3 Enables the onchip LVDS Upstream to Sensor 3
	@param i_enable_upstream_4 Enables the onchip LVDS Upstream to Sensor 4
	@param i_force_sync Switches on the 'force_sync' Datapattern
*/
typedef struct _PB_LVDS_OUT_
{
	int i_enable_driver;
	int i_enable_upstream_1;
	int i_enable_upstream_2;
	int i_enable_upstream_3;
	int i_enable_upstream_4;
	int i_force_sync;
}PB_LVDS_OUT;
#define		PB_IDENT_LVDS_OUT					0x4C4F5554		/* --> LOUT */
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct PB_POWER_SUPERVISOR
	@brief Structure that holds spezific informations for the POWER-SUPERVISOR-Block
	@param i_pg_3v3 3,3V Power-Good
	@param i_pg_5v0 5,0V Power-Good
	@param i_pe_3v3 3,3V Power-Error
	@param i_pe_5v0 5,0V Power-Error
	@param i_5v0_switch 5,0V DCDC-Converter Status
*/
typedef struct _PB_POWER_SUPERVISOR_
{
	int i_pg_3v3;
	int i_pg_5v0;
	int i_pe_3v3;
	int i_pe_5v0;
	int i_5v0_switch;
}PB_POWER_SUPERVISOR;
/**
	@def PB_IDENT_POWER_SUPERVISOR
	Ident for the Power-Supervisor Block
*/
#define		PB_IDENT_POWER_SUPERVISOR				0x504F5355 		/* --> POSU */	
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct PERIPH_BLOCK
	@brief Structure that holds infos about the PERIPH_BLOCK.
*/
typedef struct _PERIPH_BLOCK_
{
	int i_ident;							/**< Periph Blockident */
	int i_version;							/**< Periph Blockversion */
	void *pv_pb_desc;						/**< Void Pointer to the PBlock dependent hardwarestructure */
	int i_base;							/**< Baseaddress in the AVALON Memory Map of this Block */
	int i_index;							/**< Instance Index. 1 is associated with Channel 1, 2 with channel 2 and so on... */
	
}PERIPH_BLOCK;
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct API_INFO
	@brief Structure that holds infos about the API.
	@param i_version API Version
	@param i_revision API Revision
	@param i_license API License
*/
typedef struct _API_INFO_
{
	int i_version;
	int i_revision;
	int i_license;
}API_INFO;
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct LED_CONTROLLER
	@brief Structure that holds all infos about the LED_CONTROLLER. (Sensorconnector-Leds)
*/
typedef struct _LED_CONTROLLER_
{
	unsigned int ui_led_1_green;					/**< Mode of the Green Led from Connector #1 */
	unsigned int ui_led_1_yellow;					/**< Mode of the Yellow Led from Connector #1 */
	unsigned int ui_led_2_green;					/**< Mode of the Green Led from Connector #2 */
	unsigned int ui_led_2_yellow;					/**< Mode of the Yellow Led from Connector #2 */
	unsigned int ui_led_3_green;					/**< Mode of the Green Led from Connector #3 */
	unsigned int ui_led_3_yellow;					/**< Mode of the Yellow Led from Connector #3 */
	unsigned int ui_led_4_green;					/**< Mode of the Green Led from Connector #4 */
	unsigned int ui_led_4_yellow;					/**< Mode of the Yellow Led from Connector #4 */
	unsigned int ui_blinkrate_pwm0;					/**< Blinkrate in Hz from the PWM0 counter */
	unsigned int ui_duty_cycle_pwm0;				/**< Dutycycle in % (on-time) for the PWM0 counter */
	unsigned int ui_blinkrate_pwm1;					/**< Blinkrate in Hz from the PWM1 counter */
	unsigned int ui_duty_cycle_pwm1;				/**< Dutycycle in % (on-time)for the PWM1 counter */
}LED_CONTROLLER;
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct TRIGGER_INFO
	@brief Structure that holds all infos about the Trigger-Modes
*/
typedef struct _TRIGGER_INFO_
{
	unsigned int	ui_trigger_mode;				/**< Selects the Trigger Mode for the Sensor. */
	unsigned int	ui_trigger_delay;				/**< Delay in µs between Trigger and Exposure */
	unsigned int	ui_trigger_source;				/**< Selects Triggersource */
}TRIGGER_INFO;
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct SENSOR_INFO
	@brief Structure that holds all infos about a connected Sensor-Module.
	@see TRIGGER_INFO
*/
typedef struct _SENSOR_INFO_
{
	unsigned int 	ui_channel;					/**< Channel where the sensor is connected */
	unsigned short 	us_id;						/**< Holds the value from the Ident register from the sensor */
	unsigned short 	us_image_width;					/**< Width of the imagewindow */
	unsigned short 	us_image_height;				/**< Height of the imagewindow */
	unsigned short 	us_image_startx;				/**< Startcolumn of the imagewindow */
	unsigned short 	us_image_starty;				/**< Startrow of the imagewindow */
	unsigned int	ui_col_flip;					/**< TRUE flips column readout */
	unsigned int	ui_row_flip;					/**< TRUE flips row readout */
	unsigned int 	ui_exposure;					/**< Exposuretime */
	unsigned int 	ui_gain;					/**< Gain */
	unsigned int 	ui_aec_agc;					/**< Switch on or off the aec/agc */
	unsigned int 	ui_adc_mode;					/**< ADC Mode **/
	TRIGGER_INFO 	*trigger_info;					/**< Informationen about the trigger to use for this sensor */
}SENSOR_INFO;
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
/**
	@struct MQ2_MODULE_DESC
	@brief Structure that holds all infos about the MQ2-Module.
	@brief This structure is a list of pointers.
	
	@see API_INFO
	@see PERIPH_BLOCK
	@see SENSOR_INFO
	@see LED_CONTROLLER
*/
typedef struct _MQ2_MODULE_DESC_
{
	API_INFO *api_info;						/**< API_INFO Structureruct */
	PERIPH_BLOCK *periph_block[MAX_PB_HWBLOCKS];			/**< Periph-Block tructure */
	SENSOR_INFO *sensor_info[MAX_SENSORS];				/**< SENSOR_INFO Structure */
	LED_CONTROLLER *led_controller;					/**< LED_CONTROLLER Structure */
}MQ2_MODULE_DESC;
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************************+
//*********************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************************





//Funktionsprototypen
//Highlevel Funktionen
MQ2_MODULE_DESC * mq2api_make_module_description(void);
int mq2api_free_module_description(MQ2_MODULE_DESC *t_mq2_module_desc);
int mq2api_mappb(MQ2_MODULE_DESC *t_mq2_module_desc, void **pv_pb_desc, int i_periph_ident, int i_periph_index);
int mq2api_getfeature(MQ2_MODULE_DESC *t_mq2_module_desc, int i_feature_category, int i_feature, ...);
int mq2api_setfeature(MQ2_MODULE_DESC *t_mq2_module_desc, int i_feature_category, int i_feature, ...);
int mq2api_mark_events(short *framebuffer, VE2_EVENT *t_events, unsigned int featurelist);


//Lowlevel Funktionen
int i2c_init(unsigned int ui_channel, unsigned int ui_enable, unsigned int ui_i2c_speed, unsigned int ui_core_speed);
int i2c_read_word(unsigned int ui_channel, unsigned char uc_slave_address, unsigned short us_register_address);
int i2c_write_word (unsigned int ui_channel, unsigned char uc_slave_address, unsigned short us_register_address, unsigned short us_value);
int i2c_write_byte (unsigned int ui_channel, unsigned char uc_slave_address, unsigned short us_register_address, unsigned char uc_value);
int write_imagesensor_reg (unsigned int ui_channel, unsigned char uc_slave_address, unsigned short us_register_address, unsigned short us_value);
int read_imagesensor_reg (unsigned int ui_channel, unsigned char uc_slave_address, unsigned short us_register_address);
int write_imagesensor_reg_bit (unsigned int ui_channel, unsigned char uc_slave_address, unsigned short us_register_address, unsigned int ui_bitnumber, unsigned char uc_value);
int set_led_controller (LED_CONTROLLER *t_led_controller);
int find_sensor_sync (PERIPH_BLOCK *periph_block, unsigned int ui_pllno);
int step_pll_phase_down (PERIPH_BLOCK *periph_block, unsigned int ui_pllno);
int step_pll_phase_up (PERIPH_BLOCK *periph_block, unsigned int ui_pllno);

//Lowestlevel Funktionen
int write_register_bit(unsigned int baseaddr, unsigned int regaddr, unsigned int bitnumber, unsigned int value);
int read_register_bit(unsigned int baseaddr, unsigned int regaddr, unsigned int bitnumber);
int clear_register(unsigned int baseaddr, unsigned int regaddr);
int set_register(unsigned int baseaddr, unsigned int regaddr);
int write_register (unsigned int baseaddr, unsigned int regaddr, unsigned int data);
int write_register_short (unsigned int baseaddr, unsigned int regaddr, short data);
unsigned int read_piece_of_reg(unsigned int REG_BASE, unsigned int REG_OFFSET, unsigned char piece_offset, unsigned char piece_length);
int write_piece_of_reg(unsigned int REG_BASE, unsigned int REG_OFFSET, unsigned char piece_offset, unsigned char piece_length, unsigned int value);
unsigned int uncached (unsigned int baseaddr);
int read_register (unsigned int baseaddr, unsigned int regaddr);



//Defines für get und setfeature
#define		POWER_SUPERVISOR					0
#define		MQ2_IDENT						1
#define		LVDS_OUT						2
#define		SENSOR_CONTROL						3
#define		SENSOR_SYNCHRONIZER					4
#define		VGA_FIFO						5
#define		SFIR							6 
#define		SFIR1							7
#define		SFIR2							8
#define		SFIR3							9
#define		SFIR4							10
#define		PHIS							11
#define		PHIS1							12
#define		PHIS2							13
#define		PHIS3							14
#define		PHIS4							15
#define		DAPL							16
#define		DAPL1							17
#define		DAPL2							18
#define		DAPL3							19
#define		DAPL4							20
#define		TRHO							21
#define		TRHO1							22
#define		TRHO2							23
#define		TRHO3							24
#define		TRHO4							25
#define		SENSOR1							26
#define		SENSOR2							27
#define		SENSOR3							28
#define		SENSOR4							29
#define		VE1							30
#define		VE2							31
#define		VE3							32
#define		VE4							33
#define		IO							34
#define		STEREO							35
#define		PISI1							36
#define		PISI2							37
#define		PISI3							38
#define		PISI4							39
#define		RLEE							40
#define		LEDA							41





//Defines für mq2api_mark_events 
#define		DRAW_RECTANGLE						1


//Defines für Featureliste (Alle Blöcke)
#define		ALL_FEATURES						0

//Features POWER_SUPERVISOR
#define		SWITCH_EXTPOWER						1
#define		RESET_5V0_ERROR						2
#define		RESET_3V3_ERROR						3

//Features SENSOR_SYNCHRONIZER
#define		RESET_ALL_LOSTSYNC_FLAGS				4
#define		RESET_LOSTSYNC_FLAG_1					5
#define		RESET_LOSTSYNC_FLAG_2					6
#define		RESET_LOSTSYNC_FLAG_3					7
#define		RESET_LOSTSYNC_FLAG_4					8

//Features für VGA_FIFO und SG-DMA
#define		INITIALIZE_VGA						9
#define		START_VGA						10
#define		STOP_VGA						11
#define		CHANGE_VGASOURCE					12
#define		CHANGE_INPUTBUFFER					13
#define		RELOAD_DMA						14
#define		CHANGE_CHANNEL						15
#define		WAIT_FOR_DMA_READY					16


//Features für SENSOR_CONTROL		
#define		EXPOSURE						400

//Defines für DATAPLEXER
#define		THBL_DATA						0
#define		VFIF_DATA						1
#define		PISI_DATA						2
#define		SFIR_DATA						3
#define		SENSOR_DATA						4

//Features für SFIR
#define		SET_FIR1_COEF						500
#define		SET_FIR2_COEF						501
#define		SET_FIR_CONFIG						502
#define		ONLY_FIR1						0
#define		ONLY_FIR2						1
#define		FIR1_PLUS_FIR2						2
#define		CANNY							3
#define		FIR1_ABS						4
#define		FIR2_ABS						5
#define		FIR1_PLUS_FIR2_ABS					6
#define		FIR1_AND_FIR2_ABS					7
#define		FIR1_OR_FIR2_ABS					8
#define		FIR1_XOR_FIR2_ABS					9

//Features für VE2
#define		GET_EVENTS						600


#define		FEATURE_NOT_FOUND					-1000
#define 	FEATURE_FOUND						1
#define		FEATURE_FOUND_BUT_NOT_ACCESSIBLE			-1001
#define		RET_FEATURE_NOT_AVAILABLE				-1002
#define		RET_FEATURE_CATEGORY_NOT_AVAILABLE			-1003
#define		RET_FEATURE_NOT_ACCESSIBLE				-1004
#define		RET_SUCCESS						0
#define		RET_I2C_WRONG_CHANNEL					-1005	/* Channel is not valid */
#define		RET_DMA_TIMEOUT						-1006  /* Timeout beim DMA */
#define		SENSOR_NOT_CONNECTED					-1007  /*Sensor not connected */
#define		RET_WRONG_PB						-2000	/* Wrong Periphblock for that function */
#define		RET_CANNOT_FIND_END_OF_EYE				-2001   /* End of Eye cannot be found in the Synchronizer */
#define		RET_CANNOT_FIND_START_OF_EYE				-2002   /* Start of Eye cannot be found in the Synchronizer */
#define		RET_WRONG_PLL_CHANNEL					-2003	/* Wrong PLL Channel selected */
#define		RET_PB_NOT_FOUND					-2004
#define		RET_WRONG_PB_INDEX					-2005

//Features für IO
#define		WRITE_IO_OUTPUT						701
#define		GET_IO_INPUT						702
#define		RESET_IO_INPUT						703
#define		IO_OUTPUT_MODE_SINGLEBIT				0
#define	 	IO_INPUT_MODE_SINGLEBIT					0
#define	 	IO_INPUT_MODE_COUNTER					1

//Features für Stereoskopie Block
#define		GET_STEREO_RESULT					35001
#define		GET_STEREO_MW						35002
#define		RESET_ANALYSIS						35101	


//Featrues für PISI Block
#define		PISI_START						36001
#define		PISI_RESET						36002

//FEATURES für RLEE Block
#define		RLEE_RESET						40001

#define		IS_CLEAR						0
#define		IS_SET							1
#define		TRUE							1
#define		FALSE							0
#define		ON							1
#define		OFF							0

//Features für LEDA
#define		LEDA_RESET						41000
#define		LEDA_MOD						0x01
#define		LEDA_ENABLE						0x02
#define		LEDA_LED_ORANGE						0x04
#define		LEDA_LED_GREEN						0x08
#define		LEDA_EN_EXT_MOD						0x10
#define			LEDA_EN_LED1_BIT				0x01
#define			LEDA_EN_LED2_BIT				0x02
#define			LEDA_EN_LED3_BIT				0x04
#define			LEDA_EN_LED4_BIT				0x08
#define			LEDA_EN_LED5_BIT				0x10
#define			LEDA_EN_LED6_BIT				0x20
#define			LEDA_EN_LED7_BIT				0x40
#define			LEDA_EN_LED8_BIT				0x80

#define		LEDA_NORMAL_OPERATION					0
#define		LEDA_HIGH_IMPEDANCE					3


//Defines für Trigger
#define		TMODE_SNAPSHOT						0	/* Triggermodus SNAPSHOT */
#define		TSOURCE_GLOBAL						0	/* Triggersource GLOBAL */

//Defines für Videoengine
#define		BLACK							0
#define		WHITE							1



//Defines für LED-Controller
#define		LED_CONTROLLER_I2C_ADDR					0x60
#define		REG_PSC0						0x01
#define		REG_PWM0						0x02
#define		REG_PSC1						0x03
#define		REG_PWM1						0x04
#define		REG_LS0							0x05
#define		REG_LS1							0x06
#define		LED_ON							0x0
#define		LED_OFF							0x1
#define		LED_BLINK_PWM0						0x2
#define		LED_BLINK_PWM1						0x3


//Defines fuer I2C
#define   	I2C_PRERLO 						0x00
#define   	I2C_PRERHI  						0x04
#define   	I2C_CTR     						0x08
#define   	I2C_TXR     						0x0C
#define   	I2C_RXR     						0x0C
#define   	I2C_CR      						0x10
#define   	I2C_SR      						0x10

#define   	I2C_STA     						0x80
#define   	I2C_STO     						0x40
#define   	I2C_RD     						0x20
#define   	I2C_WR      						0x10
#define   	I2C_TIP     						0x02
#define   	I2C_ACK     						0x08
#define   	I2C_SL_ACK  						0x80
#define   	I2C_TXR_WR  						0x01
#define   	I2C_AL      						0x20
#define  	 I2C_BUSY   						0x40

#define	  	I2C_ENABLE						0x80

#define		I2C_CHANNEL_1						1
#define		I2C_CHANNEL_2						2
#define		I2C_CHANNEL_3						4
#define		I2C_CHANNEL_4						8


//Defines für Sensorkanäle
#define		IMAGE_SENSOR_CONNECTOR_1				1
#define		IMAGE_SENSOR_CONNECTOR_2				2
#define		IMAGE_SENSOR_CONNECTOR_3				4
#define		IMAGE_SENSOR_CONNECTOR_4				8




/* Dynamic bus access functions */
typedef signed char  alt_8;
typedef unsigned char  alt_u8;
typedef signed short alt_16;
typedef unsigned short alt_u16;
typedef signed long alt_32;
typedef unsigned long alt_u32;
typedef long long alt_64;
typedef unsigned long long alt_u64;

#define ALT_INLINE        __inline__
#define ALT_ALWAYS_INLINE __attribute__ ((always_inline))
#define ALT_WEAK          __attribute__((weak))
#define __IO_CALC_ADDRESS_DYNAMIC(BASE, OFFSET) \
  ((void *)(((alt_u8*)BASE) + (OFFSET)))

#define IORD_32DIRECT(BASE, OFFSET) \
  __builtin_ldwio (__IO_CALC_ADDRESS_DYNAMIC ((BASE), (OFFSET)))
#define IORD_16DIRECT(BASE, OFFSET) \
  __builtin_ldhuio (__IO_CALC_ADDRESS_DYNAMIC ((BASE), (OFFSET)))
#define IORD_8DIRECT(BASE, OFFSET) \
  __builtin_ldbuio (__IO_CALC_ADDRESS_DYNAMIC ((BASE), (OFFSET)))

#define IOWR_32DIRECT(BASE, OFFSET, DATA) \
  __builtin_stwio (__IO_CALC_ADDRESS_DYNAMIC ((BASE), (OFFSET)), (DATA))
#define IOWR_16DIRECT(BASE, OFFSET, DATA) \
  __builtin_sthio (__IO_CALC_ADDRESS_DYNAMIC ((BASE), (OFFSET)), (DATA))
#define IOWR_8DIRECT(BASE, OFFSET, DATA) \
  __builtin_stbio (__IO_CALC_ADDRESS_DYNAMIC ((BASE), (OFFSET)), (DATA))

/* Native bus access functions */

#define __IO_CALC_ADDRESS_NATIVE(BASE, REGNUM) \
  ((void *)(((alt_u8*)BASE) + ((REGNUM) * (SYSTEM_BUS_WIDTH/8))))

#define IORD(BASE, REGNUM) \
  __builtin_ldwio (__IO_CALC_ADDRESS_NATIVE ((BASE), (REGNUM)))
#define IOWR(BASE, REGNUM, DATA) \
  __builtin_stwio (__IO_CALC_ADDRESS_NATIVE ((BASE), (REGNUM)), (DATA))


void vid_set_pixel(int horiz, int vert, unsigned int color, int frame_buffer);
void vid_draw_horiz_line (short Hstart, short Hend, int V, int color, int frame_buffer);
void vid_draw_line(int horiz_start, int vert_start, int horiz_end, int vert_end, int width, int color, int frame_buffer);
int vid_draw_box (int horiz_start, int vert_start, int horiz_end, int vert_end, int color, int fill, int frame_buffer);
void vid_draw_sloped_line( unsigned short horiz_start, 
                           unsigned short vert_start, 
                           unsigned short horiz_end, 
                           unsigned short vert_end, 
                           unsigned short width, 
                           int color, 
                           int frame_buffer);
int vid_print_char (int horiz_offset, int vert_offset, int color, char character, char *font, int frame_buffer);
int vid_draw_cross (int schwerx, int schwery, int color, int frame_buffer);
int vid_print_string(int horiz_offset, int vert_offset, int color, char *font, int frame_buffer, char string[]);
void vid_circle_points(int cx, int cy, int x, int y, int color, char fill, int frame_buffer);
int vid_draw_circle(int Hcenter, int Vcenter, int radius, int color, char fill, int frame_buffer);

#define DO_FILL 1
#define DO_NOT_FILL 0

#define BLACK_8 0x00

#define FONT_10PT_ROW 11
#define FONT_10PT_COLUMN 8


typedef struct {
  int hbegin;
  int vbegin;
  int hend;
  int f_color;
  int b_color;
  char* string;
  char* font;
  int ms_delay;
  int ticks_at_last_move;
  int text_scroll_index;
  char text_scroll_started;
  int window_width;
  int length_of_string;
  int scroll_points;
  int string_points;
} vid_text_scroll_struct;


typedef struct {
	int   vertex_x[3];
	int   vertex_y[3];
//  int   ax, ay;
//  int   bx, by;
//  int   cx, cy;
  int   spans_needed;
  int   max_span;
  int   top_y;
  int   bottom_y;
  int   col;
  int   fill;
  int   center_z;
  int   *span_array;
} triangle_struct;

/* color conversion macro */
#define vid_color_convert24_16_m( x ) (unsigned short)(((*(x + 2) & 0xF8) >> 3) | ((*(x + 1) & 0xFC) << 3) | ((*(x + 0) & 0xF8) << 8))





                           
//Color Definitions

#define ALICEBLUE_16            0xF7DF
#define ANTIQUEWHITE_16         0xFF5A
#define AQUA_16                 0x07DF
#define AQUAMARINE_16           0x7FDA
#define AZURE_16                0xF7DF
#define BEIGE_16                0xF79B
#define BISQUE_16               0xFF18
#define BLACK_16                0x0000
#define BLANCHEDALMOND_16       0xFF59
#define BLUE_16                 0x001F
#define BLUEVIOLET_16           0x895C
#define BROWN_16                0xA145
#define BURLYWOOD_16            0xDDD0
#define CADETBLUE_16            0x5CD4
#define CHARTREUSE_16           0x7FC0
#define CHOCOLATE_16            0xD343
#define CORAL_16                0xFBCA
#define CORNFLOWERBLUE_16       0x649D
#define CORNSILK_16             0xFFDB
#define CRIMSON_16              0xD887
#define CYAN_16                 0x07DF
#define DARKBLUE_16             0x0011
#define DARKCYAN_16             0x0451
#define DARKGOLDENROD_16        0xBC01
#define DARKGRAY_16             0xAD55
#define DARKGREEN_16            0x0300
#define DARKKHAKI_16            0xBD8D
#define DARKMAGENTA_16          0x8811
#define DARKOLIVEGREEN_16       0x5345
#define DARKORANGE_16           0xFC40
#define DARKORCHID_16           0x9999
#define DARKRED_16              0x8800
#define DARKSALMON_16           0xEC8F
#define DARKSEAGREEN_16         0x8DD1
#define DARKSLATEBLUE_16        0x49D1
#define DARKSLATEGRAY_16        0x2A49
#define DARKTURQUOISE_16        0x065A
#define DARKVIOLET_16           0x901A
#define DEEPPINK_16             0xF892
#define DEEPSKYBLUE_16          0x05DF
#define DIMGRAY_16              0x6B4D
#define DODGERBLUE_16           0x1C9F
#define FELDSPAR_16             0xD48E
#define FIREBRICK_16            0xB104
#define FLORALWHITE_16          0xFFDE
#define FORESTGREEN_16          0x2444
#define FUCHSIA_16              0xF81F
#define GAINSBORO_16            0xDEDB
#define GHOSTWHITE_16           0xFFDF
#define GOLD_16                 0xFE80
#define GOLDENROD_16            0xDD04
#define GRAY_16                 0x8410
#define GRAY25_16               0x4208
#define GRAY50_16               0x7BCF
#define GRAY75_16               0xC618
#define GREEN_16                0x0400
#define GREENYELLOW_16          0xAFC5
#define HONEYDEW_16             0xF7DE
#define HOTPINK_16              0xFB56
#define INDIANRED_16            0xCACB
#define INDIGO_16               0x4810
#define IVORY_16                0xFFDE
#define KHAKI_16                0xF711
#define LAVENDER_16             0xE71F
#define LAVENDERBLUSH_16        0xFF9E
#define LAWNGREEN_16            0x7FC0
#define LEMONCHIFFON_16         0xFFD9
#define LIGHTBLUE_16            0xAEDC
#define LIGHTCORAL_16           0xF410
#define LIGHTCYAN_16            0xE7DF
#define LIGHTGOLDENRODYELLOW_16 0xFFDA
#define LIGHTGREEN_16           0x9752
#define LIGHTGREY_16            0xD69A
#define LIGHTPINK_16            0xFD98
#define LIGHTSALMON_16          0xFD0F
#define LIGHTSEAGREEN_16        0x2595
#define LIGHTSKYBLUE_16         0x865F
#define LIGHTSLATEBLUE_16       0x839F
#define LIGHTSLATEGRAY_16       0x7453
#define LIGHTSTEELBLUE_16       0xB61B
#define LIGHTYELLOW_16          0xFFDC
#define LIME_16                 0x07C0
#define LIMEGREEN_16            0x3646
#define LINEN_16                0xFF9C
#define MAGENTA_16              0xF81F
#define MAROON_16               0x8000
#define MEDIUMAQUAMARINE_16     0x6655
#define MEDIUMBLUE_16           0x0019
#define MEDIUMORCHID_16         0xBA9A
#define MEDIUMPURPLE_16         0x939B
#define MEDIUMSEAGREEN_16       0x3D8E
#define MEDIUMSLATEBLUE_16      0x7B5D
#define MEDIUMSPRINGGREEN_16    0x07D3
#define MEDIUMTURQUOISE_16      0x4E99
#define MEDIUMVIOLETRED_16      0xC090
#define MIDNIGHTBLUE_16         0x18CE
#define MINTCREAM_16            0xF7DF
#define MISTYROSE_16            0xFF1C
#define MOCCASIN_16             0xFF16
#define NAVAJOWHITE_16          0xFED5
#define NAVY_16                 0x0010
#define OLDLACE_16              0xFF9C
#define OLIVE_16                0x8400
#define OLIVEDRAB_16            0x6C44
#define ORANGE_16               0xFD00
#define ORANGERED_16            0xFA00
#define ORCHID_16               0xDB9A
#define PALEGOLDENROD_16        0xEF55
#define PALEGREEN_16            0x9FD3
#define PALETURQUOISE_16        0xAF5D
#define PALEVIOLETRED_16        0xDB92
#define PAPAYAWHIP_16           0xFF5A
#define PEACHPUFF_16            0xFED7
#define PERU_16                 0xCC07
#define PINK_16                 0xFE19
#define PLUM_16                 0xDD1B
#define POWDERBLUE_16           0xB71C
#define PURPLE_16               0x8010
#define RED_16                  0xF800
#define ROSYBROWN_16            0xBC51
#define ROYALBLUE_16            0x0092
#define SADDLEBROWN_16          0x8A02
#define SALMON_16               0xFC0E
#define SANDYBROWN_16           0xF50C
#define SEAGREEN_16             0x2C4A
#define SEASHELL_16             0xFF9D
#define SIENNA_16               0xA285
#define SILVER_16               0xC618
#define SKYBLUE_16              0x865D
#define SLATEBLUE_16            0x6AD9
#define SLATEGRAY_16            0x7412
#define SNOW_16                 0xFFDF
#define SPRINGGREEN_16          0x07CF
#define STEELBLUE_16            0x4416
#define TAN_16                  0xD591
#define TEAL_16                 0x0410
#define THISTLE_16              0xDDDB
#define TOMATO_16               0xFB08
#define TURQUOISE_16            0x471A
#define VIOLET_16               0xEC1D
#define VIOLETRED_16            0xD112
#define WHEAT_16                0xF6D6
#define WHITE_16                0xFFDF
#define WHITESMOKE_16           0xF79E
#define YELLOW_16               0xFFC0
#define YELLOWGREEN_16          0x9E46

#define ALICEBLUE_24            0xFFF8F0
#define ANTIQUEWHITE_24         0xD7EBFA
#define AQUA_24                 0xFFFF00
#define AQUAMARINE_24           0xD4FF7F
#define AZURE_24                0xFFFFF0
#define BEIGE_24 								0xDCF5F5
#define BISQUE_24 							0xC4E4FF
#define BLACK_24 								0x000000
#define BLANCHEDALMOND_24 			0xCDEBFF
#define BLUE_24 								0xFF0000
#define BLUEVIOLET_24 					0xE22B8A
#define BROWN_24 								0x2A2AA5
#define BURLYWOOD_24 						0x87B8DE
#define CADETBLUE_24 						0xA09E5F
#define CHARTREUSE_24 					0x00FF7F
#define CHOCOLATE_24 						0x1E69D2
#define CORAL_24 								0x507FFF
#define CORNFLOWERBLUE_24 			0xED9564
#define CORNSILK_24 						0xDCF8FF
#define CRIMSON_24 							0x3C14DC
#define CYAN_24 								0xFFFF00
#define DARKBLUE_24 						0x8B0000
#define DARKCYAN_24 						0x8B8B00
#define DARKGOLDENROD_24 				0x0B86B8
#define DARKGRAY_24 						0xA9A9A9
#define DARKGREEN_24 						0x006400
#define DARKKHAKI_24 						0x6BB7BD
#define DARKMAGENTA_24 					0x8B008B
#define DARKOLIVEGREEN_24 			0x2F6B55
#define DARKORANGE_24 					0x008CFF
#define DARKORCHID_24 					0xCC3299
#define DARKRED_24 							0x00008B
#define DARKSALMON_24 					0x7A96E9
#define DARKSEAGREEN_24 				0x8FBC8F
#define DARKSLATEBLUE_24 				0x8B3D48
#define DARKSLATEGRAY_24 				0x4F4F2F
#define DARKTURQUOISE_24 				0xD1CE00
#define DARKVIOLET_24 					0xD30094
#define DEEPPINK_24 						0x9314FF
#define DEEPSKYBLUE_24 					0xFFBF00
#define DIMGRAY_24 							0x696969
#define DODGERBLUE_24 					0xFF901E
#define FELDSPAR_24 						0x7592D1
#define FIREBRICK_24 						0x2222B2
#define FLORALWHITE_24 					0xF0FAFF
#define FORESTGREEN_24 					0x228B22
#define FUCHSIA_24 							0xFF00FF
#define GAINSBORO_24 						0xDCDCDC
#define GHOSTWHITE_24 					0xFFF8F8
#define GOLD_24 								0x00D7FF
#define GOLDENROD_24 						0x20A5DA
#define GRAY_24 								0x808080
#define GREEN_24 								0x008000
#define GREENYELLOW_24 					0x2FFFAD
#define HONEYDEW_24 						0xF0FFF0
#define HOTPINK_24 							0xB469FF
#define INDIANRED_24 						0x5C5CCD
#define INDIGO_24 							0x82004B
#define IVORY_24 								0xF0FFFF
#define KHAKI_24 								0x8CE6F0
#define LAVENDER_24 						0xFAE6E6
#define LAVENDERBLUSH_24 				0xF5F0FF
#define LAWNGREEN_24 						0x00FC7C
#define LEMONCHIFFON_24 				0xCDFAFF
#define LIGHTBLUE_24 						0xE6D8AD
#define LIGHTCORAL_24 					0x8080F0
#define LIGHTCYAN_24 						0xFFFFE0
#define LIGHTGOLDENRODYELLOW_24 0xD2FAFA
#define LIGHTGREEN_24 					0x90EE90
#define LIGHTGREY_24 						0xD3D3D3
#define LIGHTPINK_24 						0xC1B6FF
#define LIGHTSALMON_24 					0x7AA0FF
#define LIGHTSEAGREEN_24 				0xAAB220
#define LIGHTSKYBLUE_24 				0xFACE87
#define LIGHTSLATEBLUE_24 			0xFF7084
#define LIGHTSLATEGRAY_24 			0x998877
#define LIGHTSTEELBLUE_24 			0xDEC4B0
#define LIGHTYELLOW_24 				 	0xE0FFFF
#define LIME_24 								0x00FF00
#define LIMEGREEN_24 						0x32CD32
#define LINEN_24 								0xE6F0FA
#define MAGENTA_24 							0xFF00FF
#define MAROON_24 							0x000080
#define MEDIUMAQUAMARINE_24 		0xAACD66
#define MEDIUMBLUE_24 					0xCD0000
#define MEDIUMORCHID_24 				0xD355BA
#define MEDIUMPURPLE_24 				0xD87093
#define MEDIUMSEAGREEN_24 			0x71B33C
#define MEDIUMSLATEBLUE_24 			0xEE687B
#define MEDIUMSPRINGGREEN_24 		0x9AFA00
#define MEDIUMTURQUOISE_24 			0xCCD148
#define MEDIUMVIOLETRED_24 			0x8515C7
#define MIDNIGHTBLUE_24 				0x701919
#define MINTCREAM_24 						0xFAFFF5
#define MISTYROSE_24 						0xE1E4FF
#define MOCCASIN_24 						0xB5E4FF
#define NAVAJOWHITE_24 					0xADDEFF
#define NAVY_24 								0x800000
#define OLDLACE_24 							0xE6F5FD
#define OLIVE_24 								0x008080
#define OLIVEDRAB_24 						0x238E6B
#define ORANGE_24 							0x00A5FF
#define ORANGERED_24 						0x0045FF
#define ORCHID_24 							0xD670DA
#define PALEGOLDENROD_24 				0xAAE8EE
#define PALEGREEN_24 						0x98FB98
#define PALETURQUOISE_24 				0xEEEEAF
#define PALEVIOLETRED_24 				0x9370D8
#define PAPAYAWHIP_24 					0xD5EFFF
#define PEACHPUFF_24 						0xB9DAFF
#define PERU_24 								0x3F85CD
#define PINK_24 								0xCBC0FF
#define PLUM_24 								0xDDA0DD
#define POWDERBLUE_24 					0xE6E0B0
#define PURPLE_24 							0x800080
#define RED_24 									0x0000FF
#define ROSYBROWN_24 						0x8F8FBC
#define ROYALBLUE_24 						0x901604
#define SADDLEBROWN_24 					0x13458B
#define SALMON_24 							0x7280FA
#define SANDYBROWN_24 					0x60A4F4
#define SEAGREEN_24 						0x578B2E
#define SEASHELL_24 						0xEEF5FF
#define SIENNA_24 							0x2D52A0
#define SILVER_24 							0xC0C0C0
#define SKYBLUE_24 							0xEBCE87
#define SLATEBLUE_24 						0xCD5A6A
#define SLATEGRAY_24 						0x908070
#define SNOW_24 								0xFAFAFF
#define SPRINGGREEN_24 					0x7FFF00
#define STEELBLUE_24 						0xB48246
#define TAN_24 									0x8CB4D2
#define TEAL_24 								0x808000
#define THISTLE_24 							0xD8BFD8
#define TOMATO_24 							0x4763FF
#define TURQUOISE_24 						0xD0E040
#define VIOLET_24 							0xEE82EE
#define VIOLETRED_24 						0x9020D0
#define WHEAT_24 								0xB3DEF5
#define WHITE_24 								0xFFFFFF
#define WHITESMOKE_24 					0xF5F5F5
#define YELLOW_24 							0x00FFFF
#define YELLOWGREEN_24 					0x32CD9A



#endif //_MQ2_API_
