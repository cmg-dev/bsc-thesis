#ifndef _MQ2_HARDWARE_DEFS_ 
#define _MQ2_HARDWARE_DEFS_


/**
	@def OFFSET_CONTROL_REG
	Offset to the Control-Register in every Periph-Hardwareblock
	@def OFFSET_STATUS_REG
	Offset to the Status-Register in every Periph-Hardwareblock
	@def OFFSET_ERROR_REG
	Offset to the Error-Register in every Periph-Hardwareblock
	Writes to this register resets the corresponding bits
*/
#define		PERIPH_BLOCKSPAN					0x10000	/*Aktuell 16 bits */

#define		VALUE_BLOCK_IDENT_1					0x50494249
#define		VALUE_BLOCK_IDENT_2					0x70696269
#define		VALUE_BLOCK_IDENT_3					0x4D513250

#define		OFFSET_BLOCK_IDENT_1					0x00
#define		OFFSET_BLOCK_IDENT_2					0x04
#define		OFFSET_BLOCK_IDENT_3					0x08
#define		OFFSET_BLOCK_IDENT_4					0x0C
#define		OFFSET_BLOCK_VERSION					0x10
#define		OFFSET_CONTROL_REG					0x20			/* Offset des CONTROL-Registers im Hardware-Peripherieblocktemplate */
#define		OFFSET_STATUS_REG					0x24			/* Offset des STATUS-Registers im Hardware-Peripherieblocktemplate */
#define		OFFSET_ERROR_REG					0x28			/* Offset des ERROR-Registers im Hardware-Peripherieblocktemplate */

#define		SENSOR_CONTROL_EXP_FREQ_BASE_FREQ			25000000 //Frequenz des Blockes, normalerweise immer 25Mhz
//Bitdefinitionen für SENSOR_CONTROL
#define		SENSOR_RESET						0x01
#define		SENSOR_1_RESETMASKBIT					0x02
#define		SENSOR_2_RESETMASKBIT					0x04
#define		SENSOR_3_RESETMASKBIT					0x08
#define		SENSOR_4_RESETMASKBIT					0x10
#define		SENSOR_1_EXPOSUREMASKBIT				0x10000			
#define		SENSOR_2_EXPOSUREMASKBIT				0x20000
#define		SENSOR_3_EXPOSUREMASKBIT				0x40000
#define		SENSOR_4_EXPOSUREMASKBIT				0x80000
#define		RESET_EXP_FREQBIT					0x100000
#define		SENSOR_1_EXP_FREQMASKBIT				0x200000
#define		SENSOR_2_EXP_FREQMASKBIT				0x400000
#define		SENSOR_3_EXP_FREQMASKBIT				0x800000
#define		SENSOR_4_EXP_FREQMASKBIT				0x1000000

#define		EXP_DO_REG						0x40
#define		RETRIGGER_WAIT_REG					0x44
#define		EXP_FREQ_REG						0x48
#define		BASE_FREQ_REG						0x4C

//Bitdefinitionen für LVDS_OUT
#define		EN_LVDS							0x01
#define		EN_STREAM_1						0x02
#define		EN_STREAM_2						0x04
#define		EN_STREAM_3						0x08
#define		EN_STREAM_4						0x10
#define		FORCE_SYNC						0x20

//Bitdefinitionen für POWER_SUPERVISOR
#define		PG_5V0							1
#define		PG_3V3							2
#define		EXT_POWER						1
#define		RESET_5V0_ER						1
#define		RESET_3V3_ER						2

//Bitdefinitionen für SENSOR_SYNCHRONIZER
#define		SENSOR1_BEEF						1
#define		SENSOR2_BEEF						2
#define		SENSOR3_BEEF						4
#define		SENSOR4_BEEF						8
#define		SENSOR1_RBEEF						1
#define		SENSOR2_RBEEF						2
#define		SENSOR3_RBEEF						4
#define		SENSOR4_RBEEF						8
#define		PHASE_UPDOWN						0x10
#define		PHASE_STEP						0x20
#define		PLL_OUT_SELECT						0x7			/* Bits 0..2 */
#define		RESET_CHAIN1						0x40
#define		RESET_CHAIN2						0x44
#define		RESET_CHAIN3						0x48
#define		RESET_CHAIN4						0x4C


