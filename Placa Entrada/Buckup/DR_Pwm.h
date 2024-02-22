/*
 * DR_Pwm.h
 *
 *  Created on: 19/10/2016
 *      Author: Alka
 */

#ifndef DRIVERS_LPC1769_DR_PWM_H_
#define DRIVERS_LPC1769_DR_PWM_H_

//includes
#include "DR_tipos.h"
#include "DR_Rgb.h"
#include "DR_pinsel.h"
#include "DR_gpio.h"


// Etiquetas Relacionadas con el PWM:
#define				PRESCALER_PWM				(25000 - 1)
#define				PERIODO_T0_PWM				200
#define				MATCH0_PWM					200
#define				MATCH2_PWM					198
#define				MATCH3_PWM					199
#define				CANT_SALIDAS_PWM			2			// Cantidad de MATCHS Sin Contar el MATCH0.
#define				CANT_CANALES_PWM			2

#define				MAX_MARCHA						0
#define				MIN_MARCHA						1
#define				MAX_CONTRAMARCHA				2
#define				MIN_CONTRAMARCHA				3
#define				FRENADO							4

#define				MAX_VALOR_MARCHA				( (MATCH0_PWM * 75 ) / 100 )
#define				MIN_VALOR_MARCHA				(  MATCH0_PWM / 2 )
#define				MAX_VALOR_CONTRAMARCHA			( (MATCH0_PWM * 75 ) / 100 )
#define				MIN_VALOR_CONTRAMARCHA			(  MATCH0_PWM / 2 )
#define				VALOR_NULL								  0

#define	AZUL		1
#define	ROJO		2
#define	VERDE		3
#define	VIOLETA		4
#define	AMARILLO	5
#define	BLANCO		6
#define	NO_COLOR	7


#define				PWM1_2	RGB_Azul// Led RGBBlue ---- ContraMarcha o Bajada del Motor de CC. ---- Canal 2 del PWM1
#define				PWM1_1	RGB_Rojo// Led RGBRed ---- Marcha o Subida del Motor de CC. ---- Canal 3 del PWM1
#define				PWM1_0	RGB_Verde// Led RGBGreen

#define					PWM1					2,0
#define					PWM2					2,1							//		43
#define					PWM3					2,2							//		44
#define					PWM4					2,3							//		45
#define					PWM5					2,4
#define					PWM6					2,5

#define			PWM1_PRESCALER			(100 - 1)		// Base de Tiempo: microsegundos.
#define			FRECUENCIA_GIRO			20000				// Frencuencia de Giro = 250 Hz.
#define			PWM1_MATCH2				( (FRECUENCIA_GIRO * 4) / 100 );
#define			PWM1_MATCH3				0


#define			VALOR_NULL				0


#define ENCENDIDO	1
#define APAGADO		0

//Registros
#define 	PCONP	(* ( ( __RW uint32_t  * ) 0x400FC0C4UL ))

//!< ///////////////////   PCLKSEL   //////////////////////////
//!< Peripheral Clock Selection registers 0 and 1 (PCLKSEL0 -0x400F C1A8 and PCLKSEL1 - 0x400F C1AC) [pag. 56 user manual]
//!< 0x400FC1A8UL : Direccion de inicio de los registros de seleccion de los CLKs de los dispositivos:
#define		PCLKSEL		( ( __RW uint32_t  * ) 0x400FC1A8UL )
//!< Registros PCLKSEL
#define		PCLKSEL0	PCLKSEL[0]
#define		PCLKSEL1	PCLKSEL[1]

//registros interrupciones
#define		ISER		( ( uint32_t * ) 0xE000E100UL )
//0xE000E180UL : Direccion de inicio de los registros de deshabilitacion (clear) de interrupciones en el NVIC:
#define		ICER		( (  uint32_t * ) 0xE000E180UL )
//Registros ISER: Para habilitar las Interupciones Se activan con 1 Escribiendo un 0 no hace nada
#define		ISER0		ISER[0]
#define		ISER1		ISER[1]
#define		ISE_PWM		ISER[0] |= (0x00000001<<9)//ISER0->bit21 pongo un 1 en el bit 21 para habilitar la INT EINT3
//Registros ICER: Para habilitar las Interupciones Se activan con 1 Escribiendo un 0 no hace nada
#define		ICER0		ICER[0]
#define		ICER1		ICER[1]
#define		ICE_PWM		ICER[0] |= (0x00000001<<9)//ISER0->bit21 pongo un 1 en el bit 21 para habilitar la INT EINT3

//pwm interrupt registers
#define		MCINTF 		( ( uint32_t * ) 0x400B8068UL )//read flag
#define		MCINTF_SET 	( ( uint32_t * ) 0x400B806CUL )//set flag interrupt
#define		PWMINTF_CLR ( ( uint32_t * ) 0x400B8070UL )//clear flag interupt

//bit9imat2//match register 2
//bit5imat1//match register 1
//bit1imat0//match register 0


#define		CLR_EINT3		EXTINT[0] |= 0x00000001 << 3 // bajo el flag de EINT3




//registros pwm1
#define		PWM		( ( __RW uint32_t  * ) 0x40018000UL )

#define		PWM1IR		PWM[0]
#define		PWM1TCR		PWM[1]
#define		PWM1TC		PWM[2]
#define		PWM1PR		PWM[3]
#define		PWM1PC		PWM[4]
#define		PWM1MCR		PWM[5]
#define		PWM1MR0		PWM[6]
#define		PWM1MR1		PWM[7]
#define		PWM1MR2		PWM[8]
#define		PWM1MR3		PWM[9]
#define		PWM1CCR		PWM[10]
#define		PWM1CR0		PWM[11]
#define		PWM1CR1		PWM[12]
#define		PWM1CR2		PWM[13]
#define		PWM1CR3		PWM[14]
#define		PWM1MR4		PWM[15]
#define		PWM1MR5		PWM[16]
#define		PWM1MR6		PWM[17]
#define		PWM1PCR		PWM[18]
#define		PWM1LER		PWM[19]
#define		PWM1CTCR	PWM[20]

//prototipos
void InicializarPWM1 (void);
//void Pop_PWM ( void );
//void Push_PWM (uint8_t );
//void Set_PWM (void);
//void InicializarPWM2 ( void );
void InicializarPWM ( void );
void PopServo ( void );



#endif /* DRIVERS_LPC1769_DR_PWM_H_ */
