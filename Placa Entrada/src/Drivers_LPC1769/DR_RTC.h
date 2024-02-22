/*******************************************************************************************************************************//**
 *
 * @file		DR_RTC.h
 * @brief		Encabezados, Includes y Defines
 * @date		11 de nov. de 2016
 * @author		Alan Kinast, Marcos Trautman
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef DRIVERS_DR_RTC_H_
#define DRIVERS_DR_RTC_H_
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_gpio.h"
#include "Inicializacion.h"
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define RTC_INTERRUPCION_SEG		0
#define RTC_INTERRUPCION_MIN		1
#define RTC_INTERRUPCION_HORA		2
#define RTC_INTERRUPCION_DIAMES		3
#define RTC_INTERRUPCION_DIASEM		4
#define RTC_INTERRUPCION_DIAANIO	5
#define RTC_INTERRUPCION_MES		6
#define RTC_INTERRUPCION_ANIO		7


#define		RTC 			(( __RW uint32_t  * ) 0x40024000UL )
#define		RTCILR			RTC[0]
#define		RTCCCR			RTC[2]
#define		RTCCIIR			RTC[3]
#define		RTCAMR			RTC[4]
#define		RTC_AUX			RTC[23]
#define		RTC_AUXEN		RTC[22]
#define		RTCCTIME0		RTC[5]
#define		RTCCTIME1		RTC[6]
#define		RTCCTIME2		RTC[7]
#define		RTCSEC			RTC[8]
#define		RTCMIN			RTC[9]
#define		RTCHOUR			RTC[10]
#define		RTCDOM			RTC[11]
#define		RTCDOW			RTC[12]
#define		RTCDOY			RTC[13]
#define		RTCMONTH		RTC[14]
#define		RTCYEAR			RTC[15]
#define		RTCCALIBRATION	RTC[16]
#define		RTCGPREG0		RTC[17]
#define		RTCGPREG1		RTC[18]
#define		RTCGPREG2		RTC[19]
#define		RTCGPREG3		RTC[20]
#define		RTCGPREG4		RTC[21]
#define		RTCALSEC		RTC[24]
#define		RTCALMIN		RTC[25]
#define		RTCALHOUR		RTC[26]
#define		RTCALDOM		RTC[27]
#define		RTCALDOW		RTC[28]
#define		RTCALDOY		RTC[29]
#define		RTCALMON		RTC[30]
#define		RTCALYEAR		RTC[31]




/*#define		ISER 		( ( __RW uint32_t  * ) 0xE000E100UL )
	#define 	ISER0		ISER[0]
	#define 	ISER1		ISER[1]

	#define		ICER 		( ( __RW uint32_t  * ) 0xE000E180UL )
	#define		ICER0		ICER[0]
	#define		ICER1		ICER[1]*/

	#define		ISPR 		( ( __RW uint32_t  * ) 0xE000E200UL )
	#define		ISPR0		ISPR[0]
	#define		ISPR1		ISPR[1]

	#define		ICPR 		( ( __RW uint32_t  * ) 0xE000E280UL )
	#define		ICPR0		ICPR[0]
	#define		ICPR1		ICPR[1]

	#define		IABR 		( ( __RW uint32_t  * ) 0xE000E300UL )
	#define		IABR0		IABR[0]
	#define		IABR1		IABR[1]

	#define		IPR 		( ( __RW uint32_t  * ) 0xE000E400UL )
	#define		IPR0		IPR[0]
	#define		IPR1		IPR[1]
	#define		IPR2		IPR[2]
	#define		IPR3		IPR[3]
	#define		IPR4		IPR[4]
	#define		IPR5		IPR[5]
	#define		IPR6		IPR[6]
	#define		IPR7		IPR[7]
	#define		IPR8		IPR[8]

	#define		STIR_ 		( ( __RW uint32_t  * ) 0xE000EF00UL )
	#define		STIR 		STIR_[0]





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
void Inic_RTC(void);
void RTC_HabilitaInterrupcion(uint32_t);
#endif /* DRIVERS_DR_RTC_H_ */

