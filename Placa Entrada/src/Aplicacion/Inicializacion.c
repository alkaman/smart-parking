
/*******************************************************************************************************************************//**
 *
 * @file		Inicializacion.c
 * @brief		Inicializaciones del Kit de Info II Infotronic
 * @date		23/03/16
 * @author		Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "Inicializacion.h"

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
 \fn  void Inicializar ( void )
 \brief Iniciliaza los perifericos y y los registros necesarios para el hardware actuante
 \param void
 \return void
 */
void Inicializacion ( void )
{
	//!< Infotronic y hardware externo
	InicializarTeclado( );//!< Teclado placa base infotronic
	//Inicializar_Display ();//!<Display Expansion 2
	Inic_Expansion3();//!<Display y teclado matricial expansion 3
	Inicializacion_EntradasDigitales();//!< Inicializo entradas digitales

	//!< LPC1769
	InitPLL();//!<Configuro en primer lugar el PLL:Estabiliza el oscilador interno del micro en 100MHz
	SysTickInit();//!<Inicializo el SysTick a 2,5 mseg
	UART0_Inicializacion();//!<Inicializo Puerto Serie
	//ADC_Init ();//!<Inicializo ADC
	InicializarPWM ();
	Inic_LCD();//!<Inicializo LCD
	Inic_RTC();//!<Inicializo RTC
	RTC_HabilitaInterrupcion(0);//!< doy start al RTC cada un segundo
}

/**
	\fn  void Init (void)
	\brief Inicializacion Reles placa base infotronic
 	\details configuracion de pines correspondientes a los relay
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void Inicializar_Reles(void)
{
	SetDIR( RELAY1 , SALIDA );
	SetDIR( RELAY2 , SALIDA );
	SetDIR( RELAY3 , SALIDA );
	SetDIR( RELAY4 , SALIDA );
}

/**
	\fn  void prueba_teclas(void)
	\brief Debugueo para prueba de teclas placa base
 	\details Utiliza la primitiva Display para mostrar por display de la expansion 2 el número
 	 de tecla presionada
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void prueba_teclas(void)
{
	uint8_t teclas=0;
	teclas=GetKey_Debounce ();
    if(teclas&0x01)
    {
    	Display(1,DSP0);
    }
    if(teclas&0x02)
    {
    	Display(2,DSP1);
    }
    if(teclas&0x04)
    {
    	Display(3,DSP0);
    }
    if(teclas&0x08)
    {
    	Display(4,DSP0);
    }
    if(teclas&0x10)
    {
    	Display(5,DSP0);
    }
}
