/*******************************************************************************************************************************//**
 *
 * @file		DR_Pwn.h
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
#include "DR_tipos.h"
#include "DR_gpio.h"
#include "DR_pinsel.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define			PWM1_PRESCALER			(100 - 1)		// Base de Tiempo: microsegundo
#define			PWM1_PRESCALER2			(100000 - 1)	// Base de tiempo: Milisegundo
#define			FRECUENCIA_GIRO			20000//4000				//500 hz// Frencuencia de Giro = 250 Hz.
#define			PWM1_MATCH2				( (FRECUENCIA_GIRO * 4) / 100 )
#define			PWM1_MATCH3				0

#define			CANT_CANALES_PWM		2

#define			VALOR_NULL				0
/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
// Defines Registros PWW

#define		PWM			( ( __RW uint32_t * ) 0x40018000UL )

#define		PWM1IR			PWM[0]
#define		PWM1TCR			PWM[1]
#define		PWM1TC			PWM[2]
#define		PWM1PR			PWM[3]
#define		PWM1PC			PWM[4]
#define		PWM1MCR			PWM[5]
#define		PWM1MR0			PWM[6]
#define		PWM1MR1			PWM[7]
#define		PWM1MR2			PWM[8]
#define		PWM1MR3			PWM[9]
#define		PWM1CCR			PWM[10]
#define		PWM1CR0			PWM[11]
#define		PWM1CR1			PWM[12]
#define		PWM1CR2			PWM[13]
#define		PWM1CR3			PWM[14]
#define		PWM1MR4			PWM[16]
#define		PWM1MR5			PWM[17]
#define		PWM1MR6			PWM[18]
#define		PWM1PCR			PWM[19]
#define		PWM1LER			PWM[20]
#define		PWM1CTCR		PWM[28]

// Salidas de PWM:
#define					PWM1					2,0
#define					PWM2					2,1							//		43
#define					PWM3					2,2							//		44
#define					PWM4					2,3							//		45
#define					PWM5					2,4
#define					PWM6					2,5
//!< 0x400FC0C4UL : Direccion de inicio del registro de habilitación de dispositivos:
#define 	PCONP	(* ( ( __RW uint32_t  * ) 0x400FC0C4UL ))

//!< ///////////////////   PCLKSEL   //////////////////////////
//!< Peripheral Clock Selection registers 0 and 1 (PCLKSEL0 -0x400F C1A8 and PCLKSEL1 - 0x400F C1AC) [pag. 56 user manual]
//!< 0x400FC1A8UL : Direccion de inicio de los registros de seleccion de los CLKs de los dispositivos:
#define		PCLKSEL		( ( __RW uint32_t  * ) 0x400FC1A8UL )
//!< Registros PCLKSEL
#define		PCLKSEL0	PCLKSEL[0]
#define		PCLKSEL1	PCLKSEL[1]


//0xE000E100UL : Direccion de inicio de los registros de habilitación (set) de interrupciones en el NVIC:
#define		ISER		( ( uint32_t * ) 0xE000E100UL )
//0xE000E180UL : Direccion de inicio de los registros de deshabilitacion (clear) de interrupciones en el NVIC:
#define		ICER		( (  uint32_t * ) 0xE000E180UL )


//Registros ISER: Para habilitar las Interupciones Se activan con 1 Escribiendo un 0 no hace nada
#define		ISER0		ISER[0]
#define		ISER1		ISER[1]
/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void InicializarPWM1 (void);

void InicializarPWM ( void );
void PopServo ( void );
