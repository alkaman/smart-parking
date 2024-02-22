/*******************************************************************************************************************************//**
 	\file #include PR_Temperatura.c
 	\brief Aplicacion que convierte el valor de cuentas a una Temperatura dada
 	\details Trabajo Practico Obligatorio
 	\author Marcos Trautman, Alan Kinast
 	\date 2016.11.25
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "PR_Temperatura.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

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
extern uint8_t Buffer_Debounce;
/***********************************************************************************************************************************
 *** VARIABLES GLOBLES PRIVADAS AL MODULO
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

@fn void Temperatura( uint16_t cuentas)
@brief Convierte el valor de cuentas en un valor de tempeatura tal que ;
0 cuenta  0 grados
1000 cuentas  200 grados
2000 cuentas  300 grados
3000 cuentas  380 grados
4000 cuentas  450 grados
12 bits
4095 cuentas max
En cada segmento la temperatura se comporta de forma lineal .
@author usted
@param [in] cuentas: valor leido del Bufer del ADC
@return valor de temperatura
*/
uint8_t Temperatura( uint16_t cuentas)
{
	if(cuentas==0)
	{
		return 0;
	}
	if(cuentas<=1000)
	{
		return (cuentas*200/1000);
	}
	if(cuentas<=2000)
	{
		return ((cuentas*(300-200)/(2000-1000))+100);
	}
	if(cuentas<=3000)
	{
		return ((cuentas*(380-300)/(3000-2000))+140);
	}
	if(cuentas<=4000)
	{
		return ((cuentas*(450-380)/(4000-3000))+170);
	}
	//asumo que despues de 4000 se comporta igual
	return ((cuentas*(450-380)/(4000-3000))+170);
}