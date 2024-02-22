/*******************************************************************************************************************************//**
 *
 * @file		DR_SysTick.h
 * @brief		Encabezados, Includes y Defines
 * @date		11 de nov. de 2016
 * @author		Alan Kinast, Marcos Trautman
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef DR_SYSTICK_H_
#define DR_SYSTICK_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"
#include "DR_gpio.h"
#include "DR_Rgb.h"
#include "DR_Teclado.h"
#include "DR_Segmento.h"
#include "DR_Antirebote_Digital.h"
#include "DR_Pwm.h"
#include "DR_uart.h"
#include "DR_7Seg_Expansion3.h"
#include "DR_Teclado_Expansion3.h"
#include "DR_EntradaDigital.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define ENCENDIDO	1
#define APAGADO		0

#define CANT_AUTOS	8
#define SEGUNDOS_ESTADIA	400
/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
//!< 0xE000E010UL: Registro de control del SysTick:
#define 	SYSTICK		( (systick_t *) 0xE000E010UL )

#define		STCTRL		SYSTICK->_STCTRL

	#define	ENABLE			SYSTICK->bits._ENABLE
	#define	TICKINT			SYSTICK->bits._TICKINT
	#define	CLKSOURCE		SYSTICK->bits._CLKSOURCE
	#define	COUNTFLAG		SYSTICK->bits._COUNTFLAG

#define		STRELOAD	SYSTICK->_STRELOAD
#define		STCURR		SYSTICK->_STCURR
#define		STCALIB		SYSTICK->_STCALIB

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
//!< /////////////		SYSTICK		///////////////////////////
//!< Tipo de dato específico para manejar el SYSTICK
typedef struct
{
	union{
		__RW uint32_t _STCTRL;
		struct{
			__RW uint32_t _ENABLE:1;
			__RW uint32_t _TICKINT:1;
			__RW uint32_t _CLKSOURCE:1;
			__RW uint32_t _RESERVED0:13;
			__RW uint32_t _COUNTFLAG:1;
			__RW uint32_t _RESERVED1:15;
		}bits;
	};
	__RW uint32_t _STRELOAD;
	__RW uint32_t _STCURR;
	__R uint32_t  _STCALIB;
}systick_t;



/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void SysTickInit ( void );

#endif /* DR_SYSTICK_H_ */
