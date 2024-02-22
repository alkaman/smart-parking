/*******************************************************************************************************************************//**
 *
 * @file		Infotronic_garage.c
 * @brief		Includes Defines y Prototipos
 * @date		25 de nov. de 2016
 * @author		Alan Kinast, Marcos Trautman
 *
 **********************************************************************************************************************************/
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include "Infotronic_garage.h"


// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void)
{
	Inicializacion ( );
	transmitir("NN");//!< Para que actualice los datos de la placa de Entrada
	SetFechaHora();
	ShowHoraFecha();
	Display(000,DSP0);
	Display(000,DSP1);
    while(1)
    {
    	/*Desentramado_Entrada_2();
    	Maquina_estados_entrada();
    	Maquina_Estacionamiento();
    	Maquina_Estacionamiento_Digital();
    	EstadiaCheck();*/
    	ActualizaHora();
    	ActualizaFecha();
    	Desentramado_Salida_2();
    	Maquina_estados_salida();
    }
    return 0;
}
