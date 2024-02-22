 /*******************************************************************************************************************************//**
 *
 * @file		DR_EINT.c
 * @brief		Interrupciones externas
 * @date		Fecha de creacion del archivo 09-06-16
 * @author		Marcelo, Trujillo
 *
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
  *** INCLUDES
  **********************************************************************************************************************************/
#include "DR_EINT.h"

 /***********************************************************************************************************************************
  *** DEFINES PRIVADOS AL MODULO
  **********************************************************************************************************************************/
#define		EINT0_PIN		2,10

 /***********************************************************************************************************************************
  *** MACROS PRIVADAS AL MODULO
  **********************************************************************************************************************************/

 /***********************************************************************************************************************************
  *** TIPOS DE DATOS PRIVADOS AL MODULO
  **********************************************************************************************************************************/

 /***********************************************************************************************************************************
  *** TABLAS PRIVADAS AL MODULO
  **********************************************************************************************************************************/

 /***********************************************************************************************************************************
  *** VARIABLES GLOBALES PUBLICAS
  **********************************************************************************************************************************/

 /***********************************************************************************************************************************
  *** VARIABLES GLOBALES PRIVADAS AL MODULO
  **********************************************************************************************************************************/

 /***********************************************************************************************************************************
  *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
  **********************************************************************************************************************************/

  /***********************************************************************************************************************************
  *** FUNCIONES PRIVADAS AL MODULO
  **********************************************************************************************************************************/

  /***********************************************************************************************************************************
  *** FUNCIONES GLOBALES AL MODULO
  **********************************************************************************************************************************/
/**
	\fn void EXT0_Inicializacion(void)
	\brief Inicializacion interrupcion externa
 	\param void
	\return void
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void EXT0_Inicializacion(void)
{
	 SetPINSEL( EINT0_PIN , PINSEL_FUNC1 ); 	// Configuro el P2[10] (SW1) para que trabaje como EINT0 esto debe hacerse con
	                                     	 	// la Interr deshabilitada Pag 25
	 EXTMODE0_F;                         		// Configuro la interrupcion externa 0 por flanco
                                         	 	// EXTPOLAR0_P; // si quiero por flanco positivo debo cambiarlo en EXTPOLAR
	 ISE_EINT0;                      	 		// Habilito Interrupcion Externa 0
}

/**
	\fn void EINT0_IRQHandler(void)
	\brief Handler Interrupcion Externa
 	\param void
	\return void
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void EINT0_IRQHandler(void)
{
	CLR_EINT0;									// borro el flag EINT0 de interrupcion externa 0 del registro EXTINT


}
