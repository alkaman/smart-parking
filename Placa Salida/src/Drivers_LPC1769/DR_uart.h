/*******************************************************************************************************************************//**
 *
* @file		    DR_Uart.h
 * @brief		Encabezados, Includes y Defines
 * @date		11 de nov. de 2016
 * @author		Alan Kinast, Marcos Trautman
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef DR_UART_H_
#define DR_UART_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"
#include "DR_PLL.h"
#include "DR_gpio.h"
#include "DR_EINT.h"
#include "maquina_estados.h"
#include "DR_SysTick.h"
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
//!< Maquinas de estado de Desentramado
#define estado0 0
#define estado1 1
#define estado2 2
#define estado3 3
#define estado4 4
#define estado5 5
#define estado6 6
#define estado7 7

//!< /////////////		UARTs		///////////////////////////
//0x40010000UL : Registro de recepcion de la UART0:
#define		DIR_UART0		( ( __RW uint32_t  * ) 0x4000C000UL )

#define		U0RBR		DIR_UART0[0]	// Registro de Recepción RBR
#define		U0THR		DIR_UART0[0]	// Registro de Transmisión THR
#define		U0DLL		DIR_UART0[0]	// Parte baja del divisor de la UART0:
#define		U0IER		DIR_UART0[1]	// Registro de Habilitación de interrupciones de la UART0:
#define		U0DLM		DIR_UART0[1]	// Parte Alta del divisor de la UART0:
#define		U0IIR		DIR_UART0[2]	// Registro de Identificación de interrupciones de la UART0:
#define		U0LCR		DIR_UART0[3]	// Line CONTROL Register de la UART0:
#define		U0LSR		DIR_UART0[5]	// Line STATUS Register de la UART0:

//Macros UART0
#define		U0DLAB_OFF	(U0LCR & 0xEF)
#define		U0DLAB_ON	(U0LCR | 0x80)


//0x40010000UL : Registro de recepcion de la UART1:
#define		DIR_UART1		( ( __RW uint32_t  * ) 0x40010000UL )

#define		U1RBR		DIR_UART1[0]
#define		U1THR		DIR_UART1[0]
#define		U1DLL		DIR_UART1[0]
#define		U1IER		DIR_UART1[1]
#define		U1DLM		DIR_UART1[1]
#define		U1IIR		DIR_UART1[2]
#define		U1LCR		DIR_UART1[3]
#define		U1LSR		DIR_UART1[5]

//Comunicación serie
#define 	TX0			0, 2	//Tx de la UART0
#define 	RX0			0, 3	//Rx de la UART0

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
// extern tipo nombreVariable;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void Push_RX (uint8_t dato);
int16_t Pop_RX ( void);
void UART0_Inicializacion (void);

void Push_TX ( uint8_t dato);
int16_t Pop_TX ( void );

void transmitir (char * S);

void Desentramado_Entrada (void);
void Desentramado_Entrada_2 (void);

void Desentramado_Salida (void);
void Desentramado_Salida_2 (void);

#endif /* DR_UART_H_ */
