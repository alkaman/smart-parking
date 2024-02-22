/*
 * ********************************************************************************************************************************
 *
 * @file		DR_EntradaDigital.h
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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define	ON		 1
#define	OFF		 0
#define	SALIDA	 1
#define	ENTRADA	 0
#define ENTRADAS_DIGITAL 2

#define EstadosEstables_Digital 4

/** -------------------------------------------------------------------------------------
 *Entradas
 */
//#define		in1				FIO4PIN29
//#define		in2				FIO2PIN11
#define			in1				4,29
#define			in2				2,11

#define		Entrada0		(   BufferEntradas        & 0x01 )
#define		Entrada1		( ( BufferEntradas >> 1 ) & 0x01 )

#define		ACEPTAReSTADO	4
#define		ENTRADAS_EXPANSION3		2


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
void DriverTecladoSW_EntradaDigital ( unsigned char  );
unsigned char DriverTecladoHW_EntradaDigital( void );
void DriverTeclado_EntradaDigital(void);
void Inicializacion_EntradasDigitales (void);
void debounce_EntradaDigital (void);


