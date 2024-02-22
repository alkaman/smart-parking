/*
 * DR_Rgb.c
 *
 *  Created on: 10/8/2016
 *      Author: Alka
 */

#include "DR_Rgb.h"
#include "DR_Segmento.h"

//P2[0] PWM1.1 42	SD0
//P2[1] PWM1.2 43	PWM2	Azul
//P2[2] PWM1.3 pin44 PWM1	Rojo
//P2[3] PWM1.4 45	PWM0	Verde


//#define RGB_comun

/**
@fn void RGB( uint16_t color,uint8_t accion )
@brief Genera el funcionamiento de cada color del RGB
@author usted
@param [in] color: 1:R,2:G, B:3
@param [in] accion: 0: APAGADO, 1: PRENDIDO, 2: PARPADEA con una frecuencia de 1Hz.
@return void
*/

uint8_t FlagFreq[3]={0,0,0};

void RGB( uint16_t color,uint8_t accion )
{
	if(accion!=2)
	{
		FlagFreq[color-1]=0;
		if(color==1)
		{
			SetPIN(RGB_Rojo,accion);
		}
		if(color==2)
		{
			SetPIN(RGB_Verde,accion);
		}
		if(color==3)
		{
			SetPIN(RGB_Azul,accion);
		}
	}
	if(accion==2)
	{
		FlagFreq[color-1]=1;
	}
}

void InitRGB (void)
{

		SetDIR ( RGB_Rojo,SALIDA);
		SetDIR ( RGB_Azul,SALIDA);
		SetDIR ( RGB_Verde,SALIDA);

}