//Bitdefinitionen für VGA_FIFO
#define		VGA_FIFO_FULL						0x1
#define		RESET_VGA_FIFO_FULL					0x1
#define		VGA_SLAVE_CONTROL_REGISTER				0x00
#define		VGA_DMA_SOURCE_REGISTER					0x04
#define		VGA_DMA_MODULUS_REGISTER				0x08
#define		VGA_CURRENT_SOURCE_REGISTER				0x0C
#define		VGA_WIDTH						640
#define		VGA_HEIGHT						480
#define		VGA_SCREEN_WIDTH					VGA_WIDTH
#define		VGA_SCREEN_HEIGHT					VGA_HEIGHT
#define		VGA_START						1
#define		FIFO_RESET_REG						0x40

//Defines für IO Block
#define		OUTPUT_MODE_REG						0x40
#define		OUTPUT_DATA_REG						0x44
#define		INPUT_MODE_REG						0x50
#define		INPUT_DATA_REG						0x54
#define		INPUT_RESET_REG						0x58

//Defines für Steroskopie Block
#define		X_POS_REG						0x40
#define		OVERLAP_REG						0x44
#define		SCALE_REG						0x48
#define		GEGENSTANDSWEITE_REG					0x4C
#define		DP_REG							0x50
#define		DK_REG							0x54
#define		BRENNWEITE_REG						0x58
#define		BASIS_REG						0x5C
#define		DK_SCALED_REG						0x60
#define		MIN_DELTA_REG						0x64
#define		KOEFF1_OPT0_S1_REG					0x68
#define		KOEFF2_OPT0_S1_REG					0x6c
#define		KOEFF3_OPT0_S1_REG					0x70
#define		KOEFF1_OPT0_S2_REG					0x74
#define		KOEFF2_OPT0_S2_REG					0x78
#define		KOEFF3_OPT0_S2_REG					0x7c
#define		KOEFF1_OPT1_S2_REG					0x80
#define		KOEFF2_OPT1_S2_REG					0x84
#define		KOEFF3_OPT1_S2_REG					0x88
#define		KOEFF1_OPT1_S3_REG					0x8c
#define		KOEFF2_OPT1_S3_REG					0x90
#define		KOEFF3_OPT1_S3_REG					0x94
#define		KOEFF1_OPT2_S3_REG					0x98
#define		KOEFF2_OPT2_S3_REG					0x9c
#define		KOEFF3_OPT2_S3_REG					0xa0
#define		KOEFF1_OPT2_S4_REG					0xa4
#define		KOEFF2_OPT2_S4_REG					0xa8
#define		KOEFF3_OPT2_S4_REG					0xac
#define		FAKTOR_BASIS_REG					0xb0
#define		X_OPT0_KOEFF1_REG					0xb4
#define		X_OPT0_KOEFF2_REG					0xb8
#define		X_OPT0_KOEFF3_REG					0xbc
#define		X_OPT0_KOEFF4_REG					0xc0
#define		X_OPT0_KOEFF5_REG					0xc4
#define		X_OPT1_KOEFF1_REG					0xc8
#define		X_OPT1_KOEFF2_REG					0xcc
#define		X_OPT1_KOEFF3_REG					0xd0
#define		X_OPT1_KOEFF4_REG					0xd4
#define		X_OPT1_KOEFF5_REG					0xd8
#define		X_OPT2_KOEFF1_REG					0xdc
#define		X_OPT2_KOEFF2_REG					0xe0
#define		X_OPT2_KOEFF3_REG					0xe4
#define		X_OPT2_KOEFF4_REG					0xe8
#define		X_OPT2_KOEFF5_REG					0xec
#define		FAKTOR_BASIS_X1_REG					0xf0
#define		FAKTOR_BASIS_X2_REG					0xf4

#define		X_KOORD_REG						0x100
#define		Y_KOORD_REG						0x104
#define		MW_BS0_REG						0x108
#define		MW_BS1_REG						0x10c
#define		MW_BS2_REG						0x110
#define		MW_BS3_REG						0x114

#define		RESET_ANALYSIS_REG					0x120

