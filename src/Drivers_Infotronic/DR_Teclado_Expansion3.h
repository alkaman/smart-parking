/*******************************************************************************************************************************//**
 *
 * @file		DR_Teclado_Expansion3.h
 * @brief		Encabezados, Includes y Defines
 * @date		11 de nov. de 2016
 * @author		Alan Kinast, Marcos Trautman
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_gpio.h"
#include "DR_pinsel.h"
#include "DR_7Seg_Expansion3.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define	ON		1
#define	OFF		0
#define	SALIDA	1
#define	ENTRADA	0
/** -------------------------------------------------------------------------------------
 *Entradas
 */
#define			in1				4,29
#define			in2				2,11
#define		Entrada0		(   BufferEntradas        & 0x01 )
#define		Entrada1		( ( BufferEntradas >> 1 ) & 0x01 )
#define		ACEPTAReSTADO	4
#define		ENTRADAS_EXPANSION3		2

/** -------------------------------------------------------------------------------------
 *Teclado
 */
#define		REBOTES		4
#define		fila0		FIO2PIN13
#define		fila1		FIO0PIN18
#define		fila2		FIO2PIN10
#define		fila3		FIO0PIN11
#define		F0			0
#define		F1			1
#define		F2			2
#define		F3			3
#define		F4			4
#define		F5			5
#define		F6			6
#define		F7			7
#define		NO_KEY		0xff



 //*PLACA EXPANSION 3

//!< Teclado
#define		EX3_fila0		1,25
#define		EX3_fila1		1,22
#define		EX3_fila2		1,19
#define		EX3_fila3		0,20
#define		EX3_columna0	3,25
#define		EX3_columna1	1,27
#define		DIGITOS		6
#define		DSP0		0				//!< Display verde
#define		DSP1		1				//!< Display rojo

//Valores para configuracion del PLL:
#define CLOCK_SETUP_Value 	    1
#define SCS_Value				0x00000020
#define CLKSRCSEL_Value         0x00000001
#define PLL0_SETUP_Value        1
#define PLL0CFG_Value           0x00050063
#define PLL1_SETUP_Value        1
#define PLL1CFG_Value           0x00000023
#define CCLKCFG_Value           0x00000003
#define USBCLKCFG_Value         0x00000000
#define PCLKSEL0_Value          0x00000000
#define PCLKSEL1_Value          0x00000000
#define PCONP_Value             0x042887DE
#define CLKOUTCFG_Value         0x00000000
#define FLASHCFG_Value			0x00004000

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void DriverTeclado_Expansion3( void );
void DriverTecladoSW_Expansion3 ( unsigned char );
unsigned char DriverTecladoHW_Expansion3( void );
void Inic_Expansion3( void );
void Debounce_Expansion3(void);