//Defines für LEDLine-Ansteuerung
#define		LEDA_DATA_REG						0x40
#define		LEDA_PD_REG						0x44
#define		LEDA_CONFIG_REG						0x48
#define		LEDA_LED_ON_TIME_REG					0x4C
#define		LEDA_EN_MOD_REG						0x50
#define		LEDA_RESET_REG						0x54


//Defines für PISI Block
#define		PISI_IMAGE_WIDTH_REG					0x40
#define		PISI_IMAGE_HEIGHT_REG					0x44
#define		PISI_WRITEDATA						0x48
#define		PISI_RESET_REG						0x4C

//Defines für RLEE Block
#define		RLEE_RESET_REG						0x40
#define		RLE_FIFO_NOT_EMPTY					1


//Defines für SFIR
#define		CONFIGURATION_SFIR_OFFSET				0x00
#define		CONFIGURATION_SFIR_LENGTH				4
#define		NUM_FIR1_KOEEFIZIENTEN					25
#define		KOEFFIZIENTEN_FIR1_REG					0x40
#define		KOEFFIZIENTEN_FIR2_REG					0xA4


//Defines für Histogramm

#define		ALLWAYS_ENABLE_HISTO					1
#define		PHIS_ERROR						1

//Defines für Dataplexer

#define		DAPL_PISI_CONF						0x40
#define		DAPL_VFIF_CONF						0x44
#define		DAPL_SFIR_CONF						0x48
#define		DAPL_VEN2_CONF						0x4C
#define		DAPL_THBL_CONF						0x50
#define		DAPL_HIST_CONF						0x54
#define		DAPL_MON_CONF						0x58

//Defines für Threshold
#define		TRHO_THRESHOLD_LOWER					0x40
#define		TRHO_THRESHOLD_UPPER					0x44


//Defines für Videoengine2
#define		VE2_EVENTFIFO_DEPTH					256	/*Maximale Anzahl an speicherbaren events ind er fifo */
#define		VEN2_IMAGE_WIDTH					0x40
#define		VEN2_THRESHOLD						0x44
#define		VEN2_CLUSTER_X						0x48
#define		VEN2_CLUSTER_Y						0x4C
#define		VEN2_MINAREA						0x50
#define		VEN2_MAXAREA						0x54
#define		VEN2_EVENTFIFO_X1_BREITE				0x60
#define		VEN2_EVENTFIFO_Y1_HOEHE					0x64

#define		VEN2_BW							0x01
#define		VEN2_ELIMINIZER_ENABLE					0x02
#define		X1_FIFO_NOTEMPTY					0x01
#define		Y1_FIFO_NOTEMPTY					0x02

//Defines für DMA
#define		DMA_REG_STATUS				0x00
#define		DMA_REG_READADDRESS			0x04
#define		DMA_REG_WRITEADDRESS			0x08
#define		DMA_REG_LENGTH				0x0C
#define		DMA_REG_CONTROL				0x18
#define		DMA_BYTE				1
#define		DMA_HW					2
#define		DMA_WORD				4
#define		DMA_GO					8
#define		DMA_I_EN				16
#define		DMA_REEN				32
#define		DMA_WEEN				64
#define		DMA_LEEN				128
#define		DMA_RCON				256
#define		DMA_WCON				512
#define		DMA_DOUBLEWORD				1024
#define		DMA_QUADWORD				2048
#define		DMA_SOFTWARERESET			4096

#define		DMA_DONE				1
#define		DMA_BUSY				2
#define		DMA_REOP				4
#define		DMA_WEOP				8
#define		DMA_LEN					16


//Defines für SG-DMA
#define		SGDMA_REG_STATUS			0x00
#define		SGDMA_REG_CONTROL			0x04
#define		SGDMA_REG_NEXT_DESCRIPTOR		0x08

#define		SGDMA_RUN				0x20
#define		SGDMA_ERROR				0x01
#define		SGDMA_DESCRIPTOR_COMPLETED		0x04
#define		SGDMA_CHAIN_COMPLETED			0x08
#define		SGDMA_BUSY				0x10



//Syncram Definitionen
/**
	@struct SYNCRAM
	@brief Structure that holds syncram contents

*/
typedef struct _SYNCRAM_
{
  	unsigned int	ui_mq2_module_desc_base;						/**< Baseaddress of the Module Descriptor */

}SYNCRAM;



#endif //_MQ2_HARDWARE_DEFS_
